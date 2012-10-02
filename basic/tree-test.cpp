#include "tree.h"
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

class BinarySearchTreeTest : public testing::Test {
  protected:
	  virtual void SetUp() { }
	  virtual void TearDown() { }
	  BinarySearchTree<int> _bstree;
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

TEST_F(BinaryTreeTest, BinaryTreeBfsDfsTest)
{
    int buff[6];
    int bfs_ord[] = {3, 5, 9, 6, 15, 13};
    int n = _bintree.bfs_order(buff);
    for (int i = 0; i < n; ++i) {
        EXPECT_EQ(buff[i], bfs_ord[i]);
    }
    
    int dfs_ord[] = {3, 5, 6, 15, 9, 13};
    n = _bintree.dfs_order(buff);
    for (int i = 0; i < n; ++i) {
        EXPECT_EQ(buff[i], dfs_ord[i]);
    }
}

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
