#include <iostream>

#include "tree.h"

int main() {
  RedBlackTree* tree = new RedBlackTree();
  for (int i = 0; i < 10; i++) {
    tree->insert(i);
  }
  tree->printTree();
  std::cout << "\n\n";
  std::cout << tree->GetHeight();
  delete tree;
}