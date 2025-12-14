#include <iostream>
#include <Eigen/Dense>
 
#include "blockfactory.h"
#include "blocksudoku.h"
#include "game.h"

#include <atomic>
#include <memory>
#include <mutex>

using namespace std;
using namespace Eigen;

int main()
{
  vector<int> scores;
  int gamesToPlay = 10;
  for(int i=0;i<gamesToPlay;i++)
  {
    Game game(10, 1000, true);
    int score = game.RunGame();
    scores.push_back(score);
  }
  
  cout << "Scores: ";
  for(int j=0;j<scores.size();j++) 
  {
    cout << scores[j] << " ";
  }
  cout << endl;

  return 0;
}