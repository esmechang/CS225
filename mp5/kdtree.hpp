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
     double dist1; // distance of currentBest
     double dist2; // distance of potential

     for (int i = 0; i < dims; i++) {
       double a = currentBest[i] - target[i];
       a = a * a;
       double b = potential[i] - target[i];
       b = b * b;
       dist1 = a;
       dist2 = b;
     }
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

template <int Dim>
KDTree<Dim>::KDTree(const vector<Point<Dim>>& newPoints)
{
    /**
     * @todo Implement this function!
     */
     // if (newPoints.size() == 0) {
     //   size = 0;
     //   root = NULL;
     // } else {
     //   int length = newPoints.size();
     //   size = length;
     //   BuildTree(newPoints, length, root);
     // }
}

// BuildTree(newPoints, length, root) {
//   int median = (length-1)/2;
//   int index = smallestElm(newPoints, 0, );
// }

template <int Dim>
int KDTree<Dim>::partition(const vector<Point<Dim>> & vec, int small, int large, int dimen) {
  Point<Dim> pivot = vec[small];
  int i = small;
  for (int j = 1; j <= small-1; j++) {
    if ((vec[j])[dimen] <= pivot) {
      swap((vec[i])[dimen], (vec[j])[dimen]);
      i++;
    }
  }
  swap((vec[i])[dimen], (vec[small])[dimen]);
  return i;
}

template <int Dim>
int KDTree<Dim>::smallestElm(const vector<Point<Dim>> & vec, int small, int large, int median) {
  int index = partition(vec, small, large);
  if (median > 0 && median <= large-small+1) {
    if (index-1 == median-1) {
      return vec[index];
    }
    if (index-1 > median-1) {
      return smallestElm(vec, small, index-1, median);
    }
    return smallestElm(vec, index+1, large, median-index+small-1);
  }
}

template <int Dim>
KDTree<Dim>::KDTree(const KDTree<Dim>& other) {
  /**
   * @todo Implement this function!
   */
}



template <int Dim>
const KDTree<Dim>& KDTree<Dim>::operator=(const KDTree<Dim>& rhs) {
  /**
   * @todo Implement this function!
   */

  return *this;
}

template <int Dim>
KDTree<Dim>::~KDTree() {
  /**
   * @todo Implement this function!
   */
}

template <int Dim>
Point<Dim> KDTree<Dim>::findNearestNeighbor(const Point<Dim>& query) const
{
    /**
     * @todo Implement this function!
     */

    return Point<Dim>();
}
