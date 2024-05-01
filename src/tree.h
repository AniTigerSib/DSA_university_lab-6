#ifndef TREE_H
#define TREE_H

#include <string>

enum Color {
  RED,
  BLACK
};

typedef struct Node* pNode;
struct Node {
  int data;
  Color color;
  pNode left;
  pNode right;
  pNode parent;

  Node(int data) : data(data), color(RED), left(nullptr), right(nullptr), parent(nullptr) {}
};

typedef void(*pFunction)(pNode);

class RedBlackTree {
private:
  pNode root;

  void leftRotate(pNode x);
  void rightRotate(pNode x);
  void insertFixUp(pNode t);
  // void transplant(pNode u, pNode v);
  // pNode minimum(pNode node);
  // void deleteFixUp(pNode x);
  void PreProcess(pNode node, pFunction Function);
  void PostProcess(pNode node, pFunction Function);
public:
  RedBlackTree() : root(nullptr) {}
  ~RedBlackTree() {
    PostProcess(root, [](pNode node) {
      delete node;
    });
  }

  pNode Root() { return root; }

  // Вставка нового узла
  void insert(int data);

  // Удаление узла
  // void remove(int data);

  // Печать дерева (для отладки)
  void printTree();

  int GetHeight(pNode root);
  int GetHeight() {
    return GetHeight(root);
  }
};

#endif