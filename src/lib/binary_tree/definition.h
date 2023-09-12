#ifndef SRC_LIB_BINARY_TREE_DEFINITION_H_
#define SRC_LIB_BINARY_TREE_DEFINITION_H_

#include <functional>
#include <iostream>
#include <memory>
#include <vector>

namespace hhullen {

enum Childs : char { Left = 0, Right, Parent };

template <class T>
concept comparable = requires(T val) { val < val; };

template <comparable Key, class Value>
class BinTree {
  struct Node;
  using NodePtr = std::shared_ptr<Node>;

 public:
  class Iterator
      : public std::iterator<std::input_iterator_tag, std::pair<Key, Value>> {
   public:
    Iterator();
    Iterator(Node* node);
    std::pair<Key, Value> operator*() const;
    Iterator& operator++();
    Iterator& operator--();
    Iterator operator++(int);
    Iterator operator--(int);
    bool operator==(const Iterator& other) const;
    bool operator!=(const Iterator& other) const;

   private:
    Node* node_ptr_;
  };
  BinTree();
  ~BinTree();

  Iterator Begin();
  Iterator End();
  void Clear();
  bool Contains(const Key& key);
  bool Empty();
  Iterator Find(const Key& key);
  Iterator Emplace(const Key& key, const Value& value);
  void Delete(const Key& key);
  size_t Size();

 private:
  struct Node {
    Key key;
    Value value;
    NodePtr childs[3];
  };
  NodePtr begin_, root_, end_;
  size_t size_;

  void SetNewNodeOnNull(NodePtr& selector, const Key& key, const Value& value);
  void SetNewNodeOnEnd(NodePtr& selector, const Key& key, const Value& value);
  NodePtr Search(const Key& key);
  bool IsKeysEQ(const Key& key1, const Key& key2);
};

}  // namespace hhullen

#endif  // SRC_LIB_BINARY_TREE_DEFINITION_H_
