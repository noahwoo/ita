/*
 * algo package for sort
 */
#ifndef ALGO_BASIC_SORT_H_
#define ALGO_BASIC_SORT_H_
#include <algorithm>
template<class T>
class SortAlgo {
	public:
		SortAlgo() {}
		void HeapSort(T* arr,int n); 
		void QuickSort(T* arr, int n);
		~SortAlgo() {}
	private:
		void qsort(T* arr, int bgn, int end);
		void sift_up(T* arr, int k, int n);
		void sift_down(T* arr, int k, int n);
};

template<class T>
void SortAlgo<T>::HeapSort(T* arr, int n) {
  // build the heap
	for(int k=n-1; k>=0; --k) 
		sift_up(arr, k, n);
	// extract for sorting
	for(int k=0; k < n; ++k) {
    std::swap(arr[0], arr[n-k-1]);
		sift_down(arr, 0, n-k-1);
	}
}

template<class T>
void SortAlgo<T>::sift_up(T* arr, int k, int n) {
  int p;
	do {
		if(k == 0) 
			break;
		p = (k-1)/2;
		if(arr[p] < arr[k]) {
			std::swap(arr[p], arr[k]);
		}
		k = p;
	} while(k > 0);
}

template<class T>
void SortAlgo<T>::sift_down(T* arr, int k, int n) {
  int l, r, c;
	do {
		l = 2*(k+1) - 1;
	 	r = 2*(k+1);
		if(l >= n) 
			break;
		c = l;
		if(r < n && arr[r] > arr[c]) {
			c = r;
		}
		if(arr[c] > arr[k]) {
			std::swap(arr[c], arr[k]);
		}
		k = c;
	} while(k < n);
}

template<class T>
void SortAlgo<T>::QuickSort(T* arr, int n) {
  qsort(arr, 0, n);
}

template<class T>
void SortAlgo<T>::qsort(T* arr, int bgn, int end) {
	if(bgn == end) {
		return;
	}
  
	// do partition
	int i = bgn+1, j;
  for(j = i; j < end; ++j) {
		if(arr[j] < arr[bgn]) {
			if(j != i) {
				std::swap(arr[i], arr[j]);
			}
			++i;
		}
	}
	std::swap(arr[bgn], arr[i-1]);

	// sort the left and right paritions
  qsort(arr, bgn, i-1);
	qsort(arr, i, end);
}
#endif // ALGO_BASIC_SORT_H_
