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
  if (root_ != end_) {
    NodePtr selector = root_.get()->childs[0];
    for (; selector; selector = selector.get()->childs[0]) {
    }
    return BinTree<Key, Value>::Iterator(selector);
  } else {
    return BinTree<Key, Value>::Iterator(end_);
  }
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
  NodePtr found = Search(key);
  if (!found) {
    found = end_;
  }
  return BinTree<Key, Value>::Iterator(found);
}

template <comparable Key, class Value>
BinTree<Key, Value>::Iterator BinTree<Key, Value>::Emplace(const Key& key,
                                                           const Value& value) {
  NodePtr found = Search(key);
  if (found == end_) {
    SetNewNodeOnEnd(found, key, value);
  } else if (found) {
    found.get()->value = value;
  } else {
    const Key& last_existed = snake_.back()->key;
    NodePtr& child = snake_.back()->childs[last_existed < key];
    SetNewNodeOnNull(child, key, value);
  }
  return BinTree<Key, Value>::Iterator(found);
}

template <comparable Key, class Value>
void BinTree<Key, Value>::Delete(const Key& key) {}

template <comparable Key, class Value>
size_t BinTree<Key, Value>::Size() {
  return size_;
}

// private methods

template <comparable Key, class Value>
void BinTree<Key, Value>::SetNewNodeOnEnd(NodePtr& node, const Key& key,
                                          const Value& value) {
  node.get()->key = key;
  node.get()->value = value;
  node.get()->childs[1].reset(new Node());
  end_ = node.get()->childs[1];
}

template <comparable Key, class Value>
void BinTree<Key, Value>::SetNewNodeOnNull(NodePtr& node, const Key& key,
                                           const Value& value) {
  node.reset(new Node());
  node.get()->key = key;
  node.get()->value = value;
}

template <comparable Key, class Value>
BinTree<Key, Value>::NodePtr BinTree<Key, Value>::Search(const Key& key) {
  snake_.clear();
  NodePtr selector = root_;
  for (; selector && selector != end_;) {
    snake_.emplace_back(selector.get());
    const Key& selected = selector.get()->key;
    if (IsKeysEQ(key, selected)) {
      break;
    }
    selector = selector.get()->childs[selected < key];
  }
  return selector;
}

template <comparable Key, class Value>
bool BinTree<Key, Value>::IsKeysEQ(const Key& key1, const Key& key2) {
  return !(key1 < key2 || key2 < key1);
}

}  // namespace hhullen
