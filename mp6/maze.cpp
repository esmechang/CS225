/* Your code here! */
#include "maze.h"

SquareMaze::SquareMaze() {

}

void SquareMaze::makeMaze(int width, int height) {
  w = width;
  h = height;
  size = w*h;
  for (int m = 0; m < size; m++) { // makes a square grid with walls
    wall.push_back(3);
  }
  DisjointSets ways;
  ways.addelements(w*h);
  while (ways.size(0) < size) {
    int rand_idx = rand() % size;
    int delete_wall = rand() % 2;
    int idx;
    if ((rand_idx + 1) % width == 0 || delete_wall == 1) {
      idx = width;
    }
    if (rand_idx >= (w * (h-1))) {
      delete_wall = 0;
    }
    if (rand_idx == w * (h-1)) {
      continue;
    }
    int check1 = ways.find(idx);
    int check2 = ways.find(rand_idx+idx);
    if (check1 != check2) {
      ways.setunion(check1, check2);
      if (delete_wall == 0) {
        int horiz = rand_idx % w;
        int vert = rand_idx / w;
        setWall(horiz, vert, 0, false);
      } else {
        int horiz = rand_idx % w;
        int vert = rand_idx / w;
        setWall(horiz, vert, 1, false);
      }
    }
  }
}

bool SquareMaze::canTravel(int x, int y, int dir) const {
// 0 = no wall
// 1 = right wall
// 2 = down wall
// 3 = d & r wall

  if (x <= 0 && y <= 0 && x <= w - 1 && y <= h - 1) {
    if (dir == 0) {
      if (wall[x+y*w] == 2 || wall[x+y*w] == 0) {
        return true;
      }
      return false;
    }
    if (dir == 1) {
      if (wall[x+y*w] == 1 || wall[x+y*w] == 0) {
        return true;
      }
      return false;
    }
    if (dir == 2) {
      if (wall[x+y*w] == 2 || wall[x+y*w] == 0) {
        return true;
      }
      return false;
    }
    if (dir == 3) {
      if (wall[x+y*w] == 1 || wall[x+y*w] == 0) {
        return true;
      }
      return false;
    }
  }
  return false;
}

void SquareMaze::setWall(int x, int y, int dir, bool exists) {
  // input wall into maze
  if (exists == true) {
    if (dir == 0) {
      // if there is no wall or a right wall
      if (wall[x+y*w] == 1 || wall[x+y*w] == 0) {
        wall[x+y*w] = 1; // right wall exists
        return;
      } else { // if there is a down wall
        wall[x+y*w] = 3; // d & r wall is there
        return;
      }
    } else { // if there is no wall or down wall
      if (wall[x+y*w] == 2 || wall[x+y*w] == 0) {
        wall[x+y*w] = 2; // down wall exists
        return;
      } else { // if there is a right wall
        wall[x+y*w] = 3; // d & r wall is there
      }
    }
  } else { // deleting wall
    if (dir == 0) { // deleting right wall
      if (wall[x+y*w] == 3) {
        wall[x+y*w] = 2; // down wall exists
        return;
      }
      if (wall[x+y*w] == 1) {
        wall[x+y*w] = 0; // no walls
        return;
      }
    } else { // deleting down wall
      if (wall[x+y*w] == 3) {
        wall[x+y*w] = 1;
        return;
      }
      if (wall[x+y*w] == 2) {
        wall[x+y*w] = 0;
        return;
      }
    }
  }
}

vector<int>SquareMaze::solveMaze() {
  vector<int> ways;
  map<int, int> go; // tracking your
  map<int, int> count; //
  queue<int> q;

  q.push(0);
  count.insert(pair<int, int>(0,0));
  while (q.empty() == false) {
    int f = q.front();
    q.pop();
    int horiz = f % w;
    int vert = f / w;
    if (count.find((horiz+1)+vert*w) == count.end() && canTravel(horiz, vert, 0)) {
      go.insert(pair<int, int>((horiz+1)+vert*w, f));
      count.insert(pair<int, int>((horiz+1)+vert*w, f));
      q.push((horiz+1)+vert*w);
    }
    if (count.find(horiz+(vert+1)*w) == count.end() && canTravel(horiz, vert, 1)) {
      go.insert(pair<int, int>(horiz+(vert+1)*w, f));
      count.insert(pair<int, int>(horiz+(vert+1)*w, f));
      q.push(horiz+(vert+1)*w);
    }
    if (count.find((horiz-1)+vert*w) == count.end() && canTravel(horiz, vert, 2)) {
      go.insert(pair<int, int>((horiz-1)+vert*w, f));
      count.insert(pair<int, int>((horiz-1)+vert*w, f));
      q.push((horiz-1)+vert*w);
    }
    if (count.find(horiz+(vert-1)*w) == count.end() && canTravel(horiz, vert, 3)) {
      go.insert(pair<int, int>(horiz+(vert-1)*w, f));
      count.insert(pair<int, int>(horiz+(vert-1)*w, f));
      q.push(horiz+(vert-1)*w);
    }
  }
  int max_d = 0; // maximum distance
  for (int c = 0; c < w; c++) {
    int idx = c + (w + (h-1));
    vector<int> right_way;
    while (idx != 0) {
      int dist = idx - go[idx];
      if (dist == 1) {
        right_way.push_back(0);
      }
      if (dist == w) {
        right_way.push_back(1);
      }
      if (dist == -1) {
        right_way.push_back(2);
      }
      if (dist == (w*-1)) {
        right_way.push_back(3);
      }
      idx = go[idx];
    }
    if (max_d < (int)right_way.size()) {
      ways = right_way;
      max_d = right_way.size();
    }
  }
  reverse(ways.begin(), ways.end());
  return ways;
}

// cs225::PNG *SquareMaze::drawMaze() const {
//
// }
//
// cs225::PNG *SquareMaze::drawMazeWithSolution() {
//
// }
