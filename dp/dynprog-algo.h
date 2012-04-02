/*
 * algo for dynamic programming
 */
#ifndef ALGO_DYN_PROG_H_
#define ALGO_DYN_PROG_H_
#include <iostream>
#include <cstdio>
#include <map>
#include "array.h"
template<class T>
class DP {
  public:
    DP () { }
    void NonDescSubseq(const T* arr, int len, 
                       T* sub, int* sub_len);
    void CommonSubseq(const T* arr1, int len1, 
                    const T* arr2, int len2, 
                    T* sub, int* sub_len);
    void CommonSubseq2(const T* arr1, int len1, 
                    const T* arr2, int len2, 
                    T* sub, int* sub_len);
		int EditDistance(const T* str1, int len1, 
											const T* str2, int len2);
		int OptimalSegment(const char* str, std::map<std::string, int> freq, char* str_seg);
    ~DP() { }
};

template<class T>
int DP<T>::OptimalSegment(const char* str, std::map<std::string, int> freq, 
				   char* str_seg) {
    return 0;
}

template<class T>
void DP<T>::NonDescSubseq(const T* arr, int len, 
                      T* sub, int* sub_len)
{
  int *max_at = new int[len];
  int *pos_at = new int[len];
  T max_c = 0;
  int max_p = -1;
  max_at[0] =  1;
  pos_at[0] = -1;
  for (int i = 1; i < len; ++i)
  {
    for (int j = i-1; j >= 0; --j) 
    {
      if (arr[j] <= arr[i]) 
      {
        max_at[i] = max_at[j] + 1;
        pos_at[i] = j;
        if (max_at[i] > max_c)
        {
           max_c = max_at[i];
           max_p = i;
        }
        break;
      }
    }
  }
  int pos = max_p;
  *sub_len = max_at[pos];
  int idx = *sub_len;
  while (pos >= 0) 
  {
    idx -= 1;
    sub[idx] = arr[pos];
    pos = pos_at[pos];
  }
  delete max_at;
  delete pos_at;
}

template<class T>
void DP<T>::CommonSubseq(const T* arr1, int len1, 
                      const T* arr2, int len2, 
                      T* sub, int* sub_len) {
  // allocate the buffer
  TwoDArray<int> pos_at(len1+1, len2+1);
  TwoDArray<int> max_at(len1+1, len2+1);
  
  // init the boundary
  bool matched = false;
  for (int i = 0; i <= len1; ++i) {
    max_at(i, 0) = 0;
  }
  for(int j = 1; j <= len2; ++j) {
    max_at(0, j) = 0;
  }

  // updates the remaining elements
  int i = 0, ii = 0;
  int j = 0, jj = 0;
  for(i = 0; i < len1; ++i) {
    for(j = 0; j < len2; ++j) {
      ii = i+1; 
      jj = j+1;
      if(arr1[i] == arr2[j]) {
        max_at(ii, jj) = max_at(ii-1, jj-1)+1;
        pos_at(ii, jj) = 3;
      } else {
        if (max_at(ii-1, jj) > max_at(ii, jj-1)) {
          max_at(ii, jj) = max_at(ii-1, jj);
          pos_at(ii, jj) = 2;
        } else {
          max_at(ii, jj) = max_at(ii, jj-1);
          pos_at(ii, jj) = 1;
        }
      }
    }
  }
 
  i = len1; j = len2;
  *sub_len = max_at(i, j);
  
  int ncomm = *sub_len;
  while( i > 0 && j > 0) {
    if (pos_at(i, j) == 3) {
       ncomm -= 1;
       sub[ncomm] = arr1[i-1];
       i -= 1; j -= 1;
    } else if (pos_at(i, j) == 2) {
       i -= 1;
    } else if (pos_at(i, j) == 1) {
       j -= 1;
    }
  }
}

template<class T>
void DP<T>::CommonSubseq2(const T* arr1, int len1, 
                      const T* arr2, int len2, 
                      T* sub, int* sub_len) {
  // allocate the buffer
  TwoDArray<int> max_at(len1+1, len2+1);
  
  // init the boundary
  bool matched = false;
  for (int i = 0; i <= len1; ++i) {
    max_at(i, 0) = 0;
  }
  for(int j = 1; j <= len2; ++j) {
    max_at(0, j) = 0;
  }

  // updates the remaining elements
  int i = 0, ii = 0;
  int j = 0, jj = 0;
  for(i = 0; i < len1; ++i) {
    for(j = 0; j < len2; ++j) {
      ii = i+1; 
      jj = j+1;
      if(arr1[i] == arr2[j]) {
        max_at(ii, jj) = max_at(ii-1, jj-1)+1;
      } else {
        if (max_at(ii-1, jj) > max_at(ii, jj-1)) {
          max_at(ii, jj) = max_at(ii-1, jj);
        } else {
          max_at(ii, jj) = max_at(ii, jj-1);
        }
      }
    }
  }
 
  // reconstruct the sub sequence
  i = len1; j = len2;
  *sub_len = max_at(i, j);
  
  int ncomm = *sub_len;
  while( i > 0 && j > 0) {
    if (max_at(i, j) == (max_at(i-1, j-1) + 1)) {
       ncomm -= 1;
       sub[ncomm] = arr1[i-1];
       i -= 1; j -= 1;
    } else if (max_at(i, j) == max_at(i-1, j)) {
       i -= 1;
    } else if (max_at(i, j) == max_at(i, j-1)) {
       j -= 1;
    }
  }
}

template<class T>
int DP<T>::EditDistance(const T* str1, int len1, 
											const T* str2, int len2)
{
  TwoDArray<int> dist_at(len1, len2);
	int i=0, j=0;
	dist_at(0, 0) = (str1[0] == str2[0] ? 0 : 1);
	
	for(i = 1; i < len1; ++i) {
    dist_at(i,0) = dist_at(i-1, 0) + 1; // insert in str2
	}

	for(j = 1; j < len2; ++j) {
		dist_at(0, j) = dist_at(0, j-1) + 1; // delete in str2
	}

	for(i = 1; i < len1; ++i) {
		for(j = 1; j < len2; ++j) {
			if (str1[i] == str2[j]) {
        dist_at(i, j) = dist_at(i-1, j-1); // a match
      } else {
				if (dist_at(i-1, j-1) <= dist_at(i, j-1) && 
						dist_at(i-1, i-1) <= dist_at(i-1, j)) {
					dist_at(i, j) = dist_at(i-1, j-1) + 1; // replace i<->j in str1/str2
				} else if (dist_at(i-1, j) <= dist_at(i-1, j-1) && 
						dist_at(i-1, j) <= dist_at(i, j-1)) {
					dist_at(i, j) = dist_at(i-1, j) + 1; // delete str1
				} else {
					dist_at(i, j) = dist_at(i, j-1) + 1; // delete str2
				}
			}
		}
	}

	return dist_at(len1-1, len2-1);
}

#endif // ALGO_DYN_PROG_H_
