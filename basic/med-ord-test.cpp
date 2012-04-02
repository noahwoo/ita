#include "med-ord.h"
#include "gtest/gtest.h"

TEST(MedianOrder, MinMaxTest) {
  int arr1[] = {3, 19, 35, 43, 72};
  int arr2[] = {72, 43, 35, 19, 3};
  MedianOrder<int> mo;
  std::pair<int, int> min_max = 
    mo.GetMinMax(arr1, sizeof(arr1)/sizeof(arr1[0]));
  EXPECT_EQ(3, min_max.first);
  EXPECT_EQ(72, min_max.second);

  min_max = 
    mo.GetMinMax(arr1, sizeof(arr1)/sizeof(arr1[0]));
  EXPECT_EQ(3, min_max.first);
  EXPECT_EQ(72, min_max.second);
}

TEST(MedianOrder, Top2Test) {
  int arr1[] = {3, 19, 35, 43, 72};
  int arr2[] = {72, 43, 35, 19, 3};
  MedianOrder<int> mo;
  std::pair<int, int> top2 = 
    mo.GetTop2(arr1, sizeof(arr1)/sizeof(arr1[0]));
  EXPECT_EQ(72, top2.first);
  EXPECT_EQ(43, top2.second);

  top2 = 
    mo.GetTop2(arr1, sizeof(arr1)/sizeof(arr1[0]));
  EXPECT_EQ(72, top2.first);
  EXPECT_EQ(43, top2.second);
}

TEST(MedianOrder, KthElementTest) {
  int arr1[] = {3, 35, 43, 72, 19};
  MedianOrder<int> mo;
  int a = 
    mo.GetKthElement(arr1, sizeof(arr1)/sizeof(arr1[0]), 0);
  EXPECT_EQ(3, a);
  a = 
    mo.GetKthElement(arr1, sizeof(arr1)/sizeof(arr1[0]), 1);
  EXPECT_EQ(19, a);

	a = mo.GetKthElement(arr1, sizeof(arr1)/sizeof(arr1[0]), 4);
  EXPECT_EQ(72, a);
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
