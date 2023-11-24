#ifndef HASH_TABLE_HASH_TABLE_H_
#include "hash_table.h"
#endif // HASH_TABLE_HASH_TABLE_H_

namespace hhullen {

HASH_TABLE_TEMPLATE_DEF
HASH_TABLE_DEF::HashTable() : table_{default_table_size_} {}

HASH_TABLE_TEMPLATE_DEF
HASH_TABLE_DEF::HashTable(const std::initializer_list<Value> &items)
    : table_{default_table_size_} {
  for (auto iter = items.begin(); iter != items.end(); ++iter) {
    Emplace(*iter);
  }
}

HASH_TABLE_TEMPLATE_DEF
HASH_TABLE_DEF::~HashTable() {}

HASH_TABLE_TEMPLATE_DEF
typename HASH_TABLE_DEF::Iterator HASH_TABLE_DEF::Begin() {
  return vault_.begin();
}

HASH_TABLE_TEMPLATE_DEF
typename HASH_TABLE_DEF::Iterator HASH_TABLE_DEF::End() { return vault_.end(); }

HASH_TABLE_TEMPLATE_DEF
void HASH_TABLE_DEF::Clear() {
  table_.resize(default_table_size_);
  table_.shrink_to_fit();
  vault_.clear();
}

HASH_TABLE_TEMPLATE_DEF
bool HASH_TABLE_DEF::Contains(const Key &key) { return true; }

HASH_TABLE_TEMPLATE_DEF
bool HASH_TABLE_DEF::Empty() { return vault_.empty(); }

HASH_TABLE_TEMPLATE_DEF
typename HASH_TABLE_DEF::Iterator HASH_TABLE_DEF::Find(const Key &key) {
  size_t hash = Hasher()(key) % table_.size();
  size_t hash_step = hash;
  for (size_t i = 0; i < table_.size(); ++i) {
    if (table_[hash]._M_node && KeyRetractor()(*(table_[hash])) == key) {
      return table_[hash];
    }
    hash = (hash + hash_step) % table_.size();
  }
  return vault_.end();
}

HASH_TABLE_TEMPLATE_DEF
typename HASH_TABLE_DEF::Iterator HASH_TABLE_DEF::Emplace(const Value &value) {
  UpscaleTable();
  Key key = KeyRetractor()(value);
  size_t hash = SeekHashToEmptyInTable(key);
  table_[hash] = vault_.end();
  vault_.emplace_back(value);
  return table_[hash];
}

HASH_TABLE_TEMPLATE_DEF
typename HASH_TABLE_DEF::Iterator HASH_TABLE_DEF::Delete(const Key &key) {}

HASH_TABLE_TEMPLATE_DEF
size_t HASH_TABLE_DEF::Size() { return vault_.size(); }

/*
  Private methods
*/

HASH_TABLE_TEMPLATE_DEF
size_t HASH_TABLE_DEF::SeekHashToEmptyInTable(const Key &key) {
  size_t hash = Hasher()(key) % table_.size();
  size_t hash_step = (Hasher()(key) + 1) % (table_.size() - 1);
  for (size_t i = 0; table_[hash]._M_node && i < table_.size(); ++i) {
    if (KeyRetractor()(*(table_[hash])) == key) {
      return hash;
    }
    hash = (hash + hash_step * i) % table_.size();
  }
  return hash;
}

HASH_TABLE_TEMPLATE_DEF
void HASH_TABLE_DEF::UpscaleTable() {
  size_t test = vault_.size() * 100 / table_.size();
  if (test < max_percent_filled_) {
    return;
  }
  size_t new_size = CalculateScaleFactor(table_.size());
  table_ = Table(new_size);
  for (auto iter = vault_.begin(); iter != vault_.end(); ++iter) {
    Key key = KeyRetractor()(*iter);
    size_t hash = SeekHashToEmptyInTable(key);
    table_[hash] = iter;
  }
}

HASH_TABLE_TEMPLATE_DEF
size_t HASH_TABLE_DEF::CalculateScaleFactor(size_t size) {
  return static_cast<size_t>(
      std::pow(std::log(static_cast<double>(size)), table_scale_factor_));
}

} // namespace hhullen
