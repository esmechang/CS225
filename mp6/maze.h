/* Your code here! */
#pragma once

#include <cmath>
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <queue>
#include <map>
#include <math.h>
#include "dsets.h"
#include "cs225/PNG.h"
#include "cs225/HSLAPixel.h"

using namespace std;

class SquareMaze {
public:
  SquareMaze();
  void makeMaze(int width, int height);
  bool canTravel(int x, int y, int dir) const;
  void setWall(int x, int y, int dir, bool exists);
  vector<int>solveMaze();
  cs225::PNG *drawMaze() const;
  cs225::PNG *drawMazeWithSolution();
  vector<int> Down;
  vector<int> Right;
private:
  int width_; // width
  int height_; // height
  int size_;
};
