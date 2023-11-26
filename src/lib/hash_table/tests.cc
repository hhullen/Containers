#include "hash_table.h"
#include <gtest/gtest.h>

TEST(HashTable_test, Constructor) {
  hhullen::HashTable<double> ht1;
  hhullen::HashTable<double> ht2{1.2, 4.4, 5.5, 7.7};
}

TEST(HashTable_test, Empty_methos) {
  hhullen::HashTable<double> ht1;
  hhullen::HashTable<double> ht2{1.2, 4.4, 5.5, 7.7};
  EXPECT_TRUE(ht1.Empty());
  EXPECT_FALSE(ht2.Empty());
}

TEST(HashTable_test, Size_method) {
  hhullen::HashTable<double> ht1;
  hhullen::HashTable<double> ht2{1.2, 4.4, 5.5, 7.7};
  EXPECT_EQ(ht1.Size(), 0);
  EXPECT_EQ(ht2.Size(), 4);
}

TEST(HashTable_test, Clear_method) {
  hhullen::HashTable<double> ht{1.2, 4.4, 5.5, 7.7};
  EXPECT_EQ(ht.Size(), 4);
  ht.Clear();
  EXPECT_EQ(ht.Size(), 0);
}

TEST(HashTable_test, Emplace_method_no_upscale) {
  hhullen::HashTable<double> ht;
  EXPECT_EQ(ht.Size(), 0);
  ht.Emplace(1.0);
  EXPECT_EQ(ht.Size(), 1);
  ht.Emplace(2.0);
  EXPECT_EQ(ht.Size(), 2);
  ht.Emplace(3.0);
  EXPECT_EQ(ht.Size(), 3);
  auto it = ht.Begin();
  for (double n = 1; it != ht.End(); ++it, n += 1) {
    EXPECT_DOUBLE_EQ(*it, n);
  }
}

TEST(HashTable_test, Emplace_method_with_upscale) {
  hhullen::HashTable<double> ht;
  for (double n = 0; n < 100000; n += 1) {
    EXPECT_EQ(ht.Size(), n);
    ht.Emplace(n);
  }
  auto it = ht.Begin();
  for (double n = 0; it != ht.End(); ++it, n += 1) {
    EXPECT_DOUBLE_EQ(*it, n);
  }
  ht.Clear();
  for (double n = 100000; n >= 0; n -= 1) {
    ht.Emplace(n);
  }
  it = ht.Begin();
  for (double n = 100000; it != ht.End(); ++it, n -= 1) {
    EXPECT_DOUBLE_EQ(*it, n);
  }
}

TEST(HashTable_test, Find_method) {
  hhullen::HashTable<double> ht;
  for (double n = 0; n < 100000; n += 1) {
    ht.Emplace(n);
  }
  for (double n = 0; n < 100000; n += 1) {
    auto it = ht.Find(n);
    EXPECT_TRUE(it != ht.End());
    EXPECT_EQ(*it, n);
  }
}

TEST(HashTable_test, Contains_method) {
  hhullen::HashTable<double> ht;
  for (double n = 0; n < 100000; n += 1) {
    ht.Emplace(n);
  }
  for (double n = 0; n < 100000; n += 1) {
    EXPECT_TRUE(ht.Contains(n));
  }
}

TEST(HashTable_test, Delete_method_no_downscale) {
  hhullen::HashTable<double> ht{1.0, 2.0, 3.0};
  auto it = ht.Delete(2.0);
  EXPECT_EQ(ht.Size(), 2);
  it = ht.Find(2.0);
  EXPECT_TRUE(it == ht.End());

  it = ht.Delete(3.0);
  EXPECT_EQ(ht.Size(), 1);
  it = ht.Find(3.0);
  EXPECT_TRUE(it == ht.End());

  it = ht.Delete(1.0);
  EXPECT_EQ(ht.Size(), 0);
  it = ht.Find(1.0);
  EXPECT_TRUE(it == ht.End());
}

TEST(HashTable_test, Delete_method_with_downscale) {
  hhullen::HashTable<double> ht;
  for (double n = 0; n < 100000; n += 1) {
    ht.Emplace(n);
  }
  for (double n = 100000; n >= 0; --n) {
    auto it = ht.Delete(n);
    EXPECT_EQ(ht.Size(), n);
    EXPECT_TRUE(it == ht.End());
  }
}
