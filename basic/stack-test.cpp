#include "stack.h"
#include "gtest/gtest.h"

TEST(StackTest, ) {
	int arr1[] = {3, 19, 35, 43, 72};
	int arr2[] = {72, 43, 35, 19, 3};
	int n = sizeof(arr1)/sizeof(arr1[0]);
  Stack<int> stack(n);
	for(int i=0; i < n; ++i) {
		EXPECT_EQ(true, stack.push(arr1[i]));
	}
	EXPECT_EQ(false, stack.push(0));

  int v;
	for(int i=0; i < n; ++i) {
		EXPECT_EQ(true, stack.pop(v));
		EXPECT_EQ(v, arr2[i]);
	}
	EXPECT_EQ(false, stack.pop(v));
}

int main(int argc, char **argv) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
