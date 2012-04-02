/*
 * package for stack
 */
#ifndef STRUCT_BASIC_STACK_H_
#define STRUCT_BASIC_STACK_H_
#include <stddef.h>
template<class T>
class Stack {
	public:
		Stack(int N) : _elem(NULL), _N(N), _top(0) {
			_elem = new T[N];
		}
		bool push(T v);
		bool pop(T& v);
		bool peek(T& v);
		bool empty() {
			return _N == 0;
		}
		~Stack() {
			if(_elem) {
				delete _elem;
			}
		}
	private:
		T* _elem;
		int _N;
		int _top;
};

template<class T>
bool Stack<T>::push(T v) {
	if(_top >= _N) 
		return false;
    _elem[_top] = v;
	_top += 1;
	return true;
}

template<class T>
bool Stack<T>::pop(T& v) {
  if(_top == 0) 
		return false;
  _top -= 1;
  v = _elem[_top];
  return true;
}

template<class T>
bool Stack<T>::peek(T& v) {
  if(_top == 0) 
		return false;
  v = _elem[_top-1];
  return true;
}

#endif // STRUCT_BASIC_STACK_H_
