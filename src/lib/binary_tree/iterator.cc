// #include "definition.h"

// namespace hhullen {

// template <comparable Key, class Value>
// BinTree<Key, Value>::Iterator::Iterator() {}

// template <comparable Key, class Value>
// BinTree<Key, Value>::Iterator::Iterator(Node* node) : node_ptr_{node} {}

// template <comparable Key, class Value>
// std::pair<Key, Value> BinTree<Key, Value>::Iterator::operator*() const {
//   return {node_ptr_., (*attended_.back()).value};
// }

// template <comparable Key, class Value>
// BinTree<Key, Value>::Iterator& BinTree<Key, Value>::Iterator::operator++() {
//   // Node* child_r = attended_.back()->childs[Childs::Right].get();
//   // if (child_r) {
//   //   attended_.emplace_back(child_r);
//   //   Node* child_l = child_r->childs[Childs::Left].get();
//   //   for (; child_l; child_l = child_l->childs[Childs::Left].get()) {
//   //     attended_.emplace_back(child_l);
//   //   }
//   // } else {
//   //   attended_.pop_back();
//   // }
//   // return *this;
// }

// template <comparable Key, class Value>
// BinTree<Key, Value>::Iterator& BinTree<Key, Value>::Iterator::operator--() {}

// template <comparable Key, class Value>
// BinTree<Key, Value>::Iterator BinTree<Key, Value>::Iterator::operator++(int)
// {}

// template <comparable Key, class Value>
// BinTree<Key, Value>::Iterator BinTree<Key, Value>::Iterator::operator--(int)
// {}

// template <comparable Key, class Value>
// bool BinTree<Key, Value>::Iterator::operator==(
//     const BinTree<Key, Value>::Iterator& other) const {
//   // return attended_.back() == other.attended_.back();
// }

// template <comparable Key, class Value>
// bool BinTree<Key, Value>::Iterator::operator!=(
//     const BinTree<Key, Value>::Iterator& other) const {
//   // return attended_.back() != other.attended_.back();
// }

// }  // namespace hhullen
