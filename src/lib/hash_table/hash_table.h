#ifndef HASH_TABLE_HASH_TABLE_H_
#define HASH_TABLE_HASH_TABLE_H_

#include <cmath>
#include <functional>
#include <iostream>
#include <list>
#include <vector>

namespace hhullen {

#define HASH_TABLE_DEF HashTable<Value, Key, KeyRetractor, Hasher>
#define HASH_TABLE_TEMPLATE_DEF                                                \
  template <class Value, class Key, class KeyRetractor, class Hasher>

template <class T> class HashTableKeyRetractor {
public:
  const T &operator()(const T &value) const { return value; }
};

template <class Value, class Key = Value,
          class KeyRetractor = HashTableKeyRetractor<Value>,
          class Hasher = std::hash<Value>>
class HashTable {

  static constexpr size_t default_table_size_{5};
  static constexpr size_t max_percent_filled_{70};
  static constexpr size_t min_percent_filled_{30};
  static constexpr double table_scale_factor_{5};

public:
  using Iterator = typename std::list<Value>::iterator;
  using Table = std::vector<Iterator>;
  using Vault = std::list<Value>;
  using HashPair = std::pair<size_t, size_t>;
  using HashMatch = std::pair<size_t, bool>;
  HashTable();
  HashTable(const std::initializer_list<Value> &items);
  ~HashTable();

  Iterator Begin();
  Iterator End();
  void Clear();
  bool Contains(const Key &key);
  bool Empty();
  Iterator Find(const Key &key);
  Iterator Emplace(const Value &value);
  Iterator Delete(const Key &key);
  size_t Size();

private:
  Table table_;
  Vault vault_;

  void UpscaleTable();
  void DownscaleTable();
  void ResizeTable(size_t new_size);
  HashMatch SeekHashMatchInTable(const Key &key);
  size_t SeekHashToEmptyInTable(const Key &key);
  HashPair CalculateHashPair(const Key &key);
  size_t CalculateScaleFactor(size_t size);
};

} // namespace hhullen

#include "hash_table.cc"

#endif // HASH_TABLE_HASH_TABLE_H_
