#include "list.h"
#include <iostream>
#include "gtest/gtest.h"

TEST(ListTest, List) {
  List<int> list;
  int arr[] = {3, 5, 7, 13, 17, 23, 4};
  int n = sizeof(arr)/sizeof(arr[0]);

  Node<int>* p;
  for(int i = 0; i < n; ++i) { 
    p = list.insert(arr[i]);
    EXPECT_EQ(arr[i], p->value);
  }
  std::cout << "List: " << list.toString() << std::endl;
  p = list.search(13);
  EXPECT_EQ(13, p->value);

  list.remove(p);
  p = list.search(13);
  EXPECT_EQ(NULL, p);
  std::cout << "Remove 13: " << list.toString() << std::endl;
  list.reverse();
  std::cout << "Reverse: " << list.toString() << std::endl;

  for(int i = 0; i < n; ++i) {
    p = list.search(arr[i]);
    list.remove(p);
    p = list.search(arr[i]);
    EXPECT_EQ(NULL, p);
    std::cout << "Remove " << arr[i] << ": " << list.toString() << std::endl;
  }
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
