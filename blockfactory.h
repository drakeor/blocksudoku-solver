#ifndef _BLOCKFACTORY_H_
#define _BLOCKFACTORY_H_

#include <vector>
#include <Eigen/Dense>

class BlockFactory
{
public:
    static std::vector<Eigen::MatrixXi> GetBlockList();
private:
    BlockFactory();
};

#endif