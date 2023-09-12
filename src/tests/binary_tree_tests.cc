#include <gtest/gtest.h>
// #include <lib/binary_tree/binary_tree.h>
#include <lib/binary_tree/definition.h>

#include <map>

class Test1 {
 public:
  Test1() {}
  bool operator<(const Test1& src) const { return true; }
  void operator()() const { return; }
};

TEST(BinTree, Constructor) {
  // hhullen::BinTree<char, int> tree1;
  hhullen::BinTree<Test1, int, Test1> tree2;
}

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

// std::ostream& operator<<(std::ostream& out, const Test1& aboba) {
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

// TEST(BinTree, Emplace_simple) {
//   std::map<Test1, int> m{{Test1(), 5}};
// std::map<int, int> m2(m.begin(), m.end());
// std::cout << m << std::endl << m2 << std::endl;
// m.begin()->first = 50;
// std::cout << m << std::endl << m2 << std::endl;

// std::cout << sizeof(Aboba);
// Aboba aboba;
// std::cout << aboba << std::endl;
// aboba.a = true;
// std::cout << aboba;
// bool& ref = aboba.a;
// std::cout << std::endl << ref;
// hhullen::BinTree<double, int> tree;
// tree.Emplace(1, 1);
// tree.Emplace(0.5, 2);
// tree.Emplace(1.5, 3);
// hhullen::BinTree<double, int>::Iterator iter;
// iter = tree.Find(1);
// EXPECT_EQ((*iter).second, 1);
// iter = tree.Find(0.5);
// EXPECT_EQ((*iter).second, 2);
// iter = tree.Find(1.5);
// EXPECT_EQ((*iter).second, 3);
// tree.Emplace(1.5, 4);
// iter = tree.Find(1.5);
// EXPECT_EQ((*iter).second, 4);
// }
