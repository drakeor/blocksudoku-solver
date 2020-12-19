#include <iostream>
#include <Eigen/Dense>
 
#include "blockfactory.h"
#include "blocksudoku.h"

#include <atomic>
#include <memory>
#include <mutex>

using namespace std;
using namespace Eigen;

#define QUEUE_DEPTH 3

// Play state struct. Probably make this a class later.
struct PlayState
{
  MatrixXi board;
  vector<MatrixXi> blockQueue;
  int score;
};

// Counts all possible moves with every block on the board
// This is an intensive operation!
ArrayXf CountAllMoves(MatrixXi board) {
  BlockFactory factory;
  vector<MatrixXi> blockList = factory.GetBlockList();
  ArrayXf blockMoves((int)blockList.size());
  for(int i=0;i<blockList.size();i++) {
    blockMoves(i) = (float)BlockSudoku::GetAllValidMoves(blockList[i], board).sum();
  }
  return blockMoves;
} 

vector<PlayState> RunThruPlayStates(vector<PlayState> playStates)
{
  // Should put this somewhere better
  const int TargetTreeChildren = 3;

  vector<PlayState> newPlayStates;
  std::mutex mylock;

  // Calculate this all in parallel
  #pragma omp parallel for
  for(int i=0;i<playStates.size();i++) {
    vector<PlayState> subPlayStates;
    PlayState* cState = &playStates[i];
    for(int j=0;j<cState->blockQueue.size();j++) {
      MatrixXi cBlock = cState->blockQueue[j];
      int childCount = 0;
      for(int x=0;x<9;x++) {
        for(int y=0;y<9;y++) {
          if(childCount < TargetTreeChildren && BlockSudoku::CheckIfValidMove(x, y, cBlock, cState->board)) {
            PlayState playState;
            playState.board = cState->board;
            BlockSudoku::PlaceBlock(x, y, cBlock, &(playState.board));
            playState.score = BlockSudoku::ClearBlocksAndScore(&(playState.board)) + cState->score;
            playState.blockQueue = cState->blockQueue;
            playState.blockQueue.erase(playState.blockQueue.begin() + j);
            subPlayStates.push_back(playState);
            ++childCount;
          }
        }
      }
    }

    // Add to final play states
    mylock.lock();
    newPlayStates.insert(newPlayStates.end(), subPlayStates.begin(), subPlayStates.end());
    mylock.unlock();
  }

  return newPlayStates;
}

// Adapted from: http://rosettacode.org/wiki/Combinations#C.2B.2B
vector<vector<int>> comb(int N, int K)
{
    vector<vector<int>> res;
    std::string bitmask(K, 1); // K leading 1's
    bitmask.resize(N, 0); // N-K trailing 0's
 
    // print integers and permute bitmask
    do {
        vector<int> subres;
        for (int i = 0; i < N; ++i) // [0..N-1] integers
        {
          if (bitmask[i]) subres.push_back(i);
        }
        res.push_back(subres);
    } while (std::prev_permutation(bitmask.begin(), bitmask.end()));

    return res;
}
 

struct PlayStateMoves
{
  PlayState* playState;
  float possibleMoves;
  ArrayXf allMoves;
};

int DoIteration()
{
  const int MaxIterations = 1000;
  int currentIteration = 0;
  int bestScore = 0;
  vector<PlayState> playStates;
  PlayState baseCase;
  BlockFactory blockFactory;

  // Add the base case
  baseCase.blockQueue = blockFactory.GenerateRandomBlocks(QUEUE_DEPTH);
  baseCase.board = BlockSudoku::NewBoard();
  baseCase.score = 0;
  playStates.push_back(baseCase);

  // Iterate through and find the solution
  while(currentIteration < MaxIterations) {
    cout << "Iteration " << currentIteration << ":" << endl;
    for(int i=0;i<QUEUE_DEPTH;i++) {
      cout << "Pass " << i << endl;
      playStates = RunThruPlayStates(playStates);
    }
    cout << "There are " << playStates.size() << " states to calculate for.." << endl;

    // If there are no states, game over!
    if(playStates.size() == 0) {
      cout << "Current game board may be impossible to solve!" << endl;
      break;
    }

    // Pre-populate struct
    auto playStateMoves = std::make_unique<PlayStateMoves[]>(playStates.size());

    // Expensive operation to run through all possible states
    #pragma omp parallel for
    for(int i=0;i<playStates.size();i++) {
      playStateMoves[i].playState = &playStates[i];
      ArrayXf allMoves = CountAllMoves(playStateMoves[i].playState->board);
      playStateMoves[i].possibleMoves = allMoves.mean();
      playStateMoves[i].allMoves = allMoves;

    }

    // Find the max state and make it the new play state
    float maxMoves = 0;
    int maxRecord = 0;
    for(int i=0;i<playStates.size();i++) {
      if(playStateMoves[i].possibleMoves > maxMoves) {
        maxMoves = playStateMoves[i].possibleMoves;
        maxRecord = i;
      }
    }

    // Only take the best move
    cout << "State " << maxRecord << " has the best play at " << maxMoves << endl;
    PlayState bestPlayState = *(playStateMoves[maxRecord].playState);

    // Calculate the percentage chance of having an optimal combo
    vector<MatrixXi> blockList = blockFactory.GetBlockList();
    vector<vector<int>> combos = comb(playStateMoves[maxRecord].allMoves.size(), QUEUE_DEPTH);

    atomic<int> possibleCombos(0);
    #pragma omp parallel for
    for(int j=0;j<combos.size();j++) {
      for(int k=0;k<combos[j].size();k++) {
        if(playStateMoves[maxRecord].allMoves[combos[j][k]] != 0) {
          possibleCombos++;
          break;
        }
      }
    }
    cout << possibleCombos << "/" << combos.size() << endl;
    float chanceOfPossibleCombo = (float)possibleCombos / (float)combos.size();

    // Regenerate blocks
    bestPlayState.blockQueue = blockFactory.GenerateRandomBlocks(QUEUE_DEPTH);
    bestScore = bestPlayState.score;
    playStates.clear();
    playStates.push_back(bestPlayState);

    // Show the current state
    cout << "Board:" << endl;
    cout << bestPlayState.board << endl;
    cout << "Block Queue: " << endl;
    for(int i=0;i<bestPlayState.blockQueue.size();i++) {
      cout << bestPlayState.blockQueue[i] << endl;
    }
    cout << "Score: " << bestPlayState.score << endl;
    cout << "Chance of Possible Move: " <<  chanceOfPossibleCombo*100 << "%" << endl;
    cout << "Iteration " << currentIteration << " finished. " << endl << endl;
    ++currentIteration;
  }

  cout << "Game Complete" << endl;
  return bestScore;
}

int main()
{
  DoIteration();
  return 0;
}