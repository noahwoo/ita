
#include "search-algo.h"

template<class T>
void SearchAlgo<T>::foo() { }

template<class T>
int SearchAlgo<T>::BinSearch(const T* arr, 
	int len, const T& key) {
  
	int left = 0, right = len-1;
	int mid = 0, pos = -1;

	while (left <= right) {
		mid = (left+right)/2;
		if (key < arr[mid]) {
			right = mid - 1;
		} else if (key > arr[mid]) {
			left = mid + 1;
		} else {
			pos = mid;
			break;
		}
	}
  return pos;
}
