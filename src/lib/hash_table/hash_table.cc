#include <cstddef>
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
bool HASH_TABLE_DEF::Contains(const Key &key) { return Find(key) != End(); }

HASH_TABLE_TEMPLATE_DEF
bool HASH_TABLE_DEF::Empty() { return vault_.empty(); }

HASH_TABLE_TEMPLATE_DEF
typename HASH_TABLE_DEF::Iterator HASH_TABLE_DEF::Find(const Key &key) {
  HashMatch hash_match = SeekHashMatchInTable(key);
  if (hash_match.second) {
    return table_[hash_match.first];
  }
  return vault_.end();
}

HASH_TABLE_TEMPLATE_DEF
typename HASH_TABLE_DEF::Iterator HASH_TABLE_DEF::Emplace(const Value &value) {
  UpscaleTable();
  Key key = KeyRetractor()(value);
  size_t hash = SeekHashToEmptyInTable(key);
  vault_.emplace_back(value);
  table_[hash] = --vault_.end();
  return table_[hash];
}

HASH_TABLE_TEMPLATE_DEF
typename HASH_TABLE_DEF::Iterator HASH_TABLE_DEF::Delete(const Key &key) {
  DownscaleTable();
  HashMatch hash_match = SeekHashMatchInTable(key);
  if (hash_match.second) {
    auto iter_to_next = vault_.erase(table_[hash_match.first]);
    table_[hash_match.first] = Iterator();
    return iter_to_next;
  }
  return End();
}

HASH_TABLE_TEMPLATE_DEF
size_t HASH_TABLE_DEF::Size() { return vault_.size(); }

/*
  Private methods
*/

HASH_TABLE_TEMPLATE_DEF
void HASH_TABLE_DEF::UpscaleTable() {
  size_t percent_filled = vault_.size() * 100 / table_.size();
  if (percent_filled < max_percent_filled_) {
    return;
  }
  size_t new_size = CalculateScaleFactor(table_.size());
  ResizeTable(new_size);
}

HASH_TABLE_TEMPLATE_DEF
void HASH_TABLE_DEF::DownscaleTable() {
  size_t percent_filled = vault_.size() * 100 / table_.size();
  if (percent_filled > min_percent_filled_ || Size() <= default_table_size_) {
    return;
  }
  size_t new_size = table_.size() * (max_percent_filled_ - 1) / 100;
  ResizeTable(new_size);
}

HASH_TABLE_TEMPLATE_DEF
void HASH_TABLE_DEF::ResizeTable(size_t new_size) {
  table_ = Table(new_size);
  for (auto iter = vault_.begin(); iter != vault_.end(); ++iter) {
    Key key = KeyRetractor()(*iter);
    size_t hash = SeekHashToEmptyInTable(key);
    table_[hash] = iter;
  }
}

HASH_TABLE_TEMPLATE_DEF
typename HASH_TABLE_DEF::HashMatch
HASH_TABLE_DEF::SeekHashMatchInTable(const Key &key) {
  HashPair hashes = CalculateHashPair(key);
  for (size_t i = 0; i < table_.size(); ++i) {
    if (table_[hashes.first]._M_node &&
        KeyRetractor()(*(table_[hashes.first])) == key) {
      return HashMatch(hashes.first, true);
    }
    hashes.first = (hashes.first + hashes.second) % table_.size();
  }
  return HashMatch(0, false);
}

HASH_TABLE_TEMPLATE_DEF
size_t HASH_TABLE_DEF::SeekHashToEmptyInTable(const Key &key) {
  HashPair hashes = CalculateHashPair(key);
  for (size_t i = 0; table_[hashes.first]._M_node && i < table_.size(); ++i) {
    if (KeyRetractor()(*(table_[hashes.first])) == key) {
      return hashes.first;
    }
    hashes.first = (hashes.first + hashes.second) % table_.size();
  }
  return hashes.first;
}

HASH_TABLE_TEMPLATE_DEF
typename HASH_TABLE_DEF::HashPair
HASH_TABLE_DEF::CalculateHashPair(const Key &key) {
  return HashPair(Hasher()(key) % table_.size(), (table_.size() - 1));
}

HASH_TABLE_TEMPLATE_DEF
size_t HASH_TABLE_DEF::CalculateScaleFactor(size_t size) {
  return static_cast<size_t>(
      std::pow(std::log(static_cast<double>(size)), table_scale_factor_));
}

} // namespace hhullen
