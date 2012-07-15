#include "bin-tree-search.h"
#include "gtest/gtest.h"

class BinarySearchTreeTest : public testing::Test {
  protected:
	  virtual void SetUp() { }
	  virtual void TearDown() { }
	  BinarySearchTree<int> _bstree;
};

TEST_F(BinarySearchTreeTest, BinarySearchTreeInsertTest) 
{
	int keys[] = {3, 15, 6, 6, 15, 9, 13};
	for (int i = 0; i < sizeof(keys)/sizeof(keys[0]); ++i) {
		Node<int>* node = new Node<int>();
		node->key = keys[i];
		_bstree.insert(node);
	}
	EXPECT_EQ(_bstree.size(), sizeof(keys)/sizeof(keys[0]));
    Node<int>* node = _bstree.search(6);
    ASSERT_TRUE(NULL != node);
	EXPECT_EQ(node->key, 6);
	ASSERT_TRUE(NULL == _bstree.search(10));
}

TEST_F(BinarySearchTreeTest, BinarySearchTreeMinMaxTest) 
{
	int keys[] = {3, 15, 6, 6, 15, 9, 13, 1, 2}; 
	for (int i = 0; i < sizeof(keys)/sizeof(keys[0]); ++i) {
		Node<int>* node = new Node<int>(keys[i]);
		_bstree.insert(node);
	}
	EXPECT_EQ(_bstree.size(), sizeof(keys)/sizeof(keys[0]));
	EXPECT_EQ(_bstree.minimum()->key, 1);
	EXPECT_EQ(_bstree.maximum()->key, 15);
}

TEST_F(BinarySearchTreeTest, BinarySearchTreeSuccPredTest) 
{
	int keys[] = {3, 15, 6, 6, 17, 9, 13, 1, 2}; 
	for (int i = 0; i < sizeof(keys)/sizeof(keys[0]); ++i) {
		Node<int>* node = new Node<int>(keys[i]);
		_bstree.insert(node);
	}
	EXPECT_EQ(_bstree.size(), sizeof(keys)/sizeof(keys[0]));
	Node<int>* node = _bstree.search(13);
	EXPECT_EQ(node->key, 13);

	const Node<int>* succ1 = _bstree.successor(node);
	ASSERT_TRUE(succ1 != NULL);
	EXPECT_EQ(succ1->key, 15);

	node = _bstree.search(17);
	EXPECT_EQ(node->key, 17);

	const Node<int>* succ2 = _bstree.successor(node);
	ASSERT_TRUE(succ2 == NULL);

	node = _bstree.search(6);
	EXPECT_EQ(node->key, 6);

	const Node<int>* pred1 = _bstree.predecessor(node);
	ASSERT_TRUE(pred1 != NULL);
	EXPECT_EQ(pred1->key, 3);

	node = _bstree.search(1);
	EXPECT_EQ(node->key, 1);

	const Node<int>* pred2 = _bstree.predecessor(node);
	ASSERT_TRUE(pred2 == NULL);
}

TEST_F(BinarySearchTreeTest, BinarySearchTreeDeleteTest) 
{
	int keys[] = {3, 15, 6, 6, 17, 9, 13, 1, 2}; 
	for (int i = 0; i < sizeof(keys)/sizeof(keys[0]); ++i) {
		Node<int>* node = new Node<int>(keys[i]);
		_bstree.insert(node);
	}
	EXPECT_EQ(_bstree.size(), sizeof(keys)/sizeof(keys[0]));
	Node<int>* node = _bstree.search(13);
	EXPECT_EQ(node->key, 13);

	_bstree.delete_n(node);
    node = _bstree.search(13);
	ASSERT_TRUE(NULL == node);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
