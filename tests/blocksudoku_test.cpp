#define  CATCH_CONFIG_RUNNER

#include "catch.hpp"

#include "blocksudoku.h"
#include <iostream>
#include <vector>

using namespace Eigen;
using namespace std;

TEST_CASE( "New Board", "[blocksudoku]" ) {
    MatrixXi board = BlockSudoku::NewBoard();
    REQUIRE( board.cols() == BOARD_SIZE );
    REQUIRE( board.rows() == BOARD_SIZE );
    INFO(board);
}


TEST_CASE( "Check If Valid Move 1", "[blocksudoku]" ) {
    // Makes sure board isn't mutated and orientated correctly (x and y are swapped than normal)
    MatrixXi board = BlockSudoku::NewBoard();
    MatrixXi block(5, 5);
    block << 1,1,1,1,1,
             0,0,0,0,0,
             0,0,0,0,0,
             0,0,0,0,0,
             0,0,0,0,0;
    bool result = BlockSudoku::CheckIfValidMove(0, 0, block, board);
    bool result2 = BlockSudoku::CheckIfValidMove(0, 0, block, board);
    bool result3 = BlockSudoku::CheckIfValidMove(2, 7, block, board);
    REQUIRE( result == true );
    REQUIRE( result2 == true );
    REQUIRE( result3 == false );
    INFO(board);
    INFO(block);
}

TEST_CASE( "Check If Valid Move 2", "[blocksudoku]" ) {
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

TEST_CASE( "Check all valid moves", "[blocksudoku]" ) {
    // This tests the edges
    MatrixXi board = BlockSudoku::NewBoard();
    
    MatrixXi block(5, 5);
    block << 1,1,0,0,0,
             1,1,0,0,0,
             0,0,0,0,0,
             0,0,0,0,0,
             0,0,0,0,0;

    MatrixXi block2(5, 5);
    block2 << 1,1,0,0,0,
             0,0,0,0,0,
             0,0,0,0,0,
             0,0,0,0,0,
             0,0,0,0,0;

    INFO(board);
    INFO(block);
    INFO(block2);

    MatrixXi result = BlockSudoku::GetAllValidMoves(block, board);
    MatrixXi result2 = BlockSudoku::GetAllValidMoves(block2, board);

    REQUIRE( result.sum() == 8*8 );
    REQUIRE( result2.sum() == 9*8 );
}

TEST_CASE( "Place Block", "[blocksudoku]" ) {
    // Make sure the board is mutated!
    MatrixXi board = BlockSudoku::NewBoard();
    MatrixXi block(5, 5);
    block << 1,1,1,1,1,
             1,1,1,1,1,
             1,1,1,1,1,
             1,1,1,1,1,
             1,1,1,1,1;
    bool result = BlockSudoku::PlaceBlock(2, 0, block, &board);
    REQUIRE( result == true );
    REQUIRE( board != BlockSudoku::NewBoard());
    INFO(board);
    INFO(block);
}

TEST_CASE( "Game Over State", "[blocksudoku]" ) {
    // Game over state should happen after we put the massive block down
    MatrixXi board = BlockSudoku::NewBoard();
    MatrixXi block(5, 5);
    block << 1,1,1,1,1,
             1,1,1,1,1,
             1,1,1,1,1,
             1,1,1,1,1,
             1,1,1,1,1;
    vector<MatrixXi> blockList;
    blockList.push_back(block);
    blockList.push_back(block);

    bool gameOverState = BlockSudoku::CheckGameOverState(blockList, board);
    bool result = BlockSudoku::PlaceBlock(2, 1, block, &board);
    bool gameOverState2 = BlockSudoku::CheckGameOverState(blockList, board);

    REQUIRE( gameOverState == false );
    REQUIRE( result == true);
    REQUIRE( gameOverState2 == true );

    INFO(board);
    INFO(block);
}


TEST_CASE( "Clear blocks and score 1", "[blocksudoku]" ) {
    // Test clearing the 3x3 blocks
    MatrixXi board = BlockSudoku::NewBoard();
    MatrixXi block(5, 5);
    block << 1,1,1,0,0,
             1,1,1,0,0,
             1,1,1,0,0,
             0,0,0,0,0,
             0,0,0,0,0;

    BlockSudoku::PlaceBlock(0, 0, block, &board);
    BlockSudoku::PlaceBlock(6, 6, block, &board);
    int score = BlockSudoku::ClearBlocksAndScore(&board);

    REQUIRE( score == 4 );
    REQUIRE( board == BlockSudoku::NewBoard() );

    INFO(board);
    INFO(block);
}

TEST_CASE( "Clear blocks and score 2", "[blocksudoku]" ) {
    // Test clearing columns
    MatrixXi board = BlockSudoku::NewBoard();
    MatrixXi block(5, 5);
    block << 1,0,0,0,0,
             1,0,0,0,0,
             1,0,0,0,0,
             0,0,0,0,0,
             0,0,0,0,0;

    BlockSudoku::PlaceBlock(0, 0, block, &board);
    BlockSudoku::PlaceBlock(3, 0, block, &board);
    BlockSudoku::PlaceBlock(6, 0, block, &board);
    int score = BlockSudoku::ClearBlocksAndScore(&board);

    REQUIRE( score == 1 );
    REQUIRE( board == BlockSudoku::NewBoard() );

    INFO(board);
    INFO(block);
}

TEST_CASE( "Clear blocks and score 3", "[blocksudoku]" ) {
    // Test clearing rows
    MatrixXi board = BlockSudoku::NewBoard();
    MatrixXi block(5, 5);
    block << 1,1,1,0,0,
             0,0,0,0,0,
             0,0,0,0,0,
             0,0,0,0,0,
             0,0,0,0,0;

    BlockSudoku::PlaceBlock(0, 0, block, &board);
    BlockSudoku::PlaceBlock(0, 3, block, &board);
    BlockSudoku::PlaceBlock(0, 6, block, &board);
    int score = BlockSudoku::ClearBlocksAndScore(&board);

    REQUIRE( score == 1 );
    REQUIRE( board == BlockSudoku::NewBoard() );

    INFO(board);
    INFO(block);
}

TEST_CASE( "Clear blocks and score 4", "[blocksudoku]" ) {
    // Test not accidently clearing
    MatrixXi board = BlockSudoku::NewBoard();
    MatrixXi board2 = BlockSudoku::NewBoard();
    MatrixXi block(5, 5);
    block << 1,1,1,1,1,
             1,0,1,0,0,
             1,1,1,0,0,
             0,0,1,0,0,
             0,0,1,0,0;

    BlockSudoku::PlaceBlock(0, 0, block, &board);
    BlockSudoku::PlaceBlock(0, 0, block, &board2);

    int score = BlockSudoku::ClearBlocksAndScore(&board);

    REQUIRE( score == 0 );
    REQUIRE( board == board2 );

    INFO(board);
    INFO(board2);
    INFO(block);
}

TEST_CASE( "Clear blocks and score 5", "[blocksudoku]" ) {
    // Test clearing the 3x3 blocks
    MatrixXi board = BlockSudoku::NewBoard();
    MatrixXi block(5, 5);
    block << 1,1,1,0,0,
             1,1,1,0,0,
             1,1,1,0,0,
             0,0,0,0,0,
             0,0,0,0,0;

    BlockSudoku::PlaceBlock(0, 0, block, &board);
    BlockSudoku::PlaceBlock(0, 3, block, &board);
    BlockSudoku::PlaceBlock(0, 6, block, &board);

    BlockSudoku::PlaceBlock(3, 0, block, &board);
    BlockSudoku::PlaceBlock(3, 3, block, &board);
    BlockSudoku::PlaceBlock(3, 6, block, &board);

    BlockSudoku::PlaceBlock(6, 0, block, &board);
    BlockSudoku::PlaceBlock(6, 3, block, &board);
    BlockSudoku::PlaceBlock(6, 6, block, &board);

    int score = BlockSudoku::ClearBlocksAndScore(&board);

    REQUIRE( score == 27*27);
    REQUIRE( board == BlockSudoku::NewBoard() );

    INFO(board);
    INFO(block);
}