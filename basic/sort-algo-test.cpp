#include "sort-algo.h"
#include "gtest/gtest.h"

TEST(SortAlgoTest, QuickSort) {
  SortAlgo<int> sa;
	// int arr[] = {3, 35, 43, 159, 72, 327, 19, 98, 121};
	// int arr[] = {3, 35, 43, 159, 327, 1210};
	int arr[] = {1210, 327, 159, 43, 35, 3};
	sa.QuickSort(arr, sizeof(arr)/sizeof(arr[0]));
	bool sorted = true;
	for(int i = 1; i < sizeof(arr)/sizeof(arr[0]); ++i) {
		if(arr[i] < arr[i-1]) {
			sorted = false;
			break;
		}
	}
	EXPECT_EQ(sorted, true);
}

TEST(SortAlgoTest, HeapSort) {
  SortAlgo<int> sa;
	int arr[] = {3, 35, 43, 159, 72, 327, 19, 98, 121};
	// int arr[] = {3, 35, 43, 159, 327, 1210};
	// int arr[] = {1210, 327, 159, 43, 35, 3};
	sa.HeapSort(arr, sizeof(arr)/sizeof(arr[0]));
	bool sorted = true;
	for(int i = 1; i < sizeof(arr)/sizeof(arr[0]); ++i) {
		if(arr[i] < arr[i-1]) {
			sorted = false;
			break;
		}
	}
	EXPECT_EQ(sorted, true);
}

TEST(SortAlgoTest, MergeSort) {
    SortAlgo<int> sa;
	int arr[] = {3, 35, 43, 159, 72, 327, 19, 98, 121};
	// int arr[] = {3, 35, 43, 159, 327, 1210};
	// int arr[] = {1210, 327, 159, 43, 35, 3};
	sa.MergeSort(arr, sizeof(arr)/sizeof(arr[0]));
	bool sorted = true;
	for(int i = 1; i < sizeof(arr)/sizeof(arr[0]); ++i) {
		if(arr[i] < arr[i-1]) {
			sorted = false;
			break;
		}
	}
	EXPECT_EQ(sorted, true);
}

int main(int argc, char **argv) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
