#include "blocksudoku.h"

using namespace Eigen;
using namespace std;

// Creates a new 13x13 board
MatrixXi BlockSudoku::NewBoard()
{
    return (MatrixXi(BOARD_SIZE, BOARD_SIZE) <<
        0,0,0,0,0,0,0,0,0,1,1,1,1,
        0,0,0,0,0,0,0,0,0,1,1,1,1,
        0,0,0,0,0,0,0,0,0,1,1,1,1,
        0,0,0,0,0,0,0,0,0,1,1,1,1,
        0,0,0,0,0,0,0,0,0,1,1,1,1,
        0,0,0,0,0,0,0,0,0,1,1,1,1,
        0,0,0,0,0,0,0,0,0,1,1,1,1,
        0,0,0,0,0,0,0,0,0,1,1,1,1,
        0,0,0,0,0,0,0,0,0,1,1,1,1,
        1,1,1,1,1,1,1,1,1,1,1,1,1,
        1,1,1,1,1,1,1,1,1,1,1,1,1,
        1,1,1,1,1,1,1,1,1,1,1,1,1,
        1,1,1,1,1,1,1,1,1,1,1,1,1
    ).finished();
}

// Returns a 9x9 matrix of all the places you can put the 5x5 block on a 13x13 board
MatrixXi BlockSudoku::GetAllValidMoves(MatrixXi block, MatrixXi board)
{
    MatrixXi validMoves = MatrixXi::Zero(9,9);
    for(int x=0;x<9;x++) {
        for(int y=0;y<9;y++) {
            if(CheckIfValidMove(x, y, block, board)) {
                int* moveCell = &validMoves(x,y);
                *moveCell = 1;
            }
        }
    }
    return validMoves;
}

// Checks to see if there are any valid moves to place the 5x5 block on a 13x13 board
bool BlockSudoku::CheckGameOverState(vector<MatrixXi> block, MatrixXi board)
{
    return false;
}

// Checks to see if placing a 5x5 block on the 13x13 board is a valid move
bool BlockSudoku::CheckIfValidMove(int x, int y, MatrixXi ablock, MatrixXi board)
{
    if(x < 0 || x >= 9) {
        return false;
    }
    if(y < 0 || y >= 9) {
        return false;
    }

    MatrixXi newBoard = board;
    newBoard.block(x, y, 5, 5) += ablock;
    if(newBoard.maxCoeff() > 1) {
        return false;
    }

    return true;
}

// Places a 5x5 block on the 13x13 board. This mutates the board.
bool BlockSudoku::PlaceBlock(int x, int y, MatrixXi block, MatrixXi* board)
{
    return false;
}

// Clears the board. This mutates the board.
int BlockSudoku::ClearBlocksAndScore(MatrixXi* board)
{
    return 0;
}