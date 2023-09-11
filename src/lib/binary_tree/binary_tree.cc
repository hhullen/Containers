#include "binary_tree.h"

namespace hhullen {

template <comparable Key, class Value>
BinTree<Key, Value>::Iterator BinTree<Key, Value>::Begin() {
  return BinTree<Key, Value>::Iterator(root_);
}

template <comparable Key, class Value>
BinTree<Key, Value>::Iterator BinTree<Key, Value>::End() {
  return BinTree<Key, Value>::Iterator(end_);
}

template <comparable Key, class Value>
void BinTree<Key, Value>::Clear() {
  root_.reset(new Node());
  end_ = root_;
}

template <comparable Key, class Value>
bool BinTree<Key, Value>::Contains(const Key& key) {
  return false;
}

template <comparable Key, class Value>
bool BinTree<Key, Value>::Empty() {
  return size_ == 0;
}

template <comparable Key, class Value>
BinTree<Key, Value>::Iterator BinTree<Key, Value>::Emplace(const Key& key,
                                                           const Value& value) {
}

template <comparable Key, class Value>
BinTree<Key, Value>::Iterator BinTree<Key, Value>::Find(const Key& key) {}

template <comparable Key, class Value>
BinTree<Key, Value>::Iterator BinTree<Key, Value>::Delete(const Key& key) {}

template <comparable Key, class Value>
size_t BinTree<Key, Value>::Size() {
  return size_;
}

template <comparable Key, class Value>
std::pair<Key, Value>& BinTree<Key, Value>::Iterator::operator*() const {}

template <comparable Key, class Value>
BinTree<Key, Value>::Iterator BinTree<Key, Value>::Iterator::operator++() {}

template <comparable Key, class Value>
BinTree<Key, Value>::Iterator BinTree<Key, Value>::Iterator::operator--() {}

template <comparable Key, class Value>
BinTree<Key, Value>::Iterator BinTree<Key, Value>::Iterator::operator++(int) {}

template <comparable Key, class Value>
BinTree<Key, Value>::Iterator BinTree<Key, Value>::Iterator::operator--(int) {}

template <comparable Key, class Value>
bool BinTree<Key, Value>::Iterator::operator==(
    const BinTree<Key, Value>::Iterator& other) const {
  return false;
}

template <comparable Key, class Value>
bool BinTree<Key, Value>::Iterator::operator!=(
    const BinTree<Key, Value>::Iterator& other) const {
  return false;
}

}  // namespace hhullen
