/*
 * package for stack
 */
#ifndef STRUCT_BASIC_LIST_H_
#define STRUCT_BASIC_LIST_H_

#include <stddef.h>
#include <string>
#include <sstream>
#include <algorithm>

template<class T>
struct Node {
  T value;
	Node* prev;
	Node* next;
};

template<class T>
class List {
	public:
		List() : _head(NULL) { }
		Node<T>* search(T v);
		Node<T>* insert(T v);
		bool remove(Node<T>* node);
		Node<T>* reverse();
		~List();
		std::string toString();
	private:
		Node<T>* _head;
};

template<class T>
std::string List<T>::toString() {
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
Node<T>* List<T>::search(T v) {
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
Node<T>* List<T>::insert(T v) {
  Node<T>* node = new Node<T>;
	node->value = v;
	node->next = _head;
	node->prev = NULL;
	if(_head) {
		_head->prev = node;
	}
	_head = node;
	return _head;
}

template<class T>
bool List<T>::remove(Node<T>* node) {
	if(NULL == node)
		return NULL;
  if(_head == node) {
    _head = node->next;
		if(_head) {
			_head->prev = NULL;
		}
		delete node;
	} else {
    node->prev->next = node->next;
		if(node->next) {
			node->next->prev = node->prev;
		}
		delete node;
	}
}

template<class T>
List<T>::~List() {
  Node<T> *p = _head, *pn;
	while(p) {
		pn = p->next;
		delete p;
		p = pn;
	}
}

template<class T>
Node<T>* List<T>::reverse() {
  Node<T> *p = _head, *pp = _head;
  while(p) {
		std::swap(p->prev, p->next);
		pp = p;
		p = p->prev;
	}
	_head = pp;
}

#endif // STRUCT_BASIC_LIST_H_
