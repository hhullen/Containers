#include <gtest/gtest.h>
#include <lib/binary_tree/binary_tree.h>

#include <vector>

std::vector<double> data_upload_1{1,    0.9,  1.1,  0.8,   0.91, 1.05,
                                  1.2,  0.7,  0.82, 0.905, 0.92, 1.04,
                                  1.06, 1.15, 1.3,  0.75,  0.81};
std::vector<double> data_result_1{0.7,   0.75, 0.8,  0.81, 0.82, 0.9,
                                  0.905, 0.91, 0.92, 1,    1.04, 1.05,
                                  1.06,  1.1,  1.15, 1.2,  1.3};

std::vector<double> data_upload_2{-1, -2, -3, -4, -5, -6, -7, -8, -9, 9,
                                  8,  7,  6,  5,  4,  3,  2,  1,  0};
std::vector<double> data_result_2{-9, -8, -7, -6, -5, -4, -3, -2, -1, 0,
                                  1,  2,  3,  4,  5,  6,  7,  8,  9};

template <class Type>
void FillTree(hhullen::BinTree<Type>& tree, std::vector<Type> upload_data) {
  for (Type& v : upload_data) {
    tree.Emplace(v);
  }
}

class TestClass {
 public:
  TestClass() : t{0} {}
  bool operator<(const TestClass& src) const { return src.t == 0; }

 private:
  int t;
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
  tree.Emplace(0.7);
  FillTree(tree, data_upload_1);
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

// // struct Aboba {
// //   bool a : 1, b : 1, c : 1, d : 1, e : 1, f : 1, g : 1, h : 1;
// // };

// // std::ostream& operator<<(std::ostream& out, const Aboba& aboba) {
// //   out << aboba.a << aboba.b << aboba.c << aboba.d << aboba.e << aboba.f
// //       << aboba.g << aboba.h;
// //   return out;
// // }

// // template <class T>
// // struct Node {
// //   T* data;
// //   Node *left, *right, *parent;
// // };

// // template <class Value, class Key, class KeyRetractor, class Comparator>
// // class Tree {
// //  private:
// //   KeyRetractor ret_;
// //   Comparator comp_;

// //   void aboba(const Key& k) {
// //     Value value;
// //     comp_(k, ret_(value));
// //   }
// // };

// // template <class T1, class T2>
// // struct RetMap {
// //   const T1& operator()(const std::pair<T1, T2>& t) const { return t.first;
// }
// // };

// // template <class T, class Key>
// // class map {
// //   using tree = Tree<std::pair<const Key, T>, Key, RetMap, std::less<Key>>;
// // };

// // template <class T>
// // struct Ret {
// //   const T& operator()(const T& t) const { return t; }
// // };

// // template <class Key>
// // class set {
// //   using tree = Tree<const Key, Key, Ret, std::less<Key>>;
// // };

// // std::ostream& operator<<(std::ostream& out, const int& aboba) {
// //   return out << "HUITA";
// // }

// // template <class T1, class T2>
// // std::ostream& operator<<(std::ostream& out, const std::pair<T1, T2>& p) {
// //   return out << '{' << p.first << ", " << p.second << '}';
// // }

// // template <class... Args>
// // std::ostream& operator<<(std::ostream& out, const std::map<Args...>& m) {
// //   out << '{';
// //   bool comma = false;
// //   for (const auto& el : m) {
// //     if (comma) out << ", ";
// //     comma = true;
// //     out << el;
// //   }
// //   return out << '}';
// // }

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
  FillTree(tree, data_upload_1);

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
  EXPECT_EQ(tree.Size(), data_upload_1.size());
  ++iter;
}

TEST(BinTree, Delete_not_existed) {
  hhullen::BinTree<double> tree;
  FillTree(tree, data_upload_1);

  hhullen::BinTree<double>::Iterator iter;
  iter = tree.Delete(999);
  EXPECT_TRUE(iter == tree.End());
  iter = tree.Delete(0.0001);
  EXPECT_TRUE(iter == tree.End());
}

TEST(BinTree, Delete_with_R_child) {
  hhullen::BinTree<double> tree;
  FillTree(tree, data_upload_1);

  hhullen::BinTree<double>::Iterator iter;
  iter = tree.Delete(0.7);
  EXPECT_EQ(*iter, 0.75);
  iter = tree.Delete(1.3);
  EXPECT_TRUE(iter == tree.End());
}

TEST(BinTree, Delete_with_L_child) {
  hhullen::BinTree<double> tree;
  FillTree(tree, data_upload_1);

  hhullen::BinTree<double>::Iterator iter;
  iter = tree.Delete(0.82);
  EXPECT_EQ(*iter, 0.9);
}

TEST(BinTree, Delete_with_NO_child) {
  hhullen::BinTree<double> tree;
  FillTree(tree, data_upload_1);

  hhullen::BinTree<double>::Iterator iter;
  iter = tree.Delete(0.75);
  EXPECT_EQ(*iter, 0.8);
  iter = tree.Delete(0.7);
  EXPECT_EQ(*iter, 0.8);
}

