/**
 * @file avltree.cpp
 * Definitions of the binary tree functions you'll be writing for this lab.
 * You'll need to modify this file.
 */

template<class K, class V>
int  AVLTree<K, V>::maximum(Node *x, Node *y) {
  int a = heightOrNeg1(x);
  int b = heightOrNeg1(y);
  if (a >= b) {
    return a;
  } else {
    return b;
  }
  return a;
}

template <class K, class V>
V AVLTree<K, V>::find(const K& key) const
{
    return find(root, key);
}

template <class K, class V>
V AVLTree<K, V>::find(Node* subtree, const K& key) const
{
    if (subtree == NULL)
        return V();
    else if (key == subtree->key)
        return subtree->value;
    else {
        if (key < subtree->key)
            return find(subtree->left, key);
        else
            return find(subtree->right, key);
    }
}

template <class K, class V>
void AVLTree<K, V>::rotateLeft(Node*& t)
{
    functionCalls.push_back("rotateLeft"); // Stores the rotation name (don't remove this)
    // your code here
    Node *curr = t->right;
    t->right = curr->left;
    curr->left = t;
    t->height = maximum(t->left, t->right) + 1;
    curr->height = maximum(curr->left, curr->right) + 1;
    t = curr;
    return;
}

template <class K, class V>
void AVLTree<K, V>::rotateLeftRight(Node*& t)
{
    functionCalls.push_back("rotateLeftRight"); // Stores the rotation name (don't remove this)
    // Implemented for you:
    rotateLeft(t->left);
    rotateRight(t);
}

template <class K, class V>
void AVLTree<K, V>::rotateRight(Node*& t)
{
    functionCalls.push_back("rotateRight"); // Stores the rotation name (don't remove this)
    // your code here
    Node *curr = t->left;
    t->left = curr->right;
    curr->right = t;
    t->height = maximum(t->left, t->right) + 1;
    curr->height = maximum(curr->left, curr->right) + 1;
    t = curr;
    return;
}

template <class K, class V>
void AVLTree<K, V>::rotateRightLeft(Node*& t)
{
    functionCalls.push_back("rotateRightLeft"); // Stores the rotation name (don't remove this)
    // your code here
    rotateRight(t->right);
    rotateLeft(t);
}

template <class K, class V>
void AVLTree<K, V>::rebalance(Node*& subtree)
{
    // your code here
    if (subtree == NULL) {
      return;
    }
    int r = heightOrNeg1(subtree->right);
    int l = heightOrNeg1(subtree->left);
    if (r-l <= -2) {
      if (heightOrNeg1(subtree->left->left) >= heightOrNeg1(subtree->left->right))       {
        rotateRight(subtree);
      } else {
        rotateLeftRight(subtree);
      }
    } else if (r-l >= 2){
      if (heightOrNeg1(subtree->right->right) >= heightOrNeg1(subtree->right->left)) {
        rotateLeft(subtree);
      } else {
        rotateRightLeft(subtree);
      }
    }
    subtree->height = maximum(subtree->right, subtree->left) + 1;
}

template <class K, class V>
void AVLTree<K, V>::insert(const K & key, const V & value)
{
    insert(root, key, value);
}

template <class K, class V>
void AVLTree<K, V>::insert(Node*& subtree, const K& key, const V& value)
{
    // your code here
    if (subtree == NULL) {
      subtree = new Node(key, value);
      return;
    } else if (key < subtree->key) {
      insert(subtree->left, key, value);
      rebalance(subtree);
    } else if (key > subtree->key) {
      insert(subtree->right, key, value);
      rebalance(subtree);
    }
}

template <class K, class V>
void AVLTree<K, V>::remove(const K& key)
{
    remove(root, key);
}

template <class K, class V>
void AVLTree<K, V>::remove(Node*& subtree, const K& key)
{
    if (subtree == NULL)
        return;

    if (key < subtree->key) {
        // your code here
        remove(subtree->left, key);
        rebalance(subtree);
    } else if (key > subtree->key) {
        // your code here
        remove(subtree->right, key);
        rebalance(subtree);
    } else {
        if (subtree->left == NULL && subtree->right == NULL) {
            /* no-child remove */
            // your code here
            delete subtree;
            subtree = NULL;
        } else if (subtree->left != NULL && subtree->right != NULL) {
            /* two-child remove */
            // your code here
            Node *curr = subtree->left;
            while (curr->right != NULL) {
              curr = curr->right;
            }
            subtree->key = curr->key;
            subtree->value = curr->value;
            remove(subtree->left, curr->key);
        } else {
            /* one-child remove */
            // your code here
            if (subtree->left == NULL) {
              Node *curr = subtree->right;
              delete subtree;
              subtree = curr;
            }
            if (subtree->right == NULL) {
              Node *curr = subtree->left;
              delete subtree;
              subtree = curr;
            }
        }
        // your code here
        rebalance(subtree);
    }
}
