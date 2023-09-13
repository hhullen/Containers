#include "definition.h"

namespace hhullen {

template <class Value, comparable Key, class KeyRetractor, class Comparator>
BinTree<Value, Key, KeyRetractor, Comparator>::Iterator::Iterator()
    : node_ptr_{nullptr}, end_{nullptr} {}

template <class Value, comparable Key, class KeyRetractor, class Comparator>
BinTree<Value, Key, KeyRetractor, Comparator>::Iterator::Iterator(
    BinTree<Value, Key, KeyRetractor, Comparator>::Node* node, Node* end)
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
    GoToLeftEnd(selector_right);
    node_ptr_ = selector_right.get();
  } else {
    Node* parent_right = MakeStep(node_ptr_, Node::Relatives::Parent);
    parent_right = MakeStep(parent_right, Node::Relatives::Right);
    if (parent_right == node_ptr_) {
      node_ptr_ = MakeStep(node_ptr_, Node::Relatives::Parent);
      node_ptr_ = MakeStep(node_ptr_, Node::Relatives::Parent);
    } else {
      node_ptr_ = MakeStep(node_ptr_, Node::Relatives::Parent);
    }
    // parent?
    // where?
  }
  return *this;
}

template <class Value, comparable Key, class KeyRetractor, class Comparator>
BinTree<Value, Key, KeyRetractor, Comparator>::Iterator&
BinTree<Value, Key, KeyRetractor, Comparator>::Iterator::operator--() {
  return *this;
}

template <class Value, comparable Key, class KeyRetractor, class Comparator>
BinTree<Value, Key, KeyRetractor, Comparator>::Iterator
BinTree<Value, Key, KeyRetractor, Comparator>::Iterator::operator++(int) {}

template <class Value, comparable Key, class KeyRetractor, class Comparator>
BinTree<Value, Key, KeyRetractor, Comparator>::Iterator
BinTree<Value, Key, KeyRetractor, Comparator>::Iterator::operator--(int) {}

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
