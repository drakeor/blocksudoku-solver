#include <iostream>
#include <Eigen/Dense>
 
#include "blockfactory.h"
#include "blocksudoku.h"

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
float CountAllMoves(MatrixXi board) {
  BlockFactory factory;
  vector<MatrixXi> blockList = factory.GetBlockList();
  ArrayXf blockMoves((int)blockList.size());
  for(int i=0;i<blockList.size();i++) {
    blockMoves(i) = (float)BlockSudoku::GetAllValidMoves(blockList[i], board).sum();
  }
  return blockMoves.mean();
} 

vector<PlayState> RunThruPlayStates(vector<PlayState> playStates)
{
  // Should put this somewhere better
  const int TargetTreeChildren = 81;

  vector<PlayState> newPlayStates;
  std::mutex mylock;

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

struct PlayStateMoves
{
  PlayState* playState;
  float possibleMoves;
};

int DoIteration()
{
  const int MaxIterations = 100;
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
      playStateMoves[i].possibleMoves = CountAllMoves(playStateMoves[i].playState->board);
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