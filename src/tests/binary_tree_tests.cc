#include <gtest/gtest.h>
#include <lib/binary_tree/binary_tree.h>

class Test1 {
 public:
  bool operator<(const Test1 &src) const { return true; }
};

TEST(BinTree, Constructor) { hhullen::BinTree<Test1, int> tree; }
