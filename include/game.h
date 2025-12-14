#ifndef _GAME_H_
#define _GAME_H_

#include <iostream>
#include <Eigen/Dense>

#include "blockfactory.h"
#include "blocksudoku.h"

#include <atomic>
#include <memory>
#include <mutex>

#define QUEUE_DEPTH 3

// Play state struct. Probably make this a class later.
struct PlayState
{
    Eigen::MatrixXi board;
    std::vector<Eigen::MatrixXi> blockQueue;
    int score;
};

 // For storing possible moves after running through them
struct PlayStateMoves
{
  PlayState* playState;
  float possibleMoves;
  Eigen::ArrayXf allMoves;
};

// Game state
class Game
{
public:
    // Creates a new game that runs to maxIterations and each node of the tree builds targetTreeChildren
    // calculateDeadStateProb will show the probability of getting a state where we can't get any moves
    Game(int targetTreeChildren, int maxIterations, bool calculateDeadStateProb);

    // Returns an array the size of the blockList from blockFactory showing the possible moves with each block
    Eigen::ArrayXf CountAllMoves(Eigen::MatrixXi board);

    // This runs through all the play states in parallel and builds up a tree to QUEUE_DEPTH, returning only the bottom most children of possible moves
    std::vector<PlayState> RunThruPlayStates(std::vector<PlayState> playStates);

    // Creates all possible combinations of length K for an array of size N. n choose k. 
    std::vector<std::vector<int>> comb(int N, int K);

    // Executes the game to maxIterations and returns the score
    int RunGame();
private:
    int targetTreeChildren;
    int maxIterations;
    bool calculateDeadStateProb;
};

#endif