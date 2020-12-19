#define  CATCH_CONFIG_RUNNER

#include "catch.hpp"

#include "blocksudoku.h"
#include <iostream>
#include <vector>

using namespace Eigen;
using namespace std;

#define INFO WARN

TEST_CASE( "New Board", "[blocksudoku]" ) {
    MatrixXi board = BlockSudoku::NewBoard();
    REQUIRE( board.cols() == BOARD_SIZE );
    REQUIRE( board.rows() == BOARD_SIZE );
    INFO(board);
}


TEST_CASE( "Check If Valid Move 1", "[blocksudoku]" ) {
    // Run it twice to make sure the board isn't mutated
    MatrixXi board = BlockSudoku::NewBoard();
    MatrixXi block(5, 5);
    block << 1,1,1,1,1,
             0,0,0,0,0,
             0,0,0,0,0,
             0,0,0,0,0,
             0,0,0,0,0;
    bool result = BlockSudoku::CheckIfValidMove(0, 0, block, board);
    bool result2 = BlockSudoku::CheckIfValidMove(0, 0, block, board);
    REQUIRE( result == true );
    REQUIRE( result2 == true );
    INFO(board);
    INFO(block);
}

TEST_CASE( "Check If Valid Move 2", "[blocksudoku]" ) {
    // This should fail
    MatrixXi board = BlockSudoku::NewBoard();
    MatrixXi block(5, 5);
    block << 1,1,1,1,1,
             0,0,0,0,0,
             0,0,0,0,0,
             0,0,0,0,0,
             0,0,0,0,0;
    INFO(board);
    INFO(block);
    bool result = BlockSudoku::CheckIfValidMove(9, 9, block, board);
    bool result2 = BlockSudoku::CheckIfValidMove(2, 7, block, board);
    REQUIRE( result == false );
    REQUIRE( result2 == false );
    
}

TEST_CASE( "Check If Valid Move 3", "[blocksudoku]" ) {
    // This tests the edges
    MatrixXi board = BlockSudoku::NewBoard();
    MatrixXi block(5, 5);
    block << 1,1,1,1,1,
             1,0,0,0,1,
             1,0,0,0,1,
             1,0,0,0,1,
             1,1,1,1,1;
    INFO(board);
    INFO(block);
    bool result = BlockSudoku::CheckIfValidMove(0, 0, block, board);
    bool result2 = BlockSudoku::CheckIfValidMove(4, 4, block, board);
    bool result3 = BlockSudoku::CheckIfValidMove(5, 5, block, board);
    REQUIRE( result == true );
    REQUIRE( result2 == true );
    REQUIRE( result3 == false );
    
}