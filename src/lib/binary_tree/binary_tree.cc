#ifndef SRC_LIB_BINARY_TREE_DEFINITION_H_
#include "binary_tree.h"
#endif  // SRC_LIB_BINARY_TREE_DEFINITION_H_

namespace hhullen {

TEMPLATE_DEF
BIN_TREE_DEF::BinTree() : root_{new Node()}, end_{root_}, size_{0} {}

TEMPLATE_DEF
BIN_TREE_DEF::~BinTree() {}

TEMPLATE_DEF
BIN_TREE_DEF::Iterator BIN_TREE_DEF::Begin() {
  if (root_ != end_) {
    NodePtr selector = root_;
    GoToEnd(selector, Node::Left);
    return Iterator(selector, end_);
  } else {
    return Iterator(end_, end_);
  }
}

TEMPLATE_DEF
BIN_TREE_DEF::Iterator BIN_TREE_DEF::End() { return Iterator(end_, end_); }

TEMPLATE_DEF
void BIN_TREE_DEF::Clear() {
  root_.reset(new Node());
  end_ = root_;
  size_ = 0;
}

TEMPLATE_DEF
bool BIN_TREE_DEF::Contains(const Key& key) {
  if (Find(key) != End()) {
    return true;
  }
  return false;
}

TEMPLATE_DEF
bool BIN_TREE_DEF::Empty() { return size_ == 0; }

TEMPLATE_DEF
BIN_TREE_DEF::Iterator BIN_TREE_DEF::Find(const Key& key) {
  NodePtr found = Seek(key).second;
  if (!found) {
    found = end_;
  }
  return Iterator(found, end_);
}

TEMPLATE_DEF
BIN_TREE_DEF::Iterator BIN_TREE_DEF::Emplace(const Value& value) {
  const Key key = KeyRetractor()(value);
  NodePtrPair found = Seek(key);
  if (found.second == end_) {
    SetNewNodeOnEnd(found.second, value);
    ++size_;
  } else if (found.second) {
    found.second->value = value;
  } else {
    SetNewNodeOnNull(found, value);
    ++size_;
  }
  return Iterator(found.second, end_);
}

TEMPLATE_DEF
BIN_TREE_DEF::Iterator BIN_TREE_DEF::Delete(const Key& key) {
  NodePtr found = Seek(key).second;
  if (!found || found == end_) {
    return Iterator(end_, end_);
  }
  Iterator next = ++Iterator(found, end_);
  if (!found->relatives[Node::Left] && !found->relatives[Node::Right]) {
    DeleteWithNoChilds(found);
  } else if (!found->relatives[Node::Left]) {
    DeleteWithNoLeftChild(found);
  } else if (!found->relatives[Node::Right]) {
    DeleteWithNoRightChild(found);
  } else {
  }
  return next;
}

TEMPLATE_DEF
size_t BIN_TREE_DEF::Size() { return size_; }

// /*
//     private methods
// */

TEMPLATE_DEF
void BIN_TREE_DEF::SetNewNodeOnEnd(NodePtr& node, const Value& value) {
  node->value = value;
  node->relatives[Node::Right].reset(new Node());
  end_ = node->relatives[Node::Right];
  end_->relatives[Node::Parent].reset(node.get(), [this](Node*) {});
}

TEMPLATE_DEF
void BIN_TREE_DEF::SetNewNodeOnNull(NodePtrPair& nodes_pair,
                                    const Value& value) {
  bool relative_selector = Comparator()(KeyRetractor()(nodes_pair.first->value),
                                        KeyRetractor()(value));

  nodes_pair.first->relatives[relative_selector].reset(new Node());
  nodes_pair.second = nodes_pair.first->relatives[relative_selector];

  nodes_pair.second->value = value;
  nodes_pair.second->relatives[Node::Parent].reset(nodes_pair.first.get(),
                                                   [this](Node*) {});
}

TEMPLATE_DEF
BIN_TREE_DEF::NodePtrPair BIN_TREE_DEF::Seek(const Key& key) {
  NodePtr selector = root_, previous;
  for (; selector && selector != end_;) {
    previous = selector;
    const Key selected = KeyRetractor()(selector->value);
    if (IsEQ(key, selected)) {
      break;
    }
    selector = selector->relatives[Comparator()(selected, key)];
  }
  return {previous, selector};
}

TEMPLATE_DEF
void BIN_TREE_DEF::DeleteWithNoLeftChild(NodePtr& node) {
  node->value = node->relatives[Node::Right]->value;
  node->relatives[Node::Left] =
      node->relatives[Node::Right]->relatives[Node::Left];
  node->relatives[Node::Right] =
      node->relatives[Node::Right]->relatives[Node::Right];
}

TEMPLATE_DEF
void BIN_TREE_DEF::DeleteWithNoRightChild(NodePtr& node) {
  node->value = node->relatives[Node::Left]->value;
  node->relatives[Node::Right] =
      node->relatives[Node::Left]->relatives[Node::Right];
  node->relatives[Node::Left] =
      node->relatives[Node::Left]->relatives[Node::Left];
}

TEMPLATE_DEF
void BIN_TREE_DEF::DeleteWithNoChilds(NodePtr& node) {
  NodePtr parent = node->relatives[Node::Parent];

  if (parent->relatives[Node::Left] == node) {
    parent->relatives[Node::Left].reset();
  } else {
    parent->relatives[Node::Right].reset();
  }
}

// /*
//     private static methods
// */

TEMPLATE_DEF
bool BIN_TREE_DEF::IsEQ(const Key& key1, const Key& key2) {
  return !(Comparator()(key1, key2) || Comparator()(key2, key1));
}

TEMPLATE_DEF
BIN_TREE_DEF::NodePtr BIN_TREE_DEF::MakeStep(NodePtr node, size_t direction) {
  return node->relatives[direction];
}

TEMPLATE_DEF
void BIN_TREE_DEF::GoToEnd(NodePtr& selector, size_t direction) {
  for (; selector->relatives[direction];
       selector = selector->relatives[direction]) {
  }
}

}  // namespace hhullen
