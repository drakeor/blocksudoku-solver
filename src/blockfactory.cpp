#include "blockfactory.h"
#include <Eigen/Dense>

#include <algorithm>
#include <iostream>
#include <random>
#include <vector>

#define BLOCKFACT_BLOCK_DIM 5

using namespace Eigen;
using namespace std;

vector<MatrixXi> BlockFactory::GetBlockList()
{
    return blockList;
}

vector<MatrixXi> BlockFactory::GenerateRandomBlocks(int elements)
{
    vector<MatrixXi> out;
    sample(
        blockList.begin(),
        blockList.end(),
        std::back_inserter(out),
        elements,
        std::mt19937{std::random_device{}()}
    );
    return out;
}

BlockFactory::BlockFactory()
{
    PopulateBlockList();
}

void BlockFactory::PopulateBlockList()
{
    blockList.clear();

    // 1 Blocks
    blockList.push_back(
        (MatrixXi(BLOCKFACT_BLOCK_DIM, BLOCKFACT_BLOCK_DIM) <<
            1,0,0,0,0,
            0,0,0,0,0,
            0,0,0,0,0,
            0,0,0,0,0,
            0,0,0,0,0
        ).finished()
    );

    // 2 Blocks
    blockList.push_back(
    (MatrixXi(BLOCKFACT_BLOCK_DIM, BLOCKFACT_BLOCK_DIM) <<
        1,1,0,0,0,
        0,0,0,0,0,
        0,0,0,0,0,
        0,0,0,0,0,
        0,0,0,0,0
        ).finished()
    );
    blockList.push_back(
        (MatrixXi(BLOCKFACT_BLOCK_DIM, BLOCKFACT_BLOCK_DIM) <<
            1,0,0,0,0,
            1,0,0,0,0,
            0,0,0,0,0,
            0,0,0,0,0,
            0,0,0,0,0
        ).finished()
    );
    blockList.push_back(
        (MatrixXi(BLOCKFACT_BLOCK_DIM, BLOCKFACT_BLOCK_DIM) <<
            1,0,0,0,0,
            0,1,0,0,0,
            0,0,0,0,0,
            0,0,0,0,0,
            0,0,0,0,0
        ).finished()
    );
    blockList.push_back(
        (MatrixXi(BLOCKFACT_BLOCK_DIM, BLOCKFACT_BLOCK_DIM) <<
            0,1,0,0,0,
            1,0,0,0,0,
            0,0,0,0,0,
            0,0,0,0,0,
            0,0,0,0,0
        ).finished()
    );

    // 3 Blocks
    blockList.push_back(
        (MatrixXi(BLOCKFACT_BLOCK_DIM, BLOCKFACT_BLOCK_DIM) <<
            1,0,0,0,0,
            1,0,0,0,0,
            1,0,0,0,0,
            0,0,0,0,0,
            0,0,0,0,0).finished()
    );
    blockList.push_back(
        (MatrixXi(BLOCKFACT_BLOCK_DIM, BLOCKFACT_BLOCK_DIM) <<
            1,1,1,0,0,
            0,0,0,0,0,
            0,0,0,0,0,
            0,0,0,0,0,
            0,0,0,0,0).finished()
    );
    blockList.push_back(
        (MatrixXi(BLOCKFACT_BLOCK_DIM, BLOCKFACT_BLOCK_DIM) <<
            1,1,0,0,0,
            1,0,0,0,0,
            0,0,0,0,0,
            0,0,0,0,0,
            0,0,0,0,0).finished()
    );
    blockList.push_back(
        (MatrixXi(BLOCKFACT_BLOCK_DIM, BLOCKFACT_BLOCK_DIM) <<
            1,1,0,0,0,
            0,1,0,0,0,
            0,0,0,0,0,
            0,0,0,0,0,
            0,0,0,0,0).finished()
    );
    blockList.push_back(
        (MatrixXi(BLOCKFACT_BLOCK_DIM, BLOCKFACT_BLOCK_DIM) <<
            0,1,0,0,0,
            1,1,0,0,0,
            0,0,0,0,0,
            0,0,0,0,0,
            0,0,0,0,0).finished()
    );
    blockList.push_back(
        (MatrixXi(BLOCKFACT_BLOCK_DIM, BLOCKFACT_BLOCK_DIM) <<
            1,0,0,0,0,
            1,1,0,0,0,
            0,0,0,0,0,
            0,0,0,0,0,
            0,0,0,0,0).finished()
    );
    blockList.push_back(
        (MatrixXi(BLOCKFACT_BLOCK_DIM, BLOCKFACT_BLOCK_DIM) <<
            1,0,0,0,0,
            0,1,0,0,0,
            0,0,1,0,0,
            0,0,0,0,0,
            0,0,0,0,0).finished()
    );
    blockList.push_back(
        (MatrixXi(BLOCKFACT_BLOCK_DIM, BLOCKFACT_BLOCK_DIM) <<
            0,0,1,0,0,
            0,1,0,0,0,
            1,0,0,0,0,
            0,0,0,0,0,
            0,0,0,0,0).finished()
    );

    
        // 4 blocks
    blockList.push_back(
        (MatrixXi(BLOCKFACT_BLOCK_DIM, BLOCKFACT_BLOCK_DIM) <<
            1,0,0,0,0,
            1,0,0,0,0,
            1,0,0,0,0,
            1,0,0,0,0,
            0,0,0,0,0).finished()
    );
    blockList.push_back(
        (MatrixXi(BLOCKFACT_BLOCK_DIM, BLOCKFACT_BLOCK_DIM) <<
            1,1,1,1,0,
            0,0,0,0,0,
            0,0,0,0,0,
            0,0,0,0,0,
            0,0,0,0,0).finished()
    );
    blockList.push_back(
        (MatrixXi(BLOCKFACT_BLOCK_DIM, BLOCKFACT_BLOCK_DIM) <<
            1,0,0,0,0,
            1,0,0,0,0,
            1,1,0,0,0,
            0,0,0,0,0,
            0,0,0,0,0).finished()
    );
    blockList.push_back(
        (MatrixXi(BLOCKFACT_BLOCK_DIM, BLOCKFACT_BLOCK_DIM) <<
            0,0,1,0,0,
            1,1,1,0,0,
            0,0,0,0,0,
            0,0,0,0,0,
            0,0,0,0,0).finished()
    );
    blockList.push_back(
        (MatrixXi(BLOCKFACT_BLOCK_DIM, BLOCKFACT_BLOCK_DIM) <<
            1,1,0,0,0,
            0,1,0,0,0,
            0,1,0,0,0,
            0,0,0,0,0,
            0,0,0,0,0).finished()
    );
    blockList.push_back(
        (MatrixXi(BLOCKFACT_BLOCK_DIM, BLOCKFACT_BLOCK_DIM) <<
            1,1,1,0,0,
            1,0,0,0,0,
            0,0,0,0,0,
            0,0,0,0,0,
            0,0,0,0,0).finished()
    );
    blockList.push_back(
        (MatrixXi(BLOCKFACT_BLOCK_DIM, BLOCKFACT_BLOCK_DIM) <<
            1,1,0,0,0,
            0,1,1,0,0,
            0,0,0,0,0,
            0,0,0,0,0,
            0,0,0,0,0).finished()
    );
    blockList.push_back(
        (MatrixXi(BLOCKFACT_BLOCK_DIM, BLOCKFACT_BLOCK_DIM) <<
            0,1,0,0,0,
            1,1,0,0,0,
            1,0,0,0,0,
            0,0,0,0,0,
            0,0,0,0,0).finished()
    );
    blockList.push_back(
        (MatrixXi(BLOCKFACT_BLOCK_DIM, BLOCKFACT_BLOCK_DIM) <<
            1,0,0,0,0,
            1,1,0,0,0,
            0,1,0,0,0,
            0,0,0,0,0,
            0,0,0,0,0).finished()
    );
    blockList.push_back(
        (MatrixXi(BLOCKFACT_BLOCK_DIM, BLOCKFACT_BLOCK_DIM) <<
            0,1,1,0,0,
            1,1,0,0,0,
            0,0,0,0,0,
            0,0,0,0,0,
            0,0,0,0,0).finished()
    );
    blockList.push_back(
        (MatrixXi(BLOCKFACT_BLOCK_DIM, BLOCKFACT_BLOCK_DIM) <<
            1,1,0,0,0,
            1,1,0,0,0,
            0,0,0,0,0,
            0,0,0,0,0,
            0,0,0,0,0).finished()
    );
    blockList.push_back(
        (MatrixXi(BLOCKFACT_BLOCK_DIM, BLOCKFACT_BLOCK_DIM) <<
            0,1,0,0,0,
            1,1,1,0,0,
            0,0,0,0,0,
            0,0,0,0,0,
            0,0,0,0,0).finished()
    );
    blockList.push_back(
        (MatrixXi(BLOCKFACT_BLOCK_DIM, BLOCKFACT_BLOCK_DIM) <<
            1,0,0,0,0,
            1,1,0,0,0,
            1,0,0,0,0,
            0,0,0,0,0,
            0,0,0,0,0).finished()
    );
    blockList.push_back(
        (MatrixXi(BLOCKFACT_BLOCK_DIM, BLOCKFACT_BLOCK_DIM) <<
            1,1,1,0,0,
            0,1,0,0,0,
            0,0,0,0,0,
            0,0,0,0,0,
            0,0,0,0,0).finished()
    );
    blockList.push_back(
        (MatrixXi(BLOCKFACT_BLOCK_DIM, BLOCKFACT_BLOCK_DIM) <<
            0,1,0,0,0,
            1,1,0,0,0,
            0,1,0,0,0,
            0,0,0,0,0,
            0,0,0,0,0).finished()
    );
    blockList.push_back(
        (MatrixXi(BLOCKFACT_BLOCK_DIM, BLOCKFACT_BLOCK_DIM) <<
            0,1,0,0,0,
            0,1,0,0,0,
            1,1,0,0,0,
            0,0,0,0,0,
            0,0,0,0,0).finished()
    );
    blockList.push_back(
        (MatrixXi(BLOCKFACT_BLOCK_DIM, BLOCKFACT_BLOCK_DIM) <<
            1,1,1,0,0,
            0,0,1,0,0,
            0,0,0,0,0,
            0,0,0,0,0,
            0,0,0,0,0).finished()
    );
    blockList.push_back(
        (MatrixXi(BLOCKFACT_BLOCK_DIM, BLOCKFACT_BLOCK_DIM) <<
            1,1,0,0,0,
            1,0,0,0,0,
            1,0,0,0,0,
            0,0,0,0,0,
            0,0,0,0,0).finished()
    );
    blockList.push_back(
        (MatrixXi(BLOCKFACT_BLOCK_DIM, BLOCKFACT_BLOCK_DIM) <<
            1,0,0,0,0,
            1,1,1,0,0,
            0,0,0,0,0,
            0,0,0,0,0,
            0,0,0,0,0).finished()
    );
        
        // 5 blocks
    blockList.push_back(
        (MatrixXi(BLOCKFACT_BLOCK_DIM, BLOCKFACT_BLOCK_DIM) <<
            1,0,0,0,0,
            1,0,0,0,0,
            1,0,0,0,0,
            1,0,0,0,0,
            1,0,0,0,0).finished()
    );
    blockList.push_back(
        (MatrixXi(BLOCKFACT_BLOCK_DIM, BLOCKFACT_BLOCK_DIM) <<
            1,1,1,1,1,
            0,0,0,0,0,
            0,0,0,0,0,
            0,0,0,0,0,
            0,0,0,0,0).finished()
    );
    blockList.push_back(
        (MatrixXi(BLOCKFACT_BLOCK_DIM, BLOCKFACT_BLOCK_DIM) <<
            1,0,0,0,0,
            1,0,0,0,0,
            1,0,0,0,0,
            1,1,0,0,0,
            0,0,0,0,0).finished()
    );
    blockList.push_back(
        (MatrixXi(BLOCKFACT_BLOCK_DIM, BLOCKFACT_BLOCK_DIM) <<
            0,0,0,1,0,
            1,1,1,1,0,
            0,0,0,0,0,
            0,0,0,0,0,
            0,0,0,0,0).finished()
    );
    blockList.push_back(
        (MatrixXi(BLOCKFACT_BLOCK_DIM, BLOCKFACT_BLOCK_DIM) <<
            1,1,0,0,0,
            0,1,0,0,0,
            0,1,0,0,0,
            0,1,0,0,0,
            0,0,0,0,0).finished()
    );
    blockList.push_back(
        (MatrixXi(BLOCKFACT_BLOCK_DIM, BLOCKFACT_BLOCK_DIM) <<
            1,1,1,1,0,
            1,0,0,0,0,
            0,0,0,0,0,
            0,0,0,0,0,
            0,0,0,0,0).finished()
    );
    blockList.push_back(
        (MatrixXi(BLOCKFACT_BLOCK_DIM, BLOCKFACT_BLOCK_DIM) <<
            1,1,1,0,0,
            1,0,0,0,0,
            1,0,0,0,0,
            0,0,0,0,0,
            0,0,0,0,0).finished()
    );
    blockList.push_back(
        (MatrixXi(BLOCKFACT_BLOCK_DIM, BLOCKFACT_BLOCK_DIM) <<
            1,1,1,0,0,
            0,0,1,0,0,
            0,0,1,0,0,
            0,0,0,0,0,
            0,0,0,0,0).finished()
    );
    blockList.push_back(
        (MatrixXi(BLOCKFACT_BLOCK_DIM, BLOCKFACT_BLOCK_DIM) <<
            1,0,0,0,0,
            1,0,0,0,0,
            1,1,1,0,0,
            0,0,0,0,0,
            0,0,0,0,0).finished()
    );
    blockList.push_back(
        (MatrixXi(BLOCKFACT_BLOCK_DIM, BLOCKFACT_BLOCK_DIM) <<
            0,0,1,0,0,
            0,0,1,0,0,
            1,1,1,0,0,
            0,0,0,0,0,
            0,0,0,0,0).finished()
    );
    blockList.push_back(
        (MatrixXi(BLOCKFACT_BLOCK_DIM, BLOCKFACT_BLOCK_DIM) <<
            0,1,0,0,0,
            0,1,0,0,0,
            0,1,0,0,0,
            1,1,0,0,0,
            0,0,0,0,0).finished()
    );
    blockList.push_back(
        (MatrixXi(BLOCKFACT_BLOCK_DIM, BLOCKFACT_BLOCK_DIM) <<
            1,0,0,0,0,
            1,1,1,1,0,
            0,0,0,0,0,
            0,0,0,0,0,
            0,0,0,0,0).finished()
    );
    blockList.push_back(
        (MatrixXi(BLOCKFACT_BLOCK_DIM, BLOCKFACT_BLOCK_DIM) <<
            1,1,0,0,0,
            1,0,0,0,0,
            1,0,0,0,0,
            1,0,0,0,0,
            0,0,0,0,0).finished()
    );
    blockList.push_back(
        (MatrixXi(BLOCKFACT_BLOCK_DIM, BLOCKFACT_BLOCK_DIM) <<
            1,1,1,1,0,
            0,0,0,1,0,
            0,0,0,0,0,
            0,0,0,0,0,
            0,0,0,0,0).finished()
    );
    blockList.push_back(
        (MatrixXi(BLOCKFACT_BLOCK_DIM, BLOCKFACT_BLOCK_DIM) <<
            1,1,0,0,0,
            0,1,0,0,0,
            0,1,1,0,0,
            0,0,0,0,0,
            0,0,0,0,0).finished()
    );
    blockList.push_back(
        (MatrixXi(BLOCKFACT_BLOCK_DIM, BLOCKFACT_BLOCK_DIM) <<
            0,0,1,0,0,
            1,1,1,0,0,
            1,0,0,0,0,
            0,0,0,0,0,
            0,0,0,0,0).finished()
    );
    blockList.push_back(
        (MatrixXi(BLOCKFACT_BLOCK_DIM, BLOCKFACT_BLOCK_DIM) <<
            0,1,1,0,0,
            0,1,0,0,0,
            1,1,0,0,0,
            0,0,0,0,0,
            0,0,0,0,0).finished()
    );
    blockList.push_back(
        (MatrixXi(BLOCKFACT_BLOCK_DIM, BLOCKFACT_BLOCK_DIM) <<
            1,0,0,0,0,
            1,1,1,0,0,
            0,0,1,0,0,
            0,0,0,0,0,
            0,0,0,0,0).finished()
    );
    blockList.push_back(
        (MatrixXi(BLOCKFACT_BLOCK_DIM, BLOCKFACT_BLOCK_DIM) <<
            0,1,0,0,0,
            1,1,1,0,0,
            0,1,0,0,0,
            0,0,0,0,0,
            0,0,0,0,0).finished()
    );
    blockList.push_back(
        (MatrixXi(BLOCKFACT_BLOCK_DIM, BLOCKFACT_BLOCK_DIM) <<
            1,1,1,0,0,
            0,1,0,0,0,
            0,1,0,0,0,
            0,0,0,0,0,
            0,0,0,0,0).finished()
    );
    blockList.push_back(
        (MatrixXi(BLOCKFACT_BLOCK_DIM, BLOCKFACT_BLOCK_DIM) <<
            1,0,0,0,0,
            1,1,1,0,0,
            1,0,0,0,0,
            0,0,0,0,0,
            0,0,0,0,0).finished()
    );
    blockList.push_back(
        (MatrixXi(BLOCKFACT_BLOCK_DIM, BLOCKFACT_BLOCK_DIM) <<
            0,1,0,0,0,
            0,1,0,0,0,
            1,1,1,0,0,
            0,0,0,0,0,
            0,0,0,0,0).finished()
    );
    blockList.push_back(
        (MatrixXi(BLOCKFACT_BLOCK_DIM, BLOCKFACT_BLOCK_DIM) <<
            0,0,1,0,0,
            1,1,1,0,0,
            0,0,1,0,0,
            0,0,0,0,0,
            0,0,0,0,0).finished()
    );
    blockList.push_back(
        (MatrixXi(BLOCKFACT_BLOCK_DIM, BLOCKFACT_BLOCK_DIM) <<
            1,1,1,0,0,
            1,0,1,0,0,
            0,0,0,0,0,
            0,0,0,0,0,
            0,0,0,0,0).finished()
    );
    blockList.push_back(
        (MatrixXi(BLOCKFACT_BLOCK_DIM, BLOCKFACT_BLOCK_DIM) <<
            1,1,0,0,0,
            1,0,0,0,0,
            1,1,0,0,0,
            0,0,0,0,0,
            0,0,0,0,0).finished()
    );
    blockList.push_back(
        (MatrixXi(BLOCKFACT_BLOCK_DIM, BLOCKFACT_BLOCK_DIM) <<
            1,0,1,0,0,
            1,1,1,0,0,
            0,0,0,0,0,
            0,0,0,0,0,
            0,0,0,0,0).finished()
    );
    blockList.push_back(
        (MatrixXi(BLOCKFACT_BLOCK_DIM, BLOCKFACT_BLOCK_DIM) <<
            1,1,0,0,0,
            0,1,0,0,0,
            1,1,0,0,0,
            0,0,0,0,0,
            0,0,0,0,0).finished()
    );

}