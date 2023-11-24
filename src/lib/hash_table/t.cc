// #include "hash_table.h"
#include <bitset>
#include <functional>
#include <iostream>
#include <list>
#include <string>
#include <vector>

#include "hash_table.h"

int main() {

  std::vector<int> vec(5);
  // size_t h1 = std::hash<int>()(3) % vec.size();
  // size_t h2 = (std::hash<int>()(3) + 1) % vec.size();
  size_t h2 = std::hash<int>()(13) % vec.size();
  size_t h1 = std::hash<int>()(13) % vec.size();
  std::cout << h1 << " " << h2 << "\n";
  for (int i = 0; i < 5; ++i) {
    std::cout << h1 << " ";
    h1 = (h1 + h2) % vec.size();
  }
  std::cout << "\n";

  hhullen::HashTable<int> ht;
  ht.Emplace(1);
  hhullen::HashTable<int>::Iterator iter = ht.Find(1);
  if (iter == ht.End()) {
    std::cout << "NONE\n";
  }
  return 0;
}
