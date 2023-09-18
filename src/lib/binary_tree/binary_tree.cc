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
    GetSelfFromNodeParent(found).reset();
  } else if (found->relatives[Node::Right] == end_ &&
             !found->relatives[Node::Left]) {
    ReplaceNode(found, end_);
  } else if (!found->relatives[Node::Left]) {
    ReplaceNode(found, found->relatives[Node::Right]);
  } else if (!found->relatives[Node::Right] ||
             found->relatives[Node::Right] == end_) {
    ReplaceNode(found, found->relatives[Node::Left]);
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
void BIN_TREE_DEF::ReplaceNode(NodePtr& to_replace, NodePtr& src) {
  ReplaceNodeRelative(to_replace, src, Node::Left);
  ReplaceNodeRelative(to_replace, src, Node::Right);
  src->relatives[Node::Parent] = to_replace->relatives[Node::Parent];

  NodePtr& src_parent = src->relatives[Node::Parent];
  if (src_parent) {
    if (src_parent->relatives[Node::Left] == to_replace) {
      src_parent->relatives[Node::Left] = src;
    } else if (src_parent->relatives[Node::Right] == to_replace) {
      src_parent->relatives[Node::Right] = src;
    }
  }

  if (!src->relatives[Node::Parent]) {
    root_ = src;
  }
}

TEMPLATE_DEF
void BIN_TREE_DEF::ReplaceNodeRelative(NodePtr& to_replace, NodePtr& replacer,
                                       size_t relative) {
  if (to_replace->relatives[relative] != replacer) {
    replacer->relatives[relative] = to_replace->relatives[relative];
    if (replacer->relatives[relative]) {
      replacer->relatives[relative]->relatives[Node::Parent].reset(
          replacer.get(), [this](Node*) {});
    }
  }
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
      GetSelfFromNodeParent(exchange_node) =
          exchange_node->relatives[Node::Right];
      ReplaceNode(node, exchange_node);
    } else {
      GetSelfFromNodeParent(exchange_node).reset();
      ReplaceNode(node, exchange_node);
    }
  } else {
    ReplaceNode(node, exchange_node);
  }
  if (!exchange_node->relatives[Node::Parent]) {
    root_ = exchange_node;
  }
}

TEMPLATE_DEF
size_t BIN_TREE_DEF::CalculateHeight(const NodePtr& start_node) {
  size_t height = 0;
  std::vector<NodePtr> traversal_targets[2];
  bool selector = 0;
  if (start_node == end_) {
    return 0;
  }
  traversal_targets[selector].emplace_back(start_node);
  for (; !traversal_targets[selector].empty(); ++height) {
    for (size_t i = 0; i < traversal_targets[selector].size(); ++i) {
      NodePtr& node = traversal_targets[selector][i];
      if (node == end_) {
        continue;
      }
      if (node->relatives[Node::Left] && node->relatives[Node::Left] != end_) {
        traversal_targets[!selector].emplace_back(node->relatives[Node::Left]);
      }
      if (node->relatives[Node::Right] &&
          node->relatives[Node::Right] != end_) {
        traversal_targets[!selector].emplace_back(node->relatives[Node::Right]);
      }
    }
    traversal_targets[selector].clear();
    selector = !selector;
  }
  return height;
}

TEMPLATE_DEF
void BIN_TREE_DEF::OutputTreeStruct(std::ostream& os) {
  NodePtr& start_node = root_;
  std::vector<NodePtr> traversal_targets[2];
  bool selector = 0;
  if (start_node == end_) {
    return;
  }
  traversal_targets[selector].emplace_back(start_node);
  for (; !traversal_targets[selector].empty();) {
    for (size_t i = 0; i < traversal_targets[selector].size(); ++i) {
      NodePtr& node = traversal_targets[selector][i];
      if (node == end_) {
        continue;
      }
      os << "[ NODE: " << node->value << " ";
      if (node->relatives[Node::Parent]) {
        os << " PARENT: " << node->relatives[Node::Parent]->value << " ";
      }
      if (node->relatives[Node::Left] && node->relatives[Node::Left] != end_) {
        os << " L:" << node->relatives[Node::Left]->value << " ";

        traversal_targets[!selector].emplace_back(node->relatives[Node::Left]);
      }
      if (node->relatives[Node::Right] &&
          node->relatives[Node::Right] != end_) {
        os << " R:" << node->relatives[Node::Right]->value << " ";

        traversal_targets[!selector].emplace_back(node->relatives[Node::Right]);
      }
      os << "] ";
    }
    os << "\n";
    traversal_targets[selector].clear();
    selector = !selector;
  }
}

TEMPLATE_DEF
BIN_TREE_DEF::NodePtr& BIN_TREE_DEF::GetSelfFromNodeParent(NodePtr& node) {
  if (node->relatives[Node::Parent]->relatives[Node::Left] == node) {
    return node->relatives[Node::Parent]->relatives[Node::Left];
  } else {
    return node->relatives[Node::Parent]->relatives[Node::Right];
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
BIN_TREE_DEF::NodePtr& BIN_TREE_DEF::GetRelative(const NodePtr& node,
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
