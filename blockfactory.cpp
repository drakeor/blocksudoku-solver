#include "blockfactory.h"
#include <Eigen/Dense>

#define BLOCKFACT_BLOCK_DIM 5

using namespace Eigen;
using namespace std;

vector<MatrixXi> BlockFactory::GetBlockList()
{
    vector<MatrixXi> blockList;

    /*MatrixXf print_message = [&](CommaInitializer* commaInit) 
    { 
        MatrixXf(BLOCKFACT_BLOCK_DIM, BLOCKFACT_BLOCK_DIM);
        newVector.push_back(newMatrix);
        return &newMatrix;
    };*/
    blockList.push_back(
        (MatrixXi(BLOCKFACT_BLOCK_DIM, BLOCKFACT_BLOCK_DIM) <<
            1,0,0,0,0,
            0,0,0,0,0,
            0,0,0,0,0,
            0,0,0,0,0,
            0,0,0,0,0).finished()
    );

    //newMatrix << 

    return blockList;
}