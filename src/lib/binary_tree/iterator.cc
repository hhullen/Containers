#include "definition.h"

namespace hhullen {

template <class Value, comparable Key, class KeyRetractor, class Comparator>
BinTree<Value, Key, KeyRetractor, Comparator>::Iterator::Iterator()
    : node_ptr_{nullptr} {}

template <class Value, comparable Key, class KeyRetractor, class Comparator>
BinTree<Value, Key, KeyRetractor, Comparator>::Iterator::Iterator(
    BinTree<Value, Key, KeyRetractor, Comparator>::Node* node)
    : node_ptr_{node} {}

template <class Value, comparable Key, class KeyRetractor, class Comparator>
Value BinTree<Value, Key, KeyRetractor, Comparator>::Iterator::operator*()
    const {
  return node_ptr_->value;
}

template <class Value, comparable Key, class KeyRetractor, class Comparator>
BinTree<Value, Key, KeyRetractor, Comparator>::Iterator&
BinTree<Value, Key, KeyRetractor, Comparator>::Iterator::operator++() {
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

}  // namespace hhullen
