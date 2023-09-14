#ifndef SRC_LIB_BINARY_TREE_DEFINITION_H_
#include "definition.h"
#endif  // SRC_LIB_BINARY_TREE_DEFINITION_H_

namespace hhullen {

template <class Value, comparable Key, class KeyRetractor, class Comparator>
BinTree<Value, Key, KeyRetractor, Comparator>::Iterator::Iterator()
    : node_ptr_{nullptr}, end_{nullptr} {}

template <class Value, comparable Key, class KeyRetractor, class Comparator>
BinTree<Value, Key, KeyRetractor, Comparator>::Iterator::Iterator(NodePtr node,
                                                                  NodePtr end)
    : node_ptr_{node}, end_{end} {}

template <class Value, comparable Key, class KeyRetractor, class Comparator>
Value BinTree<Value, Key, KeyRetractor, Comparator>::Iterator::operator*()
    const {
  return node_ptr_->value;
}

template <class Value, comparable Key, class KeyRetractor, class Comparator>
BinTree<Value, Key, KeyRetractor, Comparator>::Iterator&
BinTree<Value, Key, KeyRetractor, Comparator>::Iterator::operator++() {
  if (node_ptr_ == end_) {
    return *this;
  }
  NodePtr selector_right = node_ptr_->relatives[Node::Right];
  if (selector_right) {
    GoToEnd(selector_right, Node::Left);
    node_ptr_ = selector_right;
  } else {
    NodePtr right_of_parent = MakeStep(node_ptr_, Node::Parent);
    right_of_parent = MakeStep(right_of_parent, Node::Right);
    if (right_of_parent == node_ptr_) {
      NodePtr parent_of_current = MakeStep(node_ptr_, Node::Parent);
      for (; parent_of_current &&
             Comparator()(KeyRetractor()(parent_of_current->value),
                          KeyRetractor()(node_ptr_->value));
           parent_of_current = MakeStep(node_ptr_, Node::Parent)) {
        node_ptr_ = parent_of_current;
      }
    }
    node_ptr_ = MakeStep(node_ptr_, Node::Parent);
  }
  return *this;
}

template <class Value, comparable Key, class KeyRetractor, class Comparator>
BinTree<Value, Key, KeyRetractor, Comparator>::Iterator
BinTree<Value, Key, KeyRetractor, Comparator>::Iterator::operator++(int) {
  BinTree<Value, Key, KeyRetractor, Comparator>::Iterator iter(*this);
  ++(*this);
  return iter;
}

template <class Value, comparable Key, class KeyRetractor, class Comparator>
BinTree<Value, Key, KeyRetractor, Comparator>::Iterator&
BinTree<Value, Key, KeyRetractor, Comparator>::Iterator::operator--() {
  NodePtr selector_left = node_ptr_->relatives[Node::Left];
  if (selector_left) {
    GoToEnd(selector_left, Node::Right);
    node_ptr_ = selector_left;
  } else {
    NodePtr current = node_ptr_;
    NodePtr left_of_parent = MakeStep(current, Node::Parent);
    left_of_parent = MakeStep(left_of_parent, Node::Left);
    if (left_of_parent == current) {
      NodePtr parent_of_current = MakeStep(current, Node::Parent);
      for (; parent_of_current &&
             Comparator()(KeyRetractor()(current->value),
                          KeyRetractor()(parent_of_current->value));
           parent_of_current = MakeStep(current, Node::Parent)) {
        current = parent_of_current;
      }
    }
    current = MakeStep(current, Node::Parent);
    if (!current) {
      return *this;
    }
    node_ptr_ = current;
  }
  return *this;
}

template <class Value, comparable Key, class KeyRetractor, class Comparator>
BinTree<Value, Key, KeyRetractor, Comparator>::Iterator
BinTree<Value, Key, KeyRetractor, Comparator>::Iterator::operator--(int) {
  BinTree<Value, Key, KeyRetractor, Comparator>::Iterator iter(*this);
  --(*this);
  return iter;
}

template <class Value, comparable Key, class KeyRetractor, class Comparator>
bool BinTree<Value, Key, KeyRetractor, Comparator>::Iterator::operator==(
    const BinTree<Value, Key, KeyRetractor, Comparator>::Iterator& other)
    const {
  return node_ptr_ == other.node_ptr_;
}

template <class Value, comparable Key, class KeyRetractor, class Comparator>
bool BinTree<Value, Key, KeyRetractor, Comparator>::Iterator::operator!=(
    const BinTree<Value, Key, KeyRetractor, Comparator>::Iterator& other)
    const {
  return node_ptr_ != other.node_ptr_;
}

}  // namespace hhullen
