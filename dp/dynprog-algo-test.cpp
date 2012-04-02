#include "dynprog-algo.h"
#include "gtest/gtest.h"

TEST (DPTest,NonDescSubseq) 
{
  DP<int> dp;
  int arr[] = {3, 19, 35, 72, 43, 121, 98, 159, 327};
  int ndsub[16];
  int sublen = 0;
  dp.NonDescSubseq(arr, sizeof(arr)/sizeof(arr[0]), 
						ndsub, &sublen);
  EXPECT_EQ(7, sublen);
  for (int i = 0; i < sublen; ++i)
  {
    std::cout << ndsub[i] << " ";
  }
  std::cout << std::endl;
}

TEST (DPTest,CommonSubseq) 
{
  DP<char> dp;
  char str1[] = "ATCGGTCTA";
  char str2[] = "CGTCTGA";
  char buff[256];
  int len = -1;
  std::cout << "len1=" << sizeof(str1)/sizeof(str1[0]) 
            << "; len2=" << sizeof(str2)/sizeof(str2[0]) 
            << std::endl;
	std::cout << str1 << std::endl;
	std::cout << str2 << std::endl;
  dp.CommonSubseq2(str1, sizeof(str1)/sizeof(str1[0]) - 1, 
            str2, sizeof(str2)/sizeof(str2[0]) - 1, 
            buff, &len);
  EXPECT_EQ(6, len);
  for (int i = 0; i < len; ++i) {
    std::cout << buff[i];
  }
  std::cout << std::endl;
}

TEST (DPTest, EditDistance) 
{
  DP<char> dp;
  char str1[] = "test";
  char str2[] = "texts";
  std::cout << "len1=" << sizeof(str1)/sizeof(str1[0]) 
            << "; len2=" << sizeof(str2)/sizeof(str2[0]) 
            << std::endl;
	std::cout << str1 << std::endl;
	std::cout << str2 << std::endl;
  int dist = dp.EditDistance (str1, sizeof(str1)/sizeof(str1[0]) - 1, 
            str2, sizeof(str2)/sizeof(str2[0]) - 1); 
  EXPECT_EQ(2, dist);
}

int main(int argc, char **argv) 
{
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
