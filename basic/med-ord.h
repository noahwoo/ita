/*
 * package for stack
 */
#ifndef STRUCT_BASIC_MED_ORD_H_
#define STRUCT_BASIC_MED_ORD_H_

#include <stddef.h>
#include <string>
#include <vector>
#include <algorithm>

template<class T>
class MedianOrder {
  public:
    MedianOrder() { }
    std::pair<T, T> GetMinMax(const T* arr, int n);
    std::pair<T, T> GetTop2(const T* arr, int n);
    T GetKthElement(T* arr, int n, int k);
    ~MedianOrder() { }
  private:
    int partition(T* arr, int p, int q);
};

template<class T>
T MedianOrder<T>::GetKthElement(T* arr, int n, int k)
{
  int p = 0, q = n;
	while (p < q) {
    int s = partition(arr, p, q);
		if (s == k) {
			return arr[s];
    } else if (s > k) {
      q = s-1;
		} else {
			p = s+1;
		}
	}
	return arr[p];
}

template<class T>
int MedianOrder<T>::partition(T* arr, int p, int q)
{
	if (p == q) {
		return p;
	}

  T pvt = arr[p];
	int j = p+1;
	for(int i = p+1; i < q; ++i) {
    if (arr[i] < pvt) {
			if (i != j) {
				std::swap(arr[j], arr[i]);
			}
			j += 1;
		}
	}
	std::swap(arr[p], arr[j-1]);
	return j-1;
}

template<class T>
std::pair<T, T> MedianOrder<T>::GetMinMax(
          const T* arr, int n)
{
  int i = 0;
  std::pair<T, T> min_max;
  if (n % 2 == 0) {
    if (arr[i] < arr[i+1]) {
      min_max.first  = arr[i];
      min_max.second = arr[i+1];
    } else {
      min_max.first  = arr[i+1];
      min_max.second = arr[i];
    }
    i += 2;
  } else {
    min_max.first  = arr[i];
    min_max.second = arr[i];
    i += 1;
  }
  // remaining items
  for(; i < n; i+=2) {
    if (arr[i] < arr[i+1]) {
      if (arr[i] < min_max.first) {
        min_max.first = arr[i];
      }
      if (arr[i+1] > min_max.second) {
        min_max.second = arr[i+1];
      }
    } else {
      if (arr[i+1] < min_max.first) {
        min_max.first = arr[i+1];
      }
      if (arr[i] > min_max.second) {
        min_max.second = arr[i];
      }
    }
  }
  return min_max;
}


template<class T>
std::pair<T, T> MedianOrder<T>::GetTop2(
          const T* arr, int n)
{
  int i;
  std::pair<T, T> top2;
  top2.first = top2.second = arr[0];
  for (i=1; i < n; ++i)
  {
    if (arr[i] > top2.first) {
      top2.second = top2.first;
      top2.first  = arr[i];
    } else if (arr[i] > top2.second) {
      top2.second = arr[i];
    }
  }
  return top2;
}

#endif // STRUCT_BASIC_MED_ORD_H_
