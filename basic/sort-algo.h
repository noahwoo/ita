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
		void MergeSort(T* arr, int n);
		~SortAlgo() {}
	private:
		void qsort(T* arr, int bgn, int end);
		void sift_up(T* arr, int k, int n);
		void sift_down(T* arr, int k, int n);
		void msort(T* arr, int bgn, int end);
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
	// divide and conqur
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

template<class T>
void SortAlgo<T>::MergeSort(T* arr, int n) {
  msort(arr, 0, n);
}

template<class T>
void SortAlgo<T>::msort(T* arr, int bgn, int end) {
	if (bgn+1 >= end) {
		return;
	}
    // divide 
    int pvt = (bgn+end)/2;
	// conquer
	msort(arr, bgn, pvt); // [bgn, pvt)
	msort(arr, pvt, end); // [pvt, end)
	// merge
	T* buff = new T[end-bgn];
	int i = bgn, j = pvt;
	int k = 0;
	while (i < pvt && j < end) {
		if (arr[i] < arr[j]) {
			buff[k++] = arr[i++];
		} else if (arr[i] > arr[j]) {
			buff[k++] = arr[j++];
		} else {
			buff[k++] = arr[i++];
			buff[k++] = arr[j++];
		}
	}
	while (i < pvt) {
		buff[k++] = arr[i++];
	}
	while (j < end) {
		buff[k++] = arr[j++];
	}
	for (int p = 0; p < k; ++p) {
		arr[bgn+p] = buff[p];
	}
  delete buff;
}

#endif // ALGO_BASIC_SORT_H_
