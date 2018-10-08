/**
 * @file binarytree.cpp
 * Definitions of the binary tree functions you'll be writing for this lab.
 * You'll need to modify this file.
 */
#include "TreeTraversals/InorderTraversal.h"
#include <iostream>

/**
 * @return The height of the binary tree. Recall that the height of a binary
 *  tree is just the length of the longest path from the root to a leaf, and
 *  that the height of an empty tree is -1.
 */
template <typename T>
int BinaryTree<T>::height() const
{
    // Call recursive helper function on root
    return height(root);
}

/**
 * Private helper function for the public height function.
 * @param subRoot
 * @return The height of the subtree
 */
template <typename T>
int BinaryTree<T>::height(const Node* subRoot) const
{
    // Base case
    if (subRoot == NULL)
        return -1;

    // Recursive definition
    return 1 + max(height(subRoot->left), height(subRoot->right));
}

/**
 * Prints out the values of the nodes of a binary tree in order.
 * That is, everything to the left of a node will be printed out before that
 * node itself, and everything to the right of a node will be printed out after
 * that node.
 */
template <typename T>
void BinaryTree<T>::printLeftToRight() const
{
    // Call recursive helper function on the root
    printLeftToRight(root);

    // Finish the line
    cout << endl;
}

/**
 * Private helper function for the public printLeftToRight function.
 * @param subRoot
 */
template <typename T>
void BinaryTree<T>::printLeftToRight(const Node* subRoot) const
{
    // Base case - null node
    if (subRoot == NULL)
        return;

    // Print left subtree
    printLeftToRight(subRoot->left);

    // Print this node
    cout << subRoot->elem << ' ';

    // Print right subtree
    printLeftToRight(subRoot->right);
}

/**
 * Flips the tree over a vertical axis, modifying the tree itself
 *  (not creating a flipped copy).
 */
template <typename T>
void BinaryTree<T>::mirror()
{
  mirrorHelp(root);

}

template <typename T>
void BinaryTree<T>::mirrorHelp(Node * curr) {
  if (curr == NULL) {
    return;
  }
  Node * temp = curr->left;
  curr->left = curr->right;
  curr->right = temp;
  mirrorHelp(curr->left);
  mirrorHelp(curr->right);
}


/**
 * isOrdered() function iterative version
 * @return True if an in-order traversal of the tree would produce a
 *  nondecreasing list output values, and false otherwise. This is also the
 *  criterion for a binary tree to be a binary search tree.
 */
template <typename T>
bool BinaryTree<T>::isOrderedIterative() const
{
    // your code here
  InorderTraversal<T> traverse(root);
  typename TreeTraversal<T>::Iterator iter = traverse.begin();
  typename TreeTraversal<T>::Iterator temp_iter = iter;
  if (*iter == NULL) {
    return true;
  }
  ++iter;
  while (iter != traverse.end()) {
    if ((*iter)->elem < (*temp_iter)->elem) {
      return false;
    }
    temp_iter = iter;
    ++iter;
  }
  return true;
}

/**
 * isOrdered() function recursive version
 * @return True if an in-order traversal of the tree would produce a
 *  nondecreasing list output values, and false otherwise. This is also the
 *  criterion for a binary tree to be a binary search tree.
 */
template <typename T>
bool BinaryTree<T>::isOrderedRecursive() const
{
    // your code here
    if (root == NULL) {
      return true;
    }
    return isOrderedRecursiveHelp(root);
}

template <typename T>
bool BinaryTree<T>::isOrderedRecursiveHelp(Node * curr) const {
  bool result = true;
  if (curr->left != NULL) {
    if (curr->elem < curr->left->elem) {
      return false;
    } else {
      result = isOrderedRecursiveHelp(curr->left);
    }
  }
  if (curr->right != NULL) {
    if (curr->elem > curr->right->elem) {
      return false;
    } else {
      result = result && isOrderedRecursiveHelp(curr->right);
    }
  }
  return result;
}

/**
 * creates vectors of all the possible paths from the root of the tree to any leaf
 * node and adds it to another vector.
 * Path is, all sequences starting at the root node and continuing
 * downwards, ending at a leaf node. Paths ending in a left node should be
 * added before paths ending in a node further to the right.
 * @param paths vector of vectors that contains path of nodes
 */
 template <typename T>
 void BinaryTree<T>::getPaths(vector<vector<T> > &paths) const
 {
   vector<T> onePath;
   getPathsHelp(paths, onePath, root);
 }


template <typename T>
void BinaryTree<T>::getPathsHelp(vector<vector<T> > &paths, vector<T> onePath, Node * curr) const
{
    // your code here
    if (curr == NULL) {
      return;
    }
    if (curr->left == NULL && curr->right == NULL) {
      onePath.push_back(curr->elem);
      paths.push_back(onePath);
      return;
    }
    onePath.push_back(curr->elem);
    Node * lefty = curr->left;
    Node * righty = curr->right;
    getPathsHelp(paths, onePath, lefty);
    getPathsHelp(paths, onePath, righty);
}


/**
 * Each node in a tree has a distance from the root node - the depth of that
 * node, or the number of edges along the path from that node to the root. This
 * function returns the sum of the distances of all nodes to the root node (the
 * sum of the depths of all the nodes). Your solution should take O(n) time,
 * where n is the number of nodes in the tree.
 * @return The sum of the distances of all nodes to the root
 */
template <typename T>
int BinaryTree<T>::sumDistances() const
{
    // your code here
    int total = 0;
    return sumDistancesHelp(root, total);
}

template <typename T>
int BinaryTree<T>::sumDistancesHelp(const Node * curr, int total) const {
  if (curr == NULL) {
    return 0;
  }
  int a = sumDistancesHelp(curr->left, total + 1);
  int b = sumDistancesHelp(curr->right, total + 1);
  return a + b + total;
}
