#include "abstractsyntaxtree.h"
#include <cmath>
#include <cstring>

/**
 * Calculates the value from an AST (Abstract Syntax Tree). To parse numbers from strings, please use std::stod
 * @return A double representing the calculated value from the expression transformed into an AST
 */
double AbstractSyntaxTree::eval() const {
    return evalHelp(root);
}

double AbstractSyntaxTree::evalHelp(Node * root) const {
  if (root->left == NULL && root->right == NULL) {
    return std::stod(root->elem);
  }
  if (root == NULL) {
    return 0;
  }
  double total = 0;
  if ((root->elem) == "*") {
    total = evalHelp(root->left) * evalHelp(root->right);
  }
  if ((root->elem) == "/") {
    total = evalHelp(root->left) / evalHelp(root->right);
  }
  if ((root->elem) == "+") {
    total = evalHelp(root->left) + evalHelp(root->right);
  }
  if ((root->elem) == "-") {
    total = evalHelp(root->left) - evalHelp(root->right);
  }
  return total;
}
