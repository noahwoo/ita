#include "bin-tree.h"
#include "gtest/gtest.h"

class BinaryTreeTest : public testing::Test {
  protected:
      virtual void SetUp() {
          Node<int> *root = new Node<int>(3);
          Node<int> *node = NULL, *parent = NULL;

          _bintree.set_root(root);

          node = new Node<int>(5);
          parent = _bintree.insert_left(root, node);
          node = new Node<int>(6);
          _bintree.insert_left(parent, node);
          node = new Node<int>(15);
          _bintree.insert_right(parent, node);

          node = new Node<int>(9);
          parent = _bintree.insert_right(root, node);
          node = new Node<int>(13);
          _bintree.insert_right(parent, node);
      }

      virtual void TearDown() { }

      BinaryTree<int> _bintree;
};

TEST_F(BinaryTreeTest, BinaryTreeSearchTest) 
{
    Node<int> *node = _bintree.search(9);
    EXPECT_EQ(9, node->key);

    node = _bintree.search(13);
    EXPECT_EQ(13, node->key);

    node = _bintree.search(15);
    EXPECT_EQ(15, node->key);

    node = _bintree.search(1);
    EXPECT_EQ(NULL, node);
}

TEST_F(BinaryTreeTest, BinaryTreeTraverseTest) 
{
    int *arr = new int[ _bintree.size() ];

    int in_ord[] = {3, 5, 6, 15, 9, 13};
    int size = _bintree.in_order(arr);
    EXPECT_EQ(size, sizeof(in_ord)/sizeof(in_ord[0]));
    for (int i = 0; i < size; ++i) {
        EXPECT_EQ(arr[i], in_ord[i]);
    }
    _bintree.clear_visit();

    int pre_ord[] = {6, 5, 15, 3, 9, 13};
    size = _bintree.pre_order(arr);
    EXPECT_EQ(size, sizeof(pre_ord)/sizeof(pre_ord[0]));
    for (int i = 0; i < size; ++i) {
        EXPECT_EQ(arr[i], pre_ord[i]);
    }
    _bintree.clear_visit();

    int pos_ord[] = {13, 9, 15, 6, 5, 3};
    size = _bintree.pos_order(arr);
    EXPECT_EQ(size, sizeof(pos_ord)/sizeof(pos_ord[0]));
    for (int i = 0; i < size; ++i) {
        EXPECT_EQ(arr[i], pos_ord[i]);
    }
    _bintree.clear_visit();
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
