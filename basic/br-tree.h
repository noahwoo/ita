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
#include "bin-tree-search.h"
// binary search tree
template<class T>
class BlackRedTree : public BinarySearchTree<T>
{
    public:
        BlackRedTree() {
            BinaryTree<T>::_root = Node<T>::nil();
        }
        void insert(Node<T>* node);
        Node<T>* delete_n(Node<T>* node);
        ~BlackRedTree() {}
    private:
        void left_rotate(Node<T>* node);
        void right_rotate(Node<T>* node);
        void insert_fixup(Node<T>* node);
        void delete_fixup(Node<T>* node);
};

template<class T>
void BlackRedTree<T>::delete_fixup(Node<T>* node)
{
    while (node != BinaryTree<T>::_root 
           && node->black == true) {
        if (node == node->parent->left) {
            Node<T>* wnode = node->parent->right;
            if (wnode->black == false) {
                wnode->black = true;
                node->parent->black = false;
                left_rotate(node->parent);
            }
            if (wnode->left->black == true &&
                wnode->right->black == true) {
                wnode->black = false;
                node = node->parent;
            } else { 
                if (wnode->right->black == true) {
                    wnode->left->black = true;
                    wnode->black = false;
                    right_rotate(wnode);
                    wnode = node->parent->right;
                }
                wnode->black = node->parent->black;
                node->parent->black = true;
                wnode->right->black = true;
                left_rotate(node->parent);
                node = BinaryTree<T>::_root;
            }
        } else {
            Node<T>* wnode = node->parent->left;
            if (wnode->black == false) {
                wnode->black = true;
                node->parent->black = false;
                right_rotate(node->parent);
            }
            if (wnode->right->black == true &&
                wnode->left->black == true) {
                wnode->black = false;
                node = node->parent;
            } else { 
                if (wnode->left->black == true) {
                    wnode->right->black = true;
                    wnode->black = false;
                    left_rotate(wnode);
                    wnode = node->parent->left;
                }
                wnode->black = node->parent->black;
                node->parent->black = true;
                wnode->left->black = true;
                right_rotate(node->parent);
                node = BinaryTree<T>::_root;
            }
        }
    }
    node->black = true;
}

template<class T>
Node<T>* BlackRedTree<T>::delete_n(Node<T>* node)
{
    Node<T>* ynode = Node<T>::nil();
    if (node->left == Node<T>::nil() || 
        node->right == Node<T>::nil()) {
        ynode = node;
    } else {
        ynode = successor(node);
    }

    Node<T>* xnode = Node<T>::nil();
    if (ynode->left != Node<T>::nil()) {
        xnode = ynode->left;
    } else {
        xnode = ynode->right;
    }
    xnode->parent = ynode->parent;
    if (ynode->parent == Node<T>::nil()) {
        BinaryTree<T>::_root = xnode;
    } else {
        if (ynode == ynode->parent->left) {
            ynode->parent->left = xnode;
        } else {
            ynode->parent->right = xnode;
        }
    }

    if (ynode != node) {
        node->key = ynode->key;
    }

    if (ynode->black == true) {
        delete_fixup(xnode);
    }

    return ynode;
}

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
