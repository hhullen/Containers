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
  NodePtr found = Search(key);
  if (!found) {
    found = end_;
  }
  return BinTree<Key, Value>::Iterator(found);
}

template <comparable Key, class Value>
BinTree<Key, Value>::Iterator BinTree<Key, Value>::Emplace(const Key& key,
                                                           const Value& value) {
  snake_.clear();
  // std::cout << "EMPLACE " << key << "\n";
  NodePtr selector = root_;
  // std::cout << "SELECTOR " << selector.get()->key << "\n";
  for (; selector && selector != end_;) {
    Key& selected = selector.get()->key;
    if (selected < key || key < selected) {
      // std::cout << "IS R " << (selected < key) << "\n";
      // std::cout << "sel " << selected << " key " << key << "\n";
      selector = selector.get()->childs[selected < key];
      snake_.emplace_back(selector.get());
    } else {
      std::cout << "EQ\n";
      selector.get()->value = value;
      return BinTree<Key, Value>::Iterator(selector);
    }
  }

  if (selector == end_) {
    NodePtr& child_r = selector.get()->childs[1];
    child_r.reset(new Node());
    end_ = child_r;
    // std::cout << " Move END\n\n";
  } else {
    // std::cout << "NEW\n\n";
    selector.reset(new Node());
  }
  selector.get()->key = key;
  selector.get()->value = value;
  return BinTree<Key, Value>::Iterator(selector);
}

template <comparable Key, class Value>
void BinTree<Key, Value>::Delete(const Key& key) {}

template <comparable Key, class Value>
size_t BinTree<Key, Value>::Size() {
  return size_;
}

// private methods

template <comparable Key, class Value>
BinTree<Key, Value>::NodePtr BinTree<Key, Value>::Search(const Key& key) {
  NodePtr selector = root_;
  for (; selector && selector != end_;) {
    Key& selected = selector.get()->key;
    if (selected < key || key < selected) {
      selector = selector.get()->childs[selected < key];
      std::cout << "IS R " << (selected < key) << "\n";
      std::cout << "sel " << selected << " key " << key << " SER " << selector
                << "\n";
      std::cout << "NOT\n";
    } else {
      std::cout << "EQ\n";
      break;
    }
  }
  std::cout << "\n";
  return selector;
}

}  // namespace hhullen
