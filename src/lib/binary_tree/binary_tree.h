#ifndef SRC_LIB_BINARY_TREE_DEFINITION_H_
#define SRC_LIB_BINARY_TREE_DEFINITION_H_

#include <functional>
#include <iostream>
#include <memory>
#include <vector>

namespace hhullen {

#define BIN_TREE_DEF BinTree<Value, Key, KeyRetractor, Comparator>
#define TEMPLATE_DEF \
  template <class Value, class Key, class KeyRetractor, class Comparator>

template <class T1>
class BinTreeKeyRetractor {
 public:
  const T1& operator()(const T1& value) const { return value; }
};

template <class Value, class Key = Value,
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
    enum Relatives : size_t { Left = 0, Right, Parent };
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

  void OutputTreeStruct(std::ostream& os);

 private:
  NodePtr root_, end_;
  size_t size_;

  void SetNewNodeOnNull(NodePtrPair& nodes_pair, const Value& value);
  void SetNewNodeOnEnd(NodePtr& selector, const Value& value);
  NodePtrPair Seek(const Key& key);
  void ReplaceNode(NodePtr& to_replace, NodePtr& src);
  void ReplaceNodeRelative(NodePtr& to_replace, NodePtr& replacer,
                           size_t relative);
  void DeleteWithNoChilds(NodePtr& node);
  void DeleteWithBothChilds(NodePtr& node);
  size_t CalculateHeight(const NodePtr&);
  NodePtr& GetSelfFromNodeParent(NodePtr& node);

  static bool IsEQ(const Key& key1, const Key& key2);
  static NodePtr& GetRelative(const NodePtr& node, size_t direction);
  static void GoToEnd(NodePtr& selector, size_t direction);
};

}  // namespace hhullen

#include "binary_tree.cc"
#include "iterator.cc"

#endif  // SRC_LIB_BINARY_TREE_DEFINITION_H_
