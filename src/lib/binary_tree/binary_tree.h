#ifndef SRC_LIB_BINARY_TREE_BINARY_TREE_H_
#define SRC_LIB_BINARY_TREE_BINARY_TREE_H_

#include <functional>
#include <iostream>
#include <memory>
#include <vector>

namespace hhullen {

template <class T>
concept comparable = requires(T val) { val < val; };

template <comparable Key, class Value>
class BinTree {
  class Node;
  using NodePtr = std::shared_ptr<Node>;
  constexpr int max_tree_height_x64 = 90;

 public:
  class Iterator : public std::iterator {
    explicit Iterator(NodePtr node) { node_ptr_ = &end_; }

   public:
    std::pair<Key, Value>& operator*() const;
    Iterator& operator++();
    Iterator& operator--();
    Iterator operator++(int);
    Iterator operator--(int);
    bool operator==(const Iterator& other) const;
    bool operator!=(const Iterator& other) const;

   private:
    NodePtr* node_ptr_;
  };
  BinTree() : size_{0}, root_{new Node()}, end_{root_} {
    snake_.reserve(max_tree_height_x64);
  }

  Iterator Begin();
  Iterator End();
  void Clear();
  bool Contains(const Key& key);
  bool Empty();
  Iterator Emplace(const Key& key, const Value& value);
  Iterator Find(const Key& key);
  Iterator Delete(const Key& key);
  size_t Size();

 private:
  class Node {
    Key key;
    Value value;
    NodePtr childs[2];
  };
  NodePtr root_, end_;
  size_t size_;
  std::vector<Node*> snake_;
};

}  // namespace hhullen

#endif  // SRC_LIB_BINARY_TREE_BINARY_TREE_H_
