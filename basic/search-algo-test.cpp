#include "search-algo.h"
#include "gtest/gtest.h"

TEST(SearchAlgoTest, BinSearch) {
  SearchAlgo<int> sa;
	int arr[] = {3, 19, 35, 43, 72, 98, 121, 159, 327};
	sa.foo();
	int key = 43;
  EXPECT_EQ(3, sa.BinSearch(arr, sizeof(arr)/sizeof(arr[0]), key));
  EXPECT_EQ(6, sa.BinSearch(arr, sizeof(arr)/sizeof(arr[0]), 121));
  EXPECT_EQ(-1, sa.BinSearch(arr, sizeof(arr)/sizeof(arr[0]), 53));
}

int main(int argc, char **argv) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
