/*
 * package for binary tree
 */

#ifndef STRUCT_BASIC_BIN_SEARCH_TREE_H_
#define STRUCT_BASIC_BIN_SEARCH_TREE_H_

#include <stddef.h>
#include <string>
#include <sstream>
#include <iostream>
#include <algorithm>

#include "bin-tree.h"

// binary search tree
template<class T>
class BinarySearchTree : public BinaryTree<T>
{
  public:
      BinarySearchTree() {}
      Node<T>* search(const T& v) 
	  {
          return _search(v, BinaryTree<T>::_root);
      }
      Node<T>* insert(Node<T>* node);
      Node<T>* delete_n(Node<T>* node);
      Node<T>* maximum();
      Node<T>* minimum();
      Node<T>* successor(Node<T>* node);
      Node<T>* predecessor(Node<T>* node);
      ~BinarySearchTree() {}
  private:
      Node<T>* _search(const T& v, Node<T>* node);
};

template<class T>
Node<T>* BinarySearchTree<T>::delete_n(Node<T>* node)
{
	Node<T>* yn = NULL;
	Node<T>* xn = NULL;
    if (node->left == NULL or node->right == NULL) {
        yn = node;
	} else {
		yn = successor(node);
	}

	if (yn->left != NULL) {
		xn = yn->left;
	} else {
		xn = yn->right;
	}

	if (xn != NULL) {
		xn->parent = yn->parent;
	}

	if (yn->parent == NULL) {
		BinaryTree<T>::_root  = xn;
	} else {
		if (yn == yn->parent->left) {
			yn->parent->left  = xn;
		} else {
			yn->parent->right = xn;
		}
	}

	if (yn != node) {
		node->key = yn->key;
	}
	return yn;
}

template<class T>
Node<T>* BinarySearchTree<T>::successor(Node<T>* node)
{
    Node<T>* p = NULL;
    if (node->right != NULL) {
        p = node->right;
        while (p->left != NULL) {
            p = p->left;
        }
    } else {
        p = node->parent;
        while (p != NULL && p->right == node) {
            node = p;
            p = p->parent;
        }
    }
    return p;
}

template<class T>
Node<T>* BinarySearchTree<T>::predecessor(Node<T>* node)
{
    Node<T>* p = NULL;
    if (node->left != NULL) {
        p = node->left;
        while (p->right != NULL) {
            p = p->right;
        }
    } else {
        p = node->parent;
        while (p != NULL && p->left == node) {
            node = p;
            p = p->parent;
        }
    }
    return p;
}

template<class T>
Node<T>* BinarySearchTree<T>::maximum()
{
    Node<T>* p = BinaryTree<T>::_root;
    if (NULL == p) {
        return NULL;
    }
    while (NULL != p->right) {
        p = p->right;
    }
    return p;
}

template<class T>
Node<T>* BinarySearchTree<T>::minimum()
{
    Node<T>* p = BinaryTree<T>::_root;
    if (NULL == p) {
        return NULL;
    }

    while (NULL != p->left) {
        p = p->left;
    }
    return p;
}

template<class T>
Node<T>* BinarySearchTree<T>::_search(const T& v, Node<T>* node)
{
    if (NULL == node) {
        return NULL;
    }
    // search for left or right
    if (node->key > v) {
        return _search(v, node->left);;
    } else if (node->key < v) {
        return _search(v, node->right);
    } else {
        return node;
    }
}

template<class T>
Node<T>* BinarySearchTree<T>::insert(Node<T>* node)
{
    // search for the position to insert
    Node<T>* pnode = NULL;
    Node<T>* cnode = BinaryTree<T>::_root;
    while (cnode != NULL) {
        pnode = cnode;
        if (cnode->key > node->key) {
            cnode = cnode->left;
        } else {
            cnode = cnode->right;
        }
    }

    // do insert
    if (pnode == NULL) {
        BinaryTree<T>::_root = node;
        node->parent = NULL;
    } else {
        node->parent = pnode;
        if (pnode->key > node->key) {
            pnode->left = node;
        } else {
            pnode->right = node;
        }
    }
    return node;
}
#endif // STRUCT_BASIC_BIN_SEARCH_TREE_H_
