#include "tree.h"
#include "gtest/gtest.h"

TEST(BinaryTree, BinaryTreeSearchTest) {
    BinaryTree<int> bintree;

	Node<int> *root = new Node<int>(3);
	Node<int> *node = NULL, *parent = NULL;

	bintree.set_root(root);

	node = new Node<int>(5);
	parent = bintree.insert_left(root, node);
	node = new Node<int>(6);
	bintree.insert_left(parent, node);
	node = new Node<int>(15);
	bintree.insert_right(parent, node);

	node = new Node<int>(9);
	parent = bintree.insert_right(root, node);
    node = new Node<int>(13);
	bintree.insert_right(parent, node);

	node = bintree.search(9);
    EXPECT_EQ(9, node->key);
    
	node = bintree.search(13);
	EXPECT_EQ(13, node->key);

	node = bintree.search(15);
	EXPECT_EQ(15, node->key);

	node = bintree.search(1);
	EXPECT_EQ(NULL, node);
}

TEST(BinaryTree, BinaryTreeTraverseTest) 
{
    BinaryTree<int> bintree;

	Node<int> *root = new Node<int>(3);
	Node<int> *node = NULL, *parent = NULL;

	bintree.set_root(root);

	node = new Node<int>(5);
	parent = bintree.insert_left(root, node);
	node = new Node<int>(6);
	bintree.insert_left(parent, node);
	node = new Node<int>(15);
	bintree.insert_right(parent, node);

	node = new Node<int>(9);
	parent = bintree.insert_right(root, node);
    node = new Node<int>(13);
	bintree.insert_right(parent, node);
    
	int *arr = new int[ bintree.size() ];

	int mid_ord[] = {3, 5, 6, 15, 9, 13};
    int size = bintree.mid_order(arr);
	EXPECT_EQ(size, sizeof(mid_ord)/sizeof(mid_ord[0]));
	for (int i = 0; i < size; ++i) {
		EXPECT_EQ(arr[i], mid_ord[i]);
	}
    bintree.clear_visit();

	int pre_ord[] = {6, 5, 15, 3, 9, 13};
	size = bintree.pre_order(arr);
	EXPECT_EQ(size, sizeof(pre_ord)/sizeof(pre_ord[0]));
	for (int i = 0; i < size; ++i) {
		EXPECT_EQ(arr[i], pre_ord[i]);
	}
    bintree.clear_visit();

	int pos_ord[] = {13, 9, 15, 6, 5, 3};
	size = bintree.pos_order(arr);
	EXPECT_EQ(size, sizeof(pos_ord)/sizeof(pos_ord[0]));
	for (int i = 0; i < size; ++i) {
		EXPECT_EQ(arr[i], pos_ord[i]);
	}
    bintree.clear_visit();
}

int main(int argc, char **argv) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
