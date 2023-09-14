#include "definition.h"

namespace hhullen {

template <class Value, comparable Key, class KeyRetractor, class Comparator>
BinTree<Value, Key, KeyRetractor, Comparator>::Iterator::Iterator()
    : node_ptr_{nullptr}, end_{nullptr} {}

template <class Value, comparable Key, class KeyRetractor, class Comparator>
BinTree<Value, Key, KeyRetractor, Comparator>::Iterator::Iterator(Node* node,
                                                                  Node* end)
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
  NodePtr selector_right = node_ptr_->relatives[Node::Relatives::Right];
  if (selector_right) {
    GoToEnd(selector_right, Node::Relatives::Left);
    node_ptr_ = selector_right.get();
  } else {
    Node* right_of_parent = MakeStep(node_ptr_, Node::Relatives::Parent);
    right_of_parent = MakeStep(right_of_parent, Node::Relatives::Right);
    if (right_of_parent == node_ptr_) {
      Node* parent_of_current = MakeStep(node_ptr_, Node::Relatives::Parent);
      for (; parent_of_current &&
             Comparator()(KeyRetractor()(parent_of_current->value),
                          KeyRetractor()(node_ptr_->value));
           parent_of_current = MakeStep(node_ptr_, Node::Relatives::Parent)) {
        node_ptr_ = parent_of_current;
      }
    }
    node_ptr_ = MakeStep(node_ptr_, Node::Relatives::Parent);
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
  NodePtr selector_left = node_ptr_->relatives[Node::Relatives::Left];
  if (selector_left) {
    GoToEnd(selector_left, Node::Relatives::Right);
    node_ptr_ = selector_left.get();
  } else {
    Node* current = node_ptr_;
    Node* left_of_parent = MakeStep(current, Node::Relatives::Parent);
    left_of_parent = MakeStep(left_of_parent, Node::Relatives::Left);
    if (left_of_parent == current) {
      Node* parent_of_current = MakeStep(current, Node::Relatives::Parent);
      for (; parent_of_current &&
             Comparator()(KeyRetractor()(current->value),
                          KeyRetractor()(parent_of_current->value));
           parent_of_current = MakeStep(current, Node::Relatives::Parent)) {
        current = parent_of_current;
      }
    }
    current = MakeStep(current, Node::Relatives::Parent);
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

template <class Value, comparable Key, class KeyRetractor, class Comparator>
BinTree<Value, Key, KeyRetractor, Comparator>::Node*
BinTree<Value, Key, KeyRetractor, Comparator>::Iterator::MakeStep(
    Node* node, char direction) {
  return node->relatives[direction].get();
}

}  // namespace hhullen
