#ifndef SRC_LIB_BINARY_TREE_DEFINITION_H_
#define SRC_LIB_BINARY_TREE_DEFINITION_H_

#define BIN_TREE_DEF BinTree<Value, Key, KeyRetractor, Comparator>
#define TEMPLATE_DEF \
  template <class Value, comparable Key, class KeyRetractor, class Comparator>

#include <functional>
#include <iostream>
#include <memory>
#include <vector>

namespace hhullen {

template <class T>
concept comparable = requires(T val) { val < val; };

template <class T1>
class BinTreeKeyRetractor {
 public:
  const T1& operator()(const T1& value) const { return value; }
};

template <class Value, comparable Key = Value,
          class KeyRetractor = BinTreeKeyRetractor<Value>,
          class Comparator = std::less<Key>>
class BinTree {
 public:
  struct Node;
  using NodePtr = std::shared_ptr<Node>;
  using NodePtrPair = std::pair<NodePtr, NodePtr>;
  struct Node {
    ~Node() {}
    Value value;
    enum Relatives { Left = 0, Right, Parent };
    NodePtr relatives[3];
  };
  class Iterator {
   public:
    Iterator();
    Iterator(NodePtr node, NodePtr end);
    Value operator*() const;
    Iterator& operator++();
    Iterator operator++(int);
    Iterator& operator--();
    Iterator operator--(int);
    bool operator==(const Iterator& other) const;
    bool operator!=(const Iterator& other) const;

   private:
    NodePtr node_ptr_, end_;
  };
  BinTree();
  ~BinTree();

  Iterator Begin();
  Iterator End();
  void Clear();
  bool Contains(const Key& key);
  bool Empty();
  Iterator Find(const Key& key);
  Iterator Emplace(const Value& value);
  Iterator Delete(const Key& key);
  size_t Size();

 private:
  NodePtr root_, end_;
  size_t size_;

  void SetNewNodeOnNull(NodePtrPair& nodes_pair, const Value& value);
  void SetNewNodeOnEnd(NodePtr& selector, const Value& value);
  NodePtrPair Seek(const Key& key);
  void DeleteWithNoLeftChild(NodePtr& node);
  void DeleteWithNoRightChild(NodePtr& node);
  void DeleteWithNoChilds(NodePtr& node);

  static bool IsEQ(const Key& key1, const Key& key2);
  static NodePtr MakeStep(const NodePtr& node, size_t direction);
  static void GoToEnd(NodePtr& selector, size_t direction);
};

}  // namespace hhullen

#include "binary_tree.cc"
#include "iterator.cc"

#endif  // SRC_LIB_BINARY_TREE_DEFINITION_H_
