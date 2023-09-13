#include <gtest/gtest.h>
#include <lib/binary_tree/binary_tree.h>
// #include <lib/binary_tree/definition.h>

#include <map>

void FillTree(hhullen::BinTree<double>& tree) {
  tree.Emplace(1);

  tree.Emplace(0.9);
  tree.Emplace(1.1);

  tree.Emplace(0.8);
  tree.Emplace(0.91);
  tree.Emplace(1.05);
  tree.Emplace(1.2);

  tree.Emplace(0.7);
  tree.Emplace(0.82);
  tree.Emplace(0.905);
  tree.Emplace(0.92);
  tree.Emplace(1.04);
  tree.Emplace(1.06);
  tree.Emplace(1.15);
  tree.Emplace(1.3);
}

class TestClass {
 public:
  TestClass() {}
  bool operator<(const TestClass& src) const { return true; }
};

template <class T1>
class TestRetractor {
 public:
  const T1& operator()(const T1& value) const { return value; }
};

TEST(BinTree, Constructor) {
  hhullen::BinTree<TestClass> tree1;
  hhullen::BinTree<int, int, TestRetractor<int>> tree2;
  hhullen::BinTree<char, float> tree3;
}

TEST(BinTree, Begin_empty) {
  hhullen::BinTree<int> tree;
  EXPECT_TRUE(tree.Begin() == tree.End());
}

TEST(BinTree, Begin_) {
  hhullen::BinTree<double> tree;
  FillTree(tree);
  EXPECT_EQ(*(tree.Begin()), 0.7);
}

TEST(BinTree, End_empty) {
  hhullen::BinTree<int> tree;
  EXPECT_TRUE(tree.Begin() == tree.End());
}

TEST(BinTree, Clear_empty) {
  hhullen::BinTree<int> tree;
  EXPECT_NO_THROW(tree.Clear());
}

TEST(BinTree, Contains_empty) {
  hhullen::BinTree<int> tree;
  int test_v;
  EXPECT_FALSE(tree.Contains(test_v));
}

TEST(BinTree, Empty_empty) {
  hhullen::BinTree<int> tree;
  EXPECT_TRUE(tree.Empty());
}

TEST(BinTree, Find_empty) {
  hhullen::BinTree<int, double> tree;
  EXPECT_TRUE(tree.Find(0.21) == tree.End());
}

// struct Aboba {
//   bool a : 1, b : 1, c : 1, d : 1, e : 1, f : 1, g : 1, h : 1;
// };

// std::ostream& operator<<(std::ostream& out, const Aboba& aboba) {
//   out << aboba.a << aboba.b << aboba.c << aboba.d << aboba.e << aboba.f
//       << aboba.g << aboba.h;
//   return out;
// }

// template <class T>
// struct Node {
//   T* data;
//   Node *left, *right, *parent;
// };

// template <class Value, class Key, class KeyRetractor, class Comparator>
// class Tree {
//  private:
//   KeyRetractor ret_;
//   Comparator comp_;

//   void aboba(const Key& k) {
//     Value value;
//     comp_(k, ret_(value));
//   }
// };

// template <class T1, class T2>
// struct RetMap {
//   const T1& operator()(const std::pair<T1, T2>& t) const { return t.first; }
// };

// template <class T, class Key>
// class map {
//   using tree = Tree<std::pair<const Key, T>, Key, RetMap, std::less<Key>>;
// };

// template <class T>
// struct Ret {
//   const T& operator()(const T& t) const { return t; }
// };

// template <class Key>
// class set {
//   using tree = Tree<const Key, Key, Ret, std::less<Key>>;
// };

// std::ostream& operator<<(std::ostream& out, const int& aboba) {
//   return out << "HUITA";
// }

// template <class T1, class T2>
// std::ostream& operator<<(std::ostream& out, const std::pair<T1, T2>& p) {
//   return out << '{' << p.first << ", " << p.second << '}';
// }

// template <class... Args>
// std::ostream& operator<<(std::ostream& out, const std::map<Args...>& m) {
//   out << '{';
//   bool comma = false;
//   for (const auto& el : m) {
//     if (comma) out << ", ";
//     comma = true;
//     out << el;
//   }
//   return out << '}';
// }

TEST(BinTree, Emplace_simple) {
  hhullen::BinTree<double> tree;
  tree.Emplace(1);
  tree.Emplace(0.5);
  tree.Emplace(1.5);
  tree.Emplace(1.6);
  tree.Emplace(0.4);
  hhullen::BinTree<double>::Iterator iter;
  iter = tree.Find(1);
  EXPECT_EQ(*iter, 1);
  iter = tree.Find(0.5);
  EXPECT_EQ(*iter, 0.5);
  iter = tree.Find(1.5);
  EXPECT_EQ(*iter, 1.5);
  iter = tree.Find(1.6);
  EXPECT_EQ(*iter, 1.6);
  iter = tree.Find(0.4);
  EXPECT_EQ(*iter, 0.4);
  iter = tree.Find(10);
  EXPECT_EQ(iter, tree.End());
  EXPECT_EQ(tree.Size(), 5);
}

TEST(BinTree, Emplace_full_directions) {
  hhullen::BinTree<double> tree;
  FillTree(tree);

  tree.Emplace(1);

  tree.Emplace(0.9);
  tree.Emplace(1.1);

  tree.Emplace(0.8);
  tree.Emplace(0.91);
  tree.Emplace(1.05);
  tree.Emplace(1.2);

  tree.Emplace(0.7);
  tree.Emplace(0.82);
  tree.Emplace(0.905);
  tree.Emplace(0.92);
  tree.Emplace(1.04);
  tree.Emplace(1.06);
  tree.Emplace(1.15);
  tree.Emplace(1.3);

  hhullen::BinTree<double>::Iterator iter;
  iter = tree.Find(1);
  EXPECT_EQ(*iter, 1);

  iter = tree.Find(0.9);
  EXPECT_EQ(*iter, 0.9);
  iter = tree.Find(1.1);
  EXPECT_EQ(*iter, 1.1);

  iter = tree.Find(0.8);
  EXPECT_EQ(*iter, 0.8);
  iter = tree.Find(0.91);
  EXPECT_EQ(*iter, 0.91);
  iter = tree.Find(1.05);
  EXPECT_EQ(*iter, 1.05);
  iter = tree.Find(1.2);
  EXPECT_EQ(*iter, 1.2);

  iter = tree.Find(0.7);
  EXPECT_EQ(*iter, 0.7);
  iter = tree.Find(0.82);
  EXPECT_EQ(*iter, 0.82);
  iter = tree.Find(0.905);
  EXPECT_EQ(*iter, 0.905);
  iter = tree.Find(0.92);
  EXPECT_EQ(*iter, 0.92);
  iter = tree.Find(1.04);
  EXPECT_EQ(*iter, 1.04);
  iter = tree.Find(1.06);
  EXPECT_EQ(*iter, 1.06);
  iter = tree.Find(1.15);
  EXPECT_EQ(*iter, 1.15);
  iter = tree.Find(1.3);
  EXPECT_EQ(*iter, 1.3);

  iter = tree.Find(10);
  EXPECT_EQ(iter, tree.End());
  iter = tree.Find(-2);
  EXPECT_EQ(iter, tree.End());
  iter = tree.Find(0.906);
  EXPECT_EQ(iter, tree.End());
  EXPECT_EQ(tree.Size(), 15);
}