TEST(BinTree_Iterator, Iterator_prefix_INcrement_1) {
  hhullen::BinTree<double> tree;
  FillTree(tree, data_upload_1);

  hhullen::BinTree<double>::Iterator iter = tree.Begin();
  for (size_t i = 0; iter != tree.End(); ++iter, ++i) {
    EXPECT_EQ(data_result_1.at(i), *iter);
  }
  EXPECT_TRUE(iter == tree.End());
  ++iter;
  EXPECT_TRUE(iter == tree.End());
  ++iter;
  EXPECT_TRUE(iter == tree.End());
}

TEST(BinTree_Iterator, Iterator_prefix_INcrement_2) {
  hhullen::BinTree<double> tree;
  FillTree(tree, data_upload_2);

  hhullen::BinTree<double>::Iterator iter = tree.Begin();
  for (size_t i = 0; iter != tree.End(); ++iter, ++i) {
    EXPECT_EQ(data_result_2.at(i), *iter);
  }
  EXPECT_TRUE(iter == tree.End());
  ++iter;
  EXPECT_TRUE(iter == tree.End());
  ++iter;
  EXPECT_TRUE(iter == tree.End());
}

TEST(BinTree_Iterator, Iterator_postfix_INcrement_1) {
  hhullen::BinTree<double> tree;
  FillTree(tree, data_upload_1);

  hhullen::BinTree<double>::Iterator iter = tree.Begin();
  for (size_t i = 0; iter != tree.End(); iter++, ++i) {
    EXPECT_EQ(data_result_1.at(i), *iter);
  }
  EXPECT_TRUE(iter == tree.End());
  iter++;
  EXPECT_TRUE(iter == tree.End());
  iter++;
  EXPECT_TRUE(iter == tree.End());
}

TEST(BinTree_Iterator, Iterator_postfix_INcrement_2) {
  hhullen::BinTree<double> tree;
  FillTree(tree, data_upload_2);

  hhullen::BinTree<double>::Iterator iter = tree.Begin();
  for (size_t i = 0; iter != tree.End(); iter++, ++i) {
    EXPECT_EQ(data_result_2.at(i), *iter);
  }
  EXPECT_TRUE(iter == tree.End());
  iter++;
  EXPECT_TRUE(iter == tree.End());
  iter++;
  EXPECT_TRUE(iter == tree.End());
}

TEST(BinTree_Iterator, Iterator_prefix_DEcrement_1) {
  hhullen::BinTree<double> tree;
  FillTree(tree, data_upload_1);

  hhullen::BinTree<double>::Iterator iter = tree.End();
  --iter;
  for (size_t i = data_result_1.size() - 1; iter != tree.Begin(); --iter, --i) {
    EXPECT_EQ(data_result_1.at(i), *iter);
  }
  EXPECT_EQ(data_result_1.at(0), *iter);
  --iter;
  EXPECT_TRUE(iter == tree.Begin());
  --iter;
  EXPECT_TRUE(iter == tree.Begin());
}

TEST(BinTree_Iterator, Iterator_prefix_DEcrement_2) {
  hhullen::BinTree<double> tree;
  FillTree(tree, data_upload_2);

  hhullen::BinTree<double>::Iterator iter = tree.End();
  --iter;
  for (size_t i = data_result_2.size() - 1; iter != tree.Begin(); --iter, --i) {
    EXPECT_EQ(data_result_2.at(i), *iter);
  }
  EXPECT_EQ(data_result_2.at(0), *iter);
  --iter;
  EXPECT_TRUE(iter == tree.Begin());
  --iter;
  EXPECT_TRUE(iter == tree.Begin());
}

TEST(BinTree_Iterator, Iterator_postfix_DEcrement_1) {
  hhullen::BinTree<double> tree;
  FillTree(tree, data_upload_1);

  hhullen::BinTree<double>::Iterator iter = tree.End();
  iter--;
  for (size_t i = data_result_1.size() - 1; iter != tree.Begin(); iter--, --i) {
    EXPECT_EQ(data_result_1.at(i), *iter);
  }
  EXPECT_EQ(data_result_1.at(0), *iter);
  iter--;
  EXPECT_TRUE(iter == tree.Begin());
  iter--;
  EXPECT_TRUE(iter == tree.Begin());
}

TEST(BinTree_Iterator, Iterator_postfix_DEcrement_2) {
  // for (int j = 0; j < 100000; ++j) {
  hhullen::BinTree<double> tree;
  FillTree(tree, data_upload_2);

  hhullen::BinTree<double>::Iterator iter = tree.End();
  iter--;
  for (size_t i = data_result_2.size() - 1; iter != tree.Begin(); iter--, --i) {
    EXPECT_EQ(data_result_2.at(i), *iter);
  }
  EXPECT_EQ(data_result_2.at(0), *iter);
  iter--;
  EXPECT_TRUE(iter == tree.Begin());
  iter--;
  EXPECT_TRUE(iter == tree.Begin());
  // }
}