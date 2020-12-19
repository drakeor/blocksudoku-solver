#include "blocksudoku.h"

#include <cassert>

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
                //int* moveCell = &validMoves(x,y);
                //*moveCell = 1;
                validMoves(x,y) = 1;
            }
        }
    }
    return validMoves;
}

// Checks to see if there are any valid moves to place the 5x5 block on a 13x13 board
bool BlockSudoku::CheckGameOverState(vector<MatrixXi> block, MatrixXi board)
{
    if(block.size() == 0)
        return false;

    // If there's at least one valid move, game is still going
    for(int n=0;n<block.size();n++) {
        for(int x=0;x<9;x++) {
            for(int y=0;y<9;y++) {
                if(CheckIfValidMove(x, y, block[n], board)) {
                    return false;
                }
            }
        }
    }

    // No valid moves, game over
    return true;
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
    (*board).block(x, y, 5, 5) += block;
    assert(board->maxCoeff() == 1);
    return true;
}

// Clears the board. This mutates the board.
int BlockSudoku::ClearBlocksAndScore(MatrixXi* board)
{
    int score = 0;
    auto subBoard = board->block(0,0,9,9);

    // Take advantage of int truncuation for clearing rows and columns
    auto colWiseSums = subBoard.colwise().sum() / 9;
    auto expandedColWise = colWiseSums.replicate(9, 1);
    score += colWiseSums.sum();

    auto rowWiseSums = subBoard.rowwise().sum() / 9;
    auto expandedRowWise = rowWiseSums.replicate(1, 9);
    score += rowWiseSums.sum();

    // Now the fun part
    MatrixXi boardMask = MatrixXi::Zero(9,9);
    for(int i=0;i<3;i++) {
        for(int j=0;j<3;j++) {
            auto subMatrix = subBoard.block(i*3, j*3, 3, 3);
            int subMatrixScore = subMatrix.sum() / 9;
            if(subMatrixScore == 1) {
                score += subMatrixScore;
                boardMask.block(i*3, j*3, 3, 3) = MatrixXi::Ones(3, 3);
            }
        }
    }

    // Apply row and col sums to the mask
    boardMask += expandedColWise;
    boardMask += expandedRowWise;

    // Clip and invert the mask
    boardMask = boardMask.cwiseMin(1).cwiseMax(0);
    boardMask = MatrixXi::Ones(9,9) - boardMask;
    boardMask = boardMask.cwiseAbs();

    // Apply the board mask to the board
    board->block(0,0,9,9) = board->block(0,0,9,9).cwiseProduct(boardMask);

    return score * score;
}