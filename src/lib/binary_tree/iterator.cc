#include "definition.h"

namespace hhullen {

template <comparable Key, class Value>
BinTree<Key, Value>::Iterator::Iterator(NodePtr node) : node_ptr_{node.get()} {}

template <comparable Key, class Value>
std::pair<Key, Value>& BinTree<Key, Value>::Iterator::operator*() const {
  return {(*node_ptr_).key, (*node_ptr_).value};
}

template <comparable Key, class Value>
BinTree<Key, Value>::Iterator& BinTree<Key, Value>::Iterator::operator++() {}

template <comparable Key, class Value>
BinTree<Key, Value>::Iterator& BinTree<Key, Value>::Iterator::operator--() {}

template <comparable Key, class Value>
BinTree<Key, Value>::Iterator BinTree<Key, Value>::Iterator::operator++(int) {}

template <comparable Key, class Value>
BinTree<Key, Value>::Iterator BinTree<Key, Value>::Iterator::operator--(int) {}

template <comparable Key, class Value>
bool BinTree<Key, Value>::Iterator::operator==(
    const BinTree<Key, Value>::Iterator& other) const {
  return node_ptr_ == other.node_ptr_;
}

template <comparable Key, class Value>
bool BinTree<Key, Value>::Iterator::operator!=(
    const BinTree<Key, Value>::Iterator& other) const {
  return node_ptr_ != other.node_ptr_;
}

}  // namespace hhullen
