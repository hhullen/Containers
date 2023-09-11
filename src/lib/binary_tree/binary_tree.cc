#include "definition.h"

namespace hhullen {

template <comparable Key, class Value>
BinTree<Key, Value>::BinTree() : size_{0}, root_{new Node()}, end_{root_} {
  snake_.reserve(max_tree_height_x64);
}

template <comparable Key, class Value>
BinTree<Key, Value>::~BinTree() {}

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
  size_ = 0;
}

template <comparable Key, class Value>
bool BinTree<Key, Value>::Contains(const Key& key) {
  if (Find(key) != End()) {
    return true;
  }
  return false;
}

template <comparable Key, class Value>
bool BinTree<Key, Value>::Empty() {
  return size_ == 0;
}

template <comparable Key, class Value>
BinTree<Key, Value>::Iterator BinTree<Key, Value>::Find(const Key& key) {
  NodePtr selector = root_;
  for (; selector && selector != end_;) {
    Key& selected = selector.get()->key;
    if (selected < key || key < selected) {
      selector = selector.get()->childs[selected < key];
    } else {
      return BinTree<Key, Value>::Iterator(selector);
    }
  }
  return BinTree<Key, Value>::Iterator(end_);
}

template <comparable Key, class Value>
BinTree<Key, Value>::Iterator BinTree<Key, Value>::Emplace(const Key& key,
                                                           const Value& value) {
  snake_.clear();
  NodePtr selector = root_;
  for (; selector && selector != end_;) {
    Key& selected = selector.get()->key;
    if (selected < key || key < selected) {
      selector = selector.get()->childs[selected < key];
      snake_.emplace_back(selector.get());
    } else {
      selector.get()->value = value;
      return BinTree<Key, Value>::Iterator(selector);
    }
  }

  if (selector == end_) {
    NodePtr& child_r = selector.get()->childs[1];
    child_r.reset(new Node());
  } else {
    selector.reset(new Node());
  }
  selector.get()->value = value;
  selector.get()->key = key;
  return BinTree<Key, Value>::Iterator(selector);
}

template <comparable Key, class Value>
void BinTree<Key, Value>::Delete(const Key& key) {}

template <comparable Key, class Value>
size_t BinTree<Key, Value>::Size() {
  return size_;
}

}  // namespace hhullen
