/*
 * code for binary search
 */
#include<iostream>

// search key in arr, return index if meet, 
// otherwise, return -1
template <class T>
int bin_search(const T* arr, int len,const T& key) {
  int left = 0;
	int right = len-1;
	int mid = 0;
	int pos = -1;
	while(left <= right) {
		mid = (left+right)/2;
		if(key < arr[mid]) {
			right = mid - 1;
		} else if(key > arr[mid]) {
			left = mid + 1;
		} else {
			pos = mid;
			break;
		}
	}
  return pos;
}

int main(int argc, char* argv[]) {
  int arr[] = {3, 19, 35, 43, 72, 98, 121, 159, 327};
	int pos, key;
	key = 43;
	pos = bin_search<int>(arr, sizeof(arr)/sizeof(arr[0]), key);
	std::cout << "search " << key << ", hit at " << pos << std::endl;
	key = 121;
	pos = bin_search<int>(arr, sizeof(arr)/sizeof(arr[0]), key);
	std::cout << "search " << key << ", hit at " << pos << std::endl;
	key = 53;
	pos = bin_search<int>(arr, sizeof(arr)/sizeof(arr[0]), key);
	std::cout << "search " << key << ", hit at " << pos << std::endl;
}
