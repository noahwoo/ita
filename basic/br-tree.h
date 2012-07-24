/*
 * package for black red binary tree
 */

#ifndef STRUCT_BASIC_BR_TREE_H_
#define STRUCT_BASIC_BR_TREE_H_

#include <stddef.h>
#include <string>
#include <sstream>
#include <iostream>
#include <algorithm>

#include "bin-tree.h"
// binary search tree
template<class T>
class BlackRedTree : public BinaryTree<T>
{
    public:
        BlackRedTree() {
			BinaryTree<T>::_root = Node<T>::nil();
		}
        void insert(Node<T>* node);
		~BlackRedTree() {}
    private:
        void left_rotate(Node<T>* node);
        void right_rotate(Node<T>* node);
        void insert_fixup(Node<T>* node);
};

template<class T>
void BlackRedTree<T>::insert(Node<T>* node)
{
    Node<T>* ynode = Node<T>::nil();
    Node<T>* xnode = BinaryTree<T>::_root;
    while (xnode != Node<T>::nil()) {
        ynode = xnode;
        if (node->key < xnode->key) {
            xnode = xnode->left;
        } else {
            xnode = xnode->right;
        }
    }
    node->parent = ynode;
    if (ynode == Node<T>::nil()) {
        BinaryTree<T>::_root = node;
    } else {
        if (node->key < ynode->key) {
            ynode->left = node;
        } else {
            ynode->right = node;
        }
    }
    node->left = Node<T>::nil();
    node->right = Node<T>::nil();
    node->black = false;
    insert_fixup(node);
}

template<class T>
void BlackRedTree<T>::insert_fixup(Node<T>* node)
{
    // fix-up
    while (node->parent->black == false) {
        if (node->parent == node->parent->parent->left) {
            Node<T>* ynode = node->parent->parent->right;
            if (ynode->black == false) {
                node->parent->black = true;
                ynode->black = true;
                node->parent->parent->black = false;
                node = node->parent->parent;
            } else { 
                if (node == node->parent->right) {
                    node = node->parent;
                    left_rotate(node);
                }
                node->parent->black = true;
                node->parent->parent->black = false;
                right_rotate(node->parent->parent);
            }
        } else {
            Node<T>* ynode = node->parent->parent->left;
            if (ynode->black == false) {
                node->parent->black = true;
                ynode->black = true;
                node->parent->parent->black = false;
                node = node->parent->parent;
            } else {
                if (node == node->parent->left) {
                    node = node->parent;
                    right_rotate(node);
                }
                node->parent->black = true;
                node->parent->parent->black = false;
                left_rotate(node->parent->parent);
            }
        }
    }

    // set the root be black
    BinaryTree<T>::_root->black = true;
}

template<class T>
void BlackRedTree<T>::left_rotate(Node<T>* node)
{
    Node<T>* rnode = node->right;
    node->right = rnode->left;
    rnode->left->parent = node;

    rnode->parent = node->parent;
    if (node->parent == Node<T>::nil()) {
      BinaryTree<T>::_root = rnode;
    } else {
        if (node == node->parent->left) {
            node->parent->left = rnode;
        } else {
            node->parent->right = rnode;
        }
    }
    rnode->left = node;
    node->parent = rnode;
}

template<class T>
void BlackRedTree<T>::right_rotate(Node<T>* node)
{
    Node<T>* lnode = node->left;
    node->left = lnode->right;
    lnode->right->parent = node;

    lnode->parent = node->parent;
    if (node->parent == Node<T>::nil()) {
        BinaryTree<T>::_root = lnode;
    } else {
        if (node == node->parent->left) {
            node->parent->left = lnode;
        } else {
            node->parent->right = lnode;
        }
    }
    lnode->right = node;
    node->parent = lnode;
}

#endif // STRUCT_BASIC_BR_TREE_H_
