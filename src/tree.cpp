#include "tree.h"

#include <iostream>

void RedBlackTree::leftRotate(pNode x) {
  pNode y = x->right;
	x->right = y->left;
	if (y->left != nullptr) {
		y->left->parent = x;
	}

	y->parent = x->parent;
	if (x->parent == nullptr) {
		this->root = y;
	} else if (x == x->parent->left) {
		x->parent->left = y;
	} else {
		x->parent->right = y;
	}

	y->left = x;
	x->parent = y;
}

void RedBlackTree::rightRotate(pNode x) {
  pNode y = x->left;
	x->left = y->right;
	if (y->right != nullptr) {
		y->right->parent = x;
	}

	y->parent = x->parent;
	if (x->parent == nullptr) {
		this->root = y;
	} else if (x == x->parent->right) {
		x->parent->right = y;
	} else {
		x->parent->left = y;
	}

	y->right = x;
	x->parent = y;
}

void RedBlackTree::insertFixUp(pNode t) {
  if (t == root) {
    t->color = BLACK;
    return;
  }
  while (t->parent->color == RED) {
    if (t->parent == t->parent->parent->left) {
      pNode uncle = t->parent->parent->right;
      if (uncle != nullptr && uncle->color == RED) {
        t->parent->color = BLACK;
        uncle->color = BLACK;
        t->parent->parent->color = RED;
        t = t->parent->parent;
      } else {
        if (t == t->parent->right) {
          t = t->parent;
          leftRotate(t);
        }
        t->parent->color = BLACK;
        t->parent->parent->color = RED;
        rightRotate(t->parent->parent);
      }
    } else {
      pNode uncle = t->parent->parent->left;
      if (uncle != nullptr && uncle->color == RED) {
        t->parent->color = BLACK;
        uncle->color = BLACK;
        t->parent->parent->color = RED;
        t = t->parent->parent;
      } else {
        if (t == t->parent->left) {
          t = t->parent;
          rightRotate(t);
        }
        t->parent->color = BLACK;
        t->parent->parent->color = RED;
        leftRotate(t->parent->parent);
      }
    }
    if (t == root) {
      break;
    }
  }
  root->color = BLACK;
}

void RedBlackTree::insert(int data) {
  pNode t = new Node(data);
  if (root == nullptr) {
    root = t;
    root->color = BLACK;
  } else {
    pNode p = root;
    pNode q = nullptr;
    while (p != nullptr) {
      q = p;
      if (p->data < t->data) {
        p = p->right;
      } else {
        p = p->left;
      }
    }
    t->parent = q;

    if (q->data < t->data) {
      q->right = t;
    } else {
      q->left = t;
    }
  }
  insertFixUp(t);
}

void RedBlackTree::PreProcess(pNode node, pFunction Function) {
  if (node != nullptr) {
    Function(node);
    PreProcess(node->left, Function);
    PreProcess(node->right, Function);
  }
}

void RedBlackTree::PostProcess(pNode node, pFunction Function) {
  if (node != nullptr) {
    PostProcess(node->left, Function);
    PostProcess(node->right, Function);
    Function(node);
  }
}

void RedBlackTree::printTree() {
  if (root != nullptr) {
    PreProcess(root, [](pNode node) {
      std::cout << "Parent: " << (node->parent ? node->parent->data : -1) << "\n";
      std::cout << "Key: " << node->data << " Color: " << (node->color == RED ? "RED" : "BLACK") << "\n";
      std::cout << "Left: " << (node->left ? node->left->data : -1) << " Right: " << (node->right ? node->right->data : -1) << "\n";
    });
  }
}

int RedBlackTree::GetHeight(pNode root) {
  if (root == nullptr) {
    return 0;
  }
  return 1 + std::max(GetHeight(root->left), GetHeight(root->right));
}