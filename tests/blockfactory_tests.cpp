#define  CATCH_CONFIG_RUNNER

#include "blockfactory.h"

#include <iostream>
#include "catch.hpp"

using namespace Eigen;
using namespace std;

TEST_CASE( "Get Block List", "[blockfactory]" ) {
    BlockFactory blockFactory;
    vector<MatrixXi> block_list = blockFactory.GetBlockList();
    REQUIRE( block_list.size() > 0 );
    INFO(block_list[0]);
}

TEST_CASE( "Generate 3 random blocks", "[blockfactory]" ) {
    BlockFactory blockFactory;
    vector<MatrixXi> block_list = blockFactory.GenerateRandomBlocks(3);
    REQUIRE( block_list.size() == 3 );
    INFO(block_list[0]);
    INFO(block_list[1]);
    INFO(block_list[2]);
}