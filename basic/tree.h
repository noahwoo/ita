/*
 * package for binary tree
 */

#ifndef STRUCT_BASIC_TREE_H_
#define STRUCT_BASIC_TREE_H_

#include <stddef.h>
#include <string>
#include <sstream>
#include <algorithm>

#include "stack.h"

#define RECUR 1

template<class T>
struct Node {
  T key;
  bool visited;
  Node* left;
  Node* right;
  Node() : left(NULL), right(NULL), visited(false) {}
  Node(T k) : left(NULL), right(NULL), visited(false) {
    key = k;
  }
};

template<class T>
class BinaryTree 
{
  public:
    BinaryTree() : _root(NULL), _size(0) { }
    Node<T>* get_root() { return _root; }
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

    // mid order traverse
    int mid_order(T* arr) {
      return _mid_order(arr, _root, 0);
    }

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
  protected:
    Node<T>* _root;
    int _size;
  private:
    Node<T>* _search(const T& v, Node<T>* node);
    void _delete_tree(Node<T>* node);
    int _pre_order(T* arr, Node<T>* node, int n);
    int _mid_order(T* arr, Node<T>* node, int n);
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
int BinaryTree<T>::_mid_order(T* arr, Node<T>* node, int n)
{
#if RECUR
    if (NULL != node) {
        arr[n] = node->key;
        int p = _mid_order(arr, node->left, n+1);
        int q = _mid_order(arr, node->right, n+p+1);
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

// binary search tree
template<class T>
class BinarySearchTree : public BinaryTree<T>
{
    public:
        BinarySearchTree() {}
        virtual Node<T>* search(const T& v);
        ~BinarySearchTree() {}
};

template<class T>
Node<T>* BinarySearchTree<T>::search(const T& v)
{
    return NULL;
}

#endif //STRUCT_BASIC_TREE_H_
