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
    Node<int>* pnode = new Node<int>(3);
    _brtree.insert(pnode);
    pnode = new Node<int>(5);
    _brtree.insert(pnode);
    pnode = new Node<int>(2);
    _brtree.insert(pnode);
    pnode = new Node<int>(6);
    _brtree.insert(pnode);
    pnode = new Node<int>(7);
    _brtree.insert(pnode);
    pnode = new Node<int>(9);
    _brtree.insert(pnode);
    pnode = new Node<int>(8);
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
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
