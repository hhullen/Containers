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
    PullToNodeFromRelative(found, Node::Right);
  } else if (!found->relatives[Node::Right]) {
    PullToNodeFromRelative(found, Node::Left);
  } else {
    DeleteWithBothChilds(found);
  }
  --size_;
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
  NodePtr& node_prev = nodes_pair.first;
  NodePtr& node_curr = nodes_pair.second;
  bool relative_selector =
      Comparator()(KeyRetractor()(node_prev->value), KeyRetractor()(value));

  node_prev->relatives[relative_selector].reset(new Node());
  node_curr = node_prev->relatives[relative_selector];
  node_curr->value = value;
  node_curr->relatives[Node::Parent].reset(node_prev.get(), [this](Node*) {});
}

TEMPLATE_DEF
BIN_TREE_DEF::NodePtrPair BIN_TREE_DEF::Seek(const Key& key) {
  NodePtr selector = root_, previous;
  for (; selector && selector != end_;) {
    previous = selector;
    const Key selected_key = KeyRetractor()(selector->value);
    if (IsEQ(key, selected_key)) {
      break;
    }
    selector = selector->relatives[Comparator()(selected_key, key)];
  }
  return {previous, selector};
}

TEMPLATE_DEF
void BIN_TREE_DEF::PullToNodeFromRelative(NodePtr& node, size_t relative) {
  size_t second_relative = !relative;
  node->value = node->relatives[relative]->value;
  node->relatives[second_relative] =
      node->relatives[relative]->relatives[second_relative];
  node->relatives[relative] = node->relatives[relative]->relatives[relative];
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

TEMPLATE_DEF
void BIN_TREE_DEF::DeleteWithBothChilds(NodePtr& node) {
  NodePtr exchange_node = node->relatives[Node::Right];
  if (exchange_node->relatives[Node::Left]) {
    GoToEnd(exchange_node, Node::Left);
    if (exchange_node->relatives[Node::Right]) {
      node->value = exchange_node->value;
      PullToNodeFromRelative(exchange_node, Node::Right);
    } else {
      node->value = exchange_node->value;
      exchange_node->relatives[Node::Parent]->relatives[Node::Left].reset();
    }
  } else {
    node->value = exchange_node->value;
    if (exchange_node->relatives[Node::Right]) {
      exchange_node->relatives[Node::Right]->relatives[Node::Parent].reset(
          node.get(), [this](Node*) {});
    }
    node->relatives[Node::Right] = exchange_node->relatives[Node::Right];
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
BIN_TREE_DEF::NodePtr BIN_TREE_DEF::MakeStep(const NodePtr& node,
                                             size_t direction) {
  return node->relatives[direction];
}

TEMPLATE_DEF
void BIN_TREE_DEF::GoToEnd(NodePtr& selector, size_t direction) {
  for (; selector->relatives[direction];
       selector = selector->relatives[direction]) {
  }
}

}  // namespace hhullen
