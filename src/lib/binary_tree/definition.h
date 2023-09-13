#ifndef SRC_LIB_BINARY_TREE_DEFINITION_H_
#define SRC_LIB_BINARY_TREE_DEFINITION_H_

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
    Value value;
    enum Relatives : char { Left = 0, Right, Parent };
    NodePtr relatives[3];
  };
  class Iterator : public std::iterator<std::input_iterator_tag, Value> {
   public:
    Iterator();
    Iterator(Node* node, Node* end);
    Value operator*() const;
    Iterator& operator++();
    Iterator operator++(int);
    Iterator& operator--();
    Iterator operator--(int);
    bool operator==(const Iterator& other) const;
    bool operator!=(const Iterator& other) const;

   private:
    Node *node_ptr_, *end_, *begin_;

    Node* MakeStep(Node* node, char direction);
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

  static void GoToEnd(NodePtr& selector, char direction);
  void SetNewNodeOnNull(NodePtrPair& found, const Value& value);
  void SetNewNodeOnEnd(NodePtr& selector, const Value& value);
  NodePtrPair Seek(const Key& key);
  bool IsEQ(const Key& key1, const Key& key2);
};

}  // namespace hhullen

#endif  // SRC_LIB_BINARY_TREE_DEFINITION_H_
