#include "definition.h"

namespace hhullen {

template <class Value, comparable Key, class KeyRetractor, class Comparator>
BinTree<Value, Key, KeyRetractor, Comparator>::BinTree()
    : size_{0}, root_{new Node()}, end_{root_} {}

template <class Value, comparable Key, class KeyRetractor, class Comparator>
BinTree<Value, Key, KeyRetractor, Comparator>::~BinTree() {}

template <class Value, comparable Key, class KeyRetractor, class Comparator>
BinTree<Value, Key, KeyRetractor, Comparator>::Iterator
BinTree<Value, Key, KeyRetractor, Comparator>::Begin() {
  if (root_ != end_) {
    NodePtr selector = root_;
    GoToEnd(selector, Node::Relatives::Left);
    return BinTree<Value, Key, KeyRetractor, Comparator>::Iterator(
        selector.get(), end_.get());
  } else {
    return BinTree<Value, Key, KeyRetractor, Comparator>::Iterator(end_.get(),
                                                                   end_.get());
  }
}

template <class Value, comparable Key, class KeyRetractor, class Comparator>
BinTree<Value, Key, KeyRetractor, Comparator>::Iterator
BinTree<Value, Key, KeyRetractor, Comparator>::End() {
  return BinTree<Value, Key, KeyRetractor, Comparator>::Iterator(end_.get(),
                                                                 end_.get());
}

template <class Value, comparable Key, class KeyRetractor, class Comparator>
void BinTree<Value, Key, KeyRetractor, Comparator>::Clear() {
  root_.reset(new Node());
  end_ = root_;
  size_ = 0;
}

template <class Value, comparable Key, class KeyRetractor, class Comparator>
bool BinTree<Value, Key, KeyRetractor, Comparator>::Contains(const Key& key) {
  if (Find(key) != End()) {
    return true;
  }
  return false;
}

template <class Value, comparable Key, class KeyRetractor, class Comparator>
bool BinTree<Value, Key, KeyRetractor, Comparator>::Empty() {
  return size_ == 0;
}

template <class Value, comparable Key, class KeyRetractor, class Comparator>
BinTree<Value, Key, KeyRetractor, Comparator>::Iterator
BinTree<Value, Key, KeyRetractor, Comparator>::Find(const Key& key) {
  NodePtr found = Seek(key).second;
  if (!found) {
    found = end_;
  }
  return BinTree<Value, Key, KeyRetractor, Comparator>::Iterator(found.get(),
                                                                 end_.get());
}

template <class Value, comparable Key, class KeyRetractor, class Comparator>
BinTree<Value, Key, KeyRetractor, Comparator>::Iterator
BinTree<Value, Key, KeyRetractor, Comparator>::Emplace(const Value& value) {
  const Key& key = KeyRetractor()(value);
  NodePtrPair found = Seek(key);
  if (found.second == end_) {
    SetNewNodeOnEnd(found.second, value);
    ++size_;
  } else if (found.second) {
    found.second.get()->value = value;
  } else {
    SetNewNodeOnNull(found, value);
    ++size_;
  }
  return BinTree<Value, Key, KeyRetractor, Comparator>::Iterator(
      found.second.get(), end_.get());
}

template <class Value, comparable Key, class KeyRetractor, class Comparator>
BinTree<Value, Key, KeyRetractor, Comparator>::Iterator
BinTree<Value, Key, KeyRetractor, Comparator>::Delete(const Key& key) {
  NodePtrPair found = Seek(key);
  if (!found.second || found.second == end_) {
    return BinTree<Value, Key, KeyRetractor, Comparator>::Iterator(end_.get(),
                                                                   end_.get());
  }

  return BinTree<Value, Key, KeyRetractor, Comparator>::Iterator();
}

template <class Value, comparable Key, class KeyRetractor, class Comparator>
size_t BinTree<Value, Key, KeyRetractor, Comparator>::Size() {
  return size_;
}

// /*
//     private methods
// */

template <class Value, comparable Key, class KeyRetractor, class Comparator>
void BinTree<Value, Key, KeyRetractor, Comparator>::GoToEnd(
    BinTree<Value, Key, KeyRetractor, Comparator>::NodePtr& selector,
    char direction) {
  for (; selector.get()->relatives[direction];
       selector = selector.get()->relatives[direction]) {
  }
}

template <class Value, comparable Key, class KeyRetractor, class Comparator>
void BinTree<Value, Key, KeyRetractor, Comparator>::SetNewNodeOnEnd(
    NodePtr& node, const Value& value) {
  node.get()->value = value;
  node.get()->relatives[Node::Relatives::Right].reset(new Node());
  end_ = node.get()->relatives[Node::Relatives::Right];
  end_.get()->relatives[Node::Relatives::Parent] = node;
}

template <class Value, comparable Key, class KeyRetractor, class Comparator>
void BinTree<Value, Key, KeyRetractor, Comparator>::SetNewNodeOnNull(
    BinTree<Value, Key, KeyRetractor, Comparator>::NodePtrPair& found,
    const Value& value) {
  bool relative_selector = Comparator()(
      KeyRetractor()(found.first.get()->value), KeyRetractor()(value));

  found.first.get()->relatives[relative_selector].reset(new Node());
  found.second = found.first.get()->relatives[relative_selector];

  found.second.get()->value = value;
  found.second.get()->relatives[Node::Relatives::Parent] = found.first;
}

template <class Value, comparable Key, class KeyRetractor, class Comparator>
BinTree<Value, Key, KeyRetractor, Comparator>::NodePtrPair
BinTree<Value, Key, KeyRetractor, Comparator>::Seek(const Key& key) {
  NodePtr selector = root_, previous;
  for (; selector && selector != end_;) {
    previous = selector;
    const Key& selected = KeyRetractor()(selector.get()->value);
    if (IsEQ(key, selected)) {
      break;
    }
    selector = selector.get()->relatives[Comparator()(selected, key)];
  }
  return {previous, selector};
}

template <class Value, comparable Key, class KeyRetractor, class Comparator>
bool BinTree<Value, Key, KeyRetractor, Comparator>::IsEQ(const Key& key1,
                                                         const Key& key2) {
  return !(Comparator()(key1, key2) || Comparator()(key2, key1));
}

}  // namespace hhullen
