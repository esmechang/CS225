/**
 * @file kdtree.cpp
 * Implementation of KDTree class.
 */

#include <utility>
#include <algorithm>

using namespace std;

template <int Dim>
bool KDTree<Dim>::smallerDimVal(const Point<Dim>& first,
                                const Point<Dim>& second, int curDim) const
{
    /**
     * @todo Implement this function!
     */

     bool result = false;
     if (first[curDim] < second[curDim]) { // if first is less than b, then true
       result = true;
     }
     if (first[curDim] > second[curDim]) { // if first is greater than b, then false
       result = false;
     }
     if (first[curDim] == second[curDim]) { // if first is equal to b, then true
       if (first < second) {
         result = true;
       }
     }
    return result;
}

template <int Dim>
bool KDTree<Dim>::shouldReplace(const Point<Dim>& target,
                                const Point<Dim>& currentBest,
                                const Point<Dim>& potential) const
{
    /**
     * @todo Implement this function!
     */
     bool result = false;
     int dims = Dim; // dimension of the compared points
     double dist1 = 0; // distance of currentBest
     double dist2 = 0; // distance of potential

     // calculate distance between the points
     for (int i = 0; i < dims; i++) {
       double a = currentBest[i] - target[i];
       a = a * a;
       double b = potential[i] - target[i];
       b = b * b;
       dist1 += a;
       dist2 += b;
     }
     // compare the distances
     if (dist2 < dist1) {
       result = true;
     }
     if (dist2 == dist1) {
       if (potential < currentBest) {
         result = true;
       }
     }
     return result;
}

// constructor
template <int Dim>
KDTree<Dim>::KDTree(const vector<Point<Dim>>& newPoints)
{
    /**
     * @todo Implement this function!
     */
     vec = newPoints;
     root = buildTree(vec, 0, vec.size()-1, 0);
     // if (newPoints.size() == 0) {
     //   size = 0;
     //   vec = 0;
     //   root = NULL;
     // } else {
     //   int dimen = 0;
     //   int length = newPoints.size();
     //   size = length;
     //   vec = newPoints;
     //   root = buildTree(newPoints, 0, length, root, dimen);
     // }
}

// builds tree from vector of unsorted points
template <int Dim>
typename KDTree<Dim>::KDTreeNode* KDTree<Dim>::buildTree(vector<Point<Dim>> & vec, int small, int large, int dimen) {
  if (small > large) { // base/end value
    return NULL;
  }
  int median = (small + large)/2; // median value
  smallestElm(vec, small, large, median, dimen);
  KDTreeNode *node = new KDTreeNode(vec[median]); // create new internal node
  dimen = (dimen+1)%Dim; //update dimension
  node->left = buildTree(vec, small, median-1, dimen); // create left subtree
  node->right = buildTree(vec, median+1, large, dimen); // create right subtree
  return node;
}

// sort vector with dimension to find values of points
template <int Dim>
int KDTree<Dim>::partition(vector<Point<Dim>> & vec, int small, int large, int median, int dimen) {
  Point<Dim> pivot = vec[median];
  Point<Dim> temp1 = vec[large]; // swap rightmost point with mid point
  vec[large] = pivot;
  vec[median] = temp1;
  int i = small;
  for (int j = small; j < large; j++) {
    if (smallerDimVal(vec[j], pivot, dimen)) { // swap points
      Point<Dim> swap1 = vec[j];
      vec[j] = vec[i];
      vec[i] = swap1;
      i++;
    }
  }
  // swap median point and end point 
  Point<Dim> swap2 = vec[i];
  vec[i] = vec[large];
  vec[large] = swap2;
  return i;
}

template <int Dim>
void KDTree<Dim>::smallestElm(vector<Point<Dim>> & vec, int small, int large, int median, int dimen) {
    if (small == large) {
      return;
    }
    int index = partition(vec, small, large, median, dimen);
    if (median == index) {
      return;
    } else if (median < index) {
      smallestElm(vec, small, index-1, median, dimen);
      return;
    } else {
      smallestElm(vec, index+1, large, median, dimen);
      return;
    }
}

template <int Dim>
KDTree<Dim>::KDTree(const KDTree<Dim>& other) {
  /**
   * @todo Implement this function!
   */
   vec = other.vec;
   root = buildTree(vec, 0, vec.size()-1, 0);
}

template <int Dim>
const KDTree<Dim>& KDTree<Dim>::operator=(const KDTree<Dim>& rhs) {
  /**
   * @todo Implement this function!
   */
  if (this != &rhs) {
    destroy(this);
    vec = rhs.vec;
    root = buildTree(rhs.vec, 0, rhs.vec.size()-1, 0);
  }
  return *this;
}

template <int Dim>
KDTree<Dim>::~KDTree() {
  /**
   * @todo Implement this function!
   */
   destroy(root);
}

template <int Dim>
void KDTree<Dim>::destroy(KDTreeNode *root) {
  if (root != NULL) {
    destroy(root->left);
    destroy(root->right);
    delete root;
  }
}

template <int Dim>
Point<Dim> KDTree<Dim>::findNearestNeighbor(const Point<Dim>& query) const
{
    /**
     * @todo Implement this function!
     */

    return Point<Dim>();
}

template <int Dim>
Point<Dim> KDTree<Dim>::neighborHelper(KDTreeNode *curr, const Point<Dim> target, Point<Dim> retval, int curr_dim) const {

}
