#ifndef _BLOCK_SUDOKU_GAME_H_
#define _BLOCK_SUDOKU_GAME_H_

#include <iostream>
#include <vector>
#include <Eigen/Dense>

#define BOARD_SIZE 13
#define BLOCK_SIZE 5

// Not standard programming, but easier to deal with threading and stuff with this structure
class BlockSudoku
{
public:
    // Creates a new 13x13 board
    static Eigen::MatrixXi NewBoard();

    // Returns a 9x9 matrix of all the places you can put the 5x5 block on a 13x13 board
    static Eigen::MatrixXi GetAllValidMoves(Eigen::MatrixXi block, Eigen::MatrixXi board);

    // Checks to see if there are any valid moves to place the 5x5 block on a 13x13 board
    static bool CheckGameOverState(std::vector<Eigen::MatrixXi> block, Eigen::MatrixXi board);

    // Checks to see if placing a 5x5 block on the 13x13 board is a valid move
    static bool CheckIfValidMove(int x, int y, Eigen::MatrixXi block, Eigen::MatrixXi board);

    // Places a 5x5 block on the 13x13 board. This mutates the board.
    static bool PlaceBlock(int x, int y, Eigen::MatrixXi block, Eigen::MatrixXi* board);

    // Clears the board. This mutates the board.
    static int ClearBlocksAndScore(Eigen::MatrixXi* board);

private:
    BlockSudoku();
};

#endif