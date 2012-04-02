/*
 * package for stack
 */
#ifndef STRUCT_BASIC_SLIST_H_
#define STRUCT_BASIC_SLIST_H_

#include <stddef.h>
#include <string>
#include <sstream>
#include <algorithm>

template<class T>
struct Node {
  T value;
	Node* next;
};

template<class T>
class SList {
	public:
		SList() : _head(NULL) { }
		Node<T>* search(T v);
		Node<T>* insert(T v);
		bool remove(Node<T>* node);
		Node<T>* reverse();
		~SList();
		std::string toString();
	private:
		Node<T>* _head;
};

template<class T>
std::string SList<T>::toString() {
	std::ostringstream oss;
  Node<T>* p = _head;
	while(p) {
		if(p == _head) {
			oss << p->value;
		} else {
			oss << "->" << p->value;
		}
		p = p->next;
	}
	return oss.str();
}

template<class T>
Node<T>* SList<T>::search(T v) {
  Node<T>* p = _head;
	while(p) {
		if(p->value == v) {
			return p;
		}
		p = p->next;
	}
	return NULL;
}

template<class T>
Node<T>* SList<T>::insert(T v) {
  Node<T>* node = new Node<T>;
	node->value = v;
	node->next = _head;
	_head = node;
	return _head;
}

template<class T>
bool SList<T>::remove(Node<T>* node) {
	if(NULL == node)
		return NULL;
  if(_head == node) {
    _head = node->next;
		delete node;
	} else {
		Node<T>* pp, *p;
    pp = NULL; p = _head;

		while(p) {
      if(p->value == node->value) {
				break;
			}
			pp = p;
			p = p->next;
		}

		if(!pp) {
			return NULL;
		}

		if(p) {
			pp->next = p->next;
		} else {
			pp->next = NULL;
		}

		delete node;
	}
}

template<class T>
SList<T>::~SList() {
  Node<T> *p = _head, *pn;
	while(p) {
		pn = p->next;
		delete p;
		p = pn;
	}
}

template<class T>
Node<T>* SList<T>::reverse() {
  Node<T> *p = _head, *pp = NULL, *t;
	while(p) {
		t = p->next;
    p->next = pp;
		pp = p;
		p = t;
	}
	_head = pp;
}

#endif // STRUCT_BASIC_SLIST_H_
