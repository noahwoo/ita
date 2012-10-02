#include "br-tree.h"
#include "gtest/gtest.h"

class BlackRedTreeTest : public testing::Test {
  protected:
      virtual void SetUp() { } 
      virtual void TearDown() { }
};

TEST_F(BlackRedTreeTest, BlackRedTreeInsertTest)
{
    BlackRedTree<int> _brtree;
    Node<int>* pnode = new Node<int>(41);
    _brtree.insert(pnode);
    pnode = new Node<int>(38);
    _brtree.insert(pnode);
    pnode = new Node<int>(31);
    _brtree.insert(pnode);
    pnode = new Node<int>(12);
    _brtree.insert(pnode);
    pnode = new Node<int>(19);
    _brtree.insert(pnode);
    pnode = new Node<int>(8);
    _brtree.insert(pnode);
    std::cout << _brtree.to_string();

    pnode = new Node<int>(7);
    _brtree.insert(pnode);
    pnode = new Node<int>(1);
    _brtree.insert(pnode);
    pnode = new Node<int>(11);
    _brtree.insert(pnode);
    pnode = new Node<int>(17);
    _brtree.insert(pnode);
    pnode = new Node<int>(19);
    _brtree.insert(pnode);

    std::cout << _brtree.to_string();

	Node<int>* node = _brtree.search(17);
    EXPECT_EQ(17, node->key);

	node = _brtree.search(24);
	EXPECT_EQ(NULL, node);

	node = _brtree.search(17);
	node = _brtree.delete_n(node);
	EXPECT_TRUE(NULL != node && 17 == node->key);

	node = _brtree.search(17);
	EXPECT_EQ(NULL, node);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
