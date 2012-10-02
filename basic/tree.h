/*
 * package for binary tree
 */

#ifndef STRUCT_BASIC_TREE_H_
#define STRUCT_BASIC_TREE_H_

#include <stddef.h>
#include <string>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <queue>
#include <stack>

#include "stack.h"

#define RECUR 1

template<class T>
struct Node {
    T key;
    bool visited;
    Node* left;
    Node* right;
    Node* parent;
    Node() : left(NULL), right(NULL), parent(NULL), visited(false) {}
    Node(T k) : left(NULL), right(NULL), parent(NULL), visited(false) {
        key = k;
    }
};

template<class T>
class BinaryTree 
{
    public:
        BinaryTree() : _root(NULL), _size(0) { }
        const Node<T>* get_root() { return _root; }
        Node<T>* set_root(Node<T>* node) {
            _root = node;
            return _root;
        }

        int size() { 
            // return _size; 
            return __size(_root);
        }

        Node<T>* insert_left(Node<T>* parent, Node<T>* node) {
            if (NULL != parent) {
                parent->left = node;
                _size += 1;
                return node;
            }
            return NULL;
        }

        Node<T>* insert_right(Node<T>* parent, Node<T>* node) {
            if (NULL != parent) {
                parent->right = node;
                _size += 1;
                return node;
            }
            return NULL;
        }

        // pre order traverse
        int pre_order(T* arr) {
            return _pre_order(arr, _root, 0);
        }

        // in order traverse
        int in_order(T* arr) {
            return _in_order(arr, _root, 0);
        }
        
        // bfs traverse
        int bfs_order(T* arr);
        
        // dfs traverse
        int dfs_order(T* arr);

        // pos order traverse
        int pos_order(T* arr) {
            return _pos_order(arr, _root, 0);
        }

        // search for given key
        virtual Node<T>* search(const T& v) {
            return _search(v, _root);
        }

        // get size of tree
        int __size(Node<T>* node) {
            if (NULL != node) {
                return 1 + __size(node->left) 
                    + __size(node->right);
            }
            return 0;
        }

        // clear visiting status
        void clear_visit() {
            _clear_visit(_root);
        }

        virtual ~BinaryTree() {
            _delete_tree(_root);
        }
    public:
        Node<T>* _root;
        int _size;
    private:
        Node<T>* _search(const T& v, Node<T>* node);
        void _delete_tree(Node<T>* node);
        int _pre_order(T* arr, Node<T>* node, int n);
        int _in_order(T* arr, Node<T>* node, int n);
        int _pos_order(T* arr, Node<T>* node, int n);
        void _clear_visit(Node<T>* node);
};

template<class T>
void BinaryTree<T>::_clear_visit(Node<T>* node) {
    if (NULL != node) {
        node->visited = false;
        _clear_visit(node->left);
        _clear_visit(node->right);
    }
}

template<class T>
void BinaryTree<T>::_delete_tree(Node<T>* node) {
    if (NULL != node) {
        _delete_tree(node->left);
        _delete_tree(node->right);
        delete node;
    }
}

template<class T>
Node<T>* BinaryTree<T>::_search(const T& v, Node<T>* node)
{
    Node<T>* match = NULL;
    if (NULL != node) {
        if (node->key == v) {
            match = node;
        } else {
            match = _search(v, node->left);
            if (NULL == match) {
                match = _search(v, node->right);
            }
        }
    }
    return match;
}

template<class T>
int BinaryTree<T>::_in_order(T* arr, Node<T>* node, int n)
{
#if RECUR
    if (NULL != node) {
        arr[n] = node->key;
        int p = _in_order(arr, node->left, n+1);
        int q = _in_order(arr, node->right, n+p+1);
        return 1+p+q;
    }
    return 0;
#else
    Stack<Node<T>*> stack(_size);
    stack.push(node);
    int k = 0;
    Node<T>* nd = NULL;
    while (true) {
        if (!stack.pop(nd)) {
            break;
        }
        T key = nd->key;
        arr[k++] = key;
        if (nd->right != NULL) {
            stack.push(nd->right);
        }
        if (nd->left != NULL) {
            stack.push(nd->left);
        }
    }
    return k;
#endif
}

template<class T>
int BinaryTree<T>::_pre_order(T* arr, Node<T>* node, int n)
{
#if RECUR
    if (NULL != node) {
        int p = _pre_order(arr, node->left, n);
        arr[n+p] = node->key;
        int q = _pre_order(arr, node->right, n+p+1);
        return 1+p+q;
    }
    return 0;
#else
    Stack<Node<T>*> stack(_size);
    stack.push(node);
    int k = 0;
    Node<T>* nd = NULL;
    while (true) {
        if (!stack.peek(nd)) {
            break;
        }
        if (nd->left != NULL && !nd->left->visited) {
            stack.push(nd->left);
        } else {
            stack.pop(nd);
            T key = nd->key;
            arr[k++] = key;
            nd->visited = true;
            if (nd->right != NULL) {
                stack.push(nd->right);
            }
        }
    }
    return k;
#endif
}

template<class T>
int BinaryTree<T>::_pos_order(T* arr, Node<T>* node, int n)
{
#ifdef RECUR
    if (NULL != node) {
        int p = _pos_order(arr, node->right, n);
        int q = _pos_order(arr, node->left, n+p);
        arr[n+p+q] = node->key;
        return 1+p+q;
    }
    return 0;
#else
    Stack<Node<T>*> stack(_size);
    stack.push(node);
    int k = 0;
    Node<T>* nd = NULL;
    while (true) {
        if (!stack.peek(nd)) {
            break;
        }

        bool visit = true;
        if (nd->right != NULL && !nd->right->visited) {
            stack.push(nd->right);
            visit = false;
        }

        if (nd->left != NULL && !nd->left->visited) {
            stack.push(nd->left);
            visit = false;
        }

        if (visit) {
            stack.pop(nd);
            T key = nd->key;
            arr[k++] = key;
            nd->visited = true;
        }
    }
    return k;
#endif
}

template<class T>
int BinaryTree<T>::bfs_order(T* arr)
{
    std::queue<Node<T>*> children_queue;
    children_queue.push(_root);
    int n = 0;
    while (!children_queue.empty()) {
        Node<T>* p = children_queue.front();
        children_queue.pop();
        arr[n] = p->key;
        n += 1;
        if (p->left) {
            children_queue.push(p->left);
        }
        if (p->right) {
            children_queue.push(p->right);
        }
    }
    return n;
}

template<class T>
int BinaryTree<T>::dfs_order(T *arr)
{
    std::stack<Node<T>*> children_stack;
    children_stack.push(_root);
    int n = 0;
    while (!children_stack.empty()) {
        Node<T>* p = children_stack.top();
        children_stack.pop();
        arr[n] = p->key;
        n += 1;
        
        if (p->right) {
            children_stack.push(p->right);
        }
        
        if (p->left) {
            children_stack.push(p->left);
        }
    }
    return n;
}

// binary search tree
template<class T>
class BinarySearchTree : public BinaryTree<T>
{
  public:
      BinarySearchTree() {}
      virtual Node<T>* search(const T& v);
      virtual Node<T>* insert(Node<T>* node);
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
Node<T>* BinarySearchTree<T>::search(const T& v)
{
    return _search(v, BinaryTree<T>::_root);
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

#endif // STRUCT_BASIC_TREE_H_
