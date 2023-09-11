#include <gtest/gtest.h>
#include <lib/binary_tree/binary_tree.h>

class Test1 {
 public:
  Test1() {}
  bool operator<(const Test1 &src) const { return true; }
};

// TEST(BinTree, Constructor) {
//   hhullen::BinTree<char, int> tree1;
//   hhullen::BinTree<Test1, int> tree2;
// }

// TEST(BinTree, Begin_empty) {
//   hhullen::BinTree<Test1, int> tree;
//   EXPECT_TRUE(tree.Begin() == tree.End());
// }

// TEST(BinTree, End_empty) {
//   hhullen::BinTree<Test1, int> tree;
//   EXPECT_TRUE(tree.Begin() == tree.End());
// }

// TEST(BinTree, Clear_empty) {
//   hhullen::BinTree<Test1, int> tree;
//   EXPECT_NO_THROW(tree.Clear());
// }

// TEST(BinTree, Contains_empty) {
//   hhullen::BinTree<Test1, int> tree;
//   Test1 test_v;
//   EXPECT_FALSE(tree.Contains(test_v));
// }

// TEST(BinTree, Empty_empty) {
//   hhullen::BinTree<Test1, int> tree;
//   EXPECT_TRUE(tree.Empty());
// }

// TEST(BinTree, Find_empty) {
//   hhullen::BinTree<double, int> tree;
//   EXPECT_TRUE(tree.Find(0.21) == tree.End());
// }

TEST(BinTree, Emplace_simple) {
  hhullen::BinTree<double, int> tree;
  tree.Emplace(1, 1);
  tree.Emplace(0.5, 2);
  tree.Emplace(1.5, 3);
  hhullen::BinTree<double, int>::Iterator iter;
  iter = tree.Find(1);
  EXPECT_EQ((*iter).second, 1);
  iter = tree.Find(0.5);
  EXPECT_EQ((*iter).second, 2);
  // iter = tree.Find(1.5);
  // EXPECT_EQ((*iter).second, 3);
}
