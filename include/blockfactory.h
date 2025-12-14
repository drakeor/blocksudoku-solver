#ifndef _BLOCKFACTORY_H_
#define _BLOCKFACTORY_H_

#include <vector>
#include  <random>
#include  <iterator>
#include <Eigen/Dense>

class BlockFactory
{
public:
    std::vector<Eigen::MatrixXi> GetBlockList();
    std::vector<Eigen::MatrixXi> GenerateRandomBlocks(int count);
    BlockFactory();
private:
    void PopulateBlockList();
    std::vector<Eigen::MatrixXi> blockList;
    std::random_device rd;
    std::mt19937 mtgen;
};

#endif