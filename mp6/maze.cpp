/* Your code here! */
#include "maze.h"
#include "cs225/HSLAPixel.h"
#include "cs225/PNG.h"
using namespace cs225;

// makes empty maze
SquareMaze::SquareMaze() {

}

// makes new maze with width and height variables
void SquareMaze::makeMaze(int width, int height) {
width_ = width;
height_ = height;
size_ = height_ * width_;
for(int i=0; i<size_; i++){
  Down.push_back(1);
  Right.push_back(1);
  }
DisjointSets path;
path.addelements(size_);
int i = 0;
while(i<size_-1){
  int random_wall = rand()%2;
  int random_x = rand()%width_;
  int random_y = rand()%height_;
  if(random_wall){
    if(random_x < width_ -1 && Right[random_x+random_y*width_] && path.find(random_x+random_y*width_) != path.find(random_x+random_y*width_+1)){
      Right[random_x+random_y*width_] = 0;
      path.setunion(path.find(random_x+random_y*width_), path.find(random_x+random_y*width_+1));
      i++;
    }
  }
  else{
    if(random_y < height_-1 && Down[random_x+random_y*width_]&&path.find(random_x+random_y*width_) != path.find(random_x+(random_y+1)*width_)){
      Down[random_x+random_y*width_] = 0;
      path.setunion(path.find(random_x+random_y*width_), path.find(random_x+(1+random_y)*width_));
      i++;
    }
  }
}
}

// whether it can go to a coordinate or not in the maze
bool SquareMaze::canTravel(int x, int y, int dir) const {
// 0 = no walls
// 1 = right wall
// 2 = down wall
// 3 = down and right walls
if (dir == 0) return !(Right[x+y*width_]);

if (dir == 1) return !(Down[x+y*width_]);
if (dir == 2){
  if (x == 0) return false;
  else return !(Right[x-1+y*width_]);
}if (dir == 3){
  if (y == 0)
    return false;
  else
    return !(Down[x + (y-1) * width_]);}

return false;
}

// if wall exists or not
void SquareMaze::setWall(int x, int y, int dir, bool exists) {
  // 0 = no walls
  // 1 = right wall
  // 2 = down wall
  // 3 = down and right walls
  if (dir==0){
    if(exists == true)
  Right[x+y*width_] = 1;
  else Right[x+y*width_] = 0;
}
  if(dir==1){
    if(exists == true)
    Down[x+y*width_] = 1;
    else Down[x+y*width_] = 0;
  }
}

// solves da maze !! (BFS)
vector<int> SquareMaze::solveMaze() {
    vector<int> vect;
    vector<bool> yesno;
    map<int, int>mom;
    queue<int> q ;
    q.push(0);


    for(int i = 0; i< size_; i++)
    yesno.push_back(false);

    yesno[0] = true;

    while(!q.empty()){
      int temp = q.front();
      q.pop();
      int x = temp% width_;
      int y = temp/width_;
      if(y==height_-1)
      vect.push_back(temp);

      if(canTravel(x,y,0) && !yesno[temp+1]){
        mom.insert(pair<int,int>(temp+1, temp));
        yesno[temp+1] = true;
        q.push(temp+1);
      }
      if(canTravel(x,y,1) && !yesno[temp+width_]){
        mom.insert(pair<int,int>(temp+width_, temp));
        yesno[temp+width_] = true;
        q.push(temp+width_);
      }
      if(canTravel(x,y,2) && !yesno[temp-1]){
        mom.insert(pair<int,int>(temp-1, temp));
        yesno[temp-1] = true;
        q.push(temp-1);
      }
      if(canTravel(x,y,3) && !yesno[temp-width_]){
        mom.insert(pair<int,int>(temp-width_, temp));
        yesno[temp-width_] = true;
        q.push(temp-width_);
      }
    }
    vector<int>vect2;
    int temp = width_-1;
    while(vect[temp] == vect[temp-1]){
      temp = temp-1;}
      int temp2 = vect[temp];
      while(temp2!=0){
        int temp3 = mom[temp2];
        if(temp2 == temp3 +1)
        vect2.push_back(0);
        if(temp2 == temp3+width_)
        vect2.push_back(1);
        if(temp2==temp3-1)
        vect2.push_back(2);
        if(temp2==temp3-width_)
        vect2.push_back(3);
        temp2 = temp3;
      }
      reverse(vect2.begin(), vect2.end());
      return vect2;
    }

// draws da maze !! (no solution)
PNG* SquareMaze::drawMaze() const{
    PNG* maize = new PNG(width_*10+1, height_*10+1);

    for (int i = 0; i < height_*10+1; i++){
              HSLAPixel &pix = maize->getPixel(0, i);
              pix.h = 0;
              pix.s = 0;
              pix.l = 0;
            }

    for (int i = 10; i < width_*10+1; i++){
              HSLAPixel &pix = maize->getPixel(i, 0);
              pix.h = 0;
              pix.s = 0;
              pix.l = 0;
            }

    for (int x = 0; x < width_; x++){
        for (int y = 0; y < height_; y++){
              if (Right[x+y*width_]){
                  for (int i = 0; i < 11; i++){
                    HSLAPixel &pix = maize->getPixel(10*x+10, 10*y+i);
                    pix.h = 0;
                    pix.s = 0;
                    pix.l = 0;
                    }}
              if (Down[x+y*width_]){
                  for (int i = 0; i < 11; i++){
                    HSLAPixel&pix = maize->getPixel(10*x+i, 10*y+10);
                    pix.h = 0;
                    pix.s = 0;
                    pix.l = 0;
                    }}
              }}
          return maize;
    }

// draws da maze with solution !! (modifies PNG)    
PNG * SquareMaze::drawMazeWithSolution() {
  PNG * maize = drawMaze();
  vector<int> solved = solveMaze();
  int x = 5;
  int y = 5;
  for(unsigned i = 0; i<solved.size();i++){
    if(solved[i]==0){
      for(int i =0; i<10; i++){
        HSLAPixel & pix = maize->getPixel(x,y);
        pix.h = 0;
        pix.s = 1;
        pix.l = 0.5;
        pix.a = 1;
        x++;
      }
    }
    if(solved[i]==1){
      for(int i =0; i<10; i++){
        HSLAPixel & pix = maize->getPixel(x,y);
        pix.h = 0;
        pix.s = 1;
        pix.l = 0.5;
        pix.a = 1;
        y++;
      }
    }
    if(solved[i]==2){
      for(int i =0; i<10; i++){
        HSLAPixel & pix = maize->getPixel(x,y);
        pix.h = 0;
        pix.s = 1;
        pix.l = 0.5;
        pix.a = 1;
        x--;
      }
    }
    if(solved[i]==3){
      for(int i =0; i<10; i++){
        HSLAPixel & pix = maize->getPixel(x,y);
        pix.h = 0;
        pix.s = 1;
        pix.l = 0.5;
        pix.a = 1;
        y--;
      }
    }
  }
  HSLAPixel & pix = maize->getPixel(x,y);
  pix.h = 0;
  pix.s = 1;
  pix.l = 0.5;
  pix.a = 1;
  x-=4;
  y+=5;
  for(int i =0; i<9; i++){
    HSLAPixel & pix = maize->getPixel(x,y);
    pix.h = 0;
    pix.s = 0;
    pix.l = 1;
    pix.a = 1;
    x++;
  }
  return maize;
}
