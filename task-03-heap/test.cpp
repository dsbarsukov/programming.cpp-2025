#include <gtest/gtest.h>

#include <algorithm>
#include <string>

#include "Heap.h"

using namespace std;

// ============================
// Тесты для целых чисел
// ============================

TEST(HeapIntTest, DefaultIsEmpty) {
  Heap<int, 5> h;
  EXPECT_TRUE(h.isEmpty());
  EXPECT_FALSE(h.isFull());
  EXPECT_EQ(h.size(), 0);
}

TEST(HeapIntTest, AddAndPeek) {
  Heap<int, 5> h;
  h.add(10);
  EXPECT_FALSE(h.isEmpty());
  EXPECT_EQ(h.peekFirst(), 10);
  EXPECT_EQ(h.size(), 1);
}

TEST(HeapIntTest, AddMultiplePreservesOrder) {
  Heap<int, 10> h;
  h.add(5);
  h.add(3);
  h.add(7);
  h.add(1);

  EXPECT_EQ(h.peekFirst(), 1);
  h.getFirst();  // удаляем 1

  EXPECT_EQ(h.peekFirst(), 3);
  h.getFirst();  // удаляем 3

  EXPECT_EQ(h.peekFirst(), 5);
  h.getFirst();  // удаляем 5

  EXPECT_EQ(h.peekFirst(), 7);
  EXPECT_EQ(h.size(), 1);
}

TEST(HeapIntTest, HeapPropertyMaintainedWithArrays) {
  Heap<int, 10> h;

  int values[] = {9, 5, 2, 7, 1, 8, 3};
  size_t valuesCount = 7;

  for (size_t i = 0; i < valuesCount; i++) {
    h.add(values[i]);
  }

  int extracted[7];
  size_t cnt = 0;

  while (!h.isEmpty()) {
    extracted[cnt] = h.getFirst();
    cnt++;
  }

  EXPECT_EQ(extracted[0], 1);
  EXPECT_EQ(extracted[1], 2);
  EXPECT_EQ(extracted[2], 3);
  EXPECT_EQ(extracted[3], 5);
  EXPECT_EQ(extracted[4], 7);
  EXPECT_EQ(extracted[5], 8);
  EXPECT_EQ(extracted[6], 9);

  EXPECT_EQ(cnt, valuesCount);
}

TEST(HeapIntTest, OverflowException) {
  Heap<int, 3> h;
  h.add(1);
  h.add(2);
  h.add(3);

  EXPECT_TRUE(h.isFull());
  EXPECT_THROW(h.add(4), overflow_error);
}

TEST(HeapIntTest, UnderflowException) {
  Heap<int, 5> h;
  EXPECT_THROW(h.peekFirst(), underflow_error);
  EXPECT_THROW(h.getFirst(), underflow_error);
}

// ============================
// Тесты для чисел с плавающей точкой
// ============================

TEST(HeapDoubleTest, FloatHandling) {
  Heap<double, 5> h;
  h.add(3.14);
  h.add(1.41);
  h.add(2.71);

  EXPECT_DOUBLE_EQ(h.peekFirst(), 1.41);
  h.getFirst();
  EXPECT_DOUBLE_EQ(h.peekFirst(), 2.71);
  h.getFirst();
  EXPECT_DOUBLE_EQ(h.peekFirst(), 3.14);
}

// ============================
// Тесты для строк
// ============================

TEST(HeapStringTest, LexicographicOrder) {
  Heap<string, 10> h;

  h.add("banana");
  h.add("apple");
  h.add("cherry");
  h.add("date");

  EXPECT_EQ(h.peekFirst(), "apple");
  h.getFirst();

  EXPECT_EQ(h.peekFirst(), "banana");
  h.getFirst();

  EXPECT_EQ(h.peekFirst(), "cherry");
  h.getFirst();

  EXPECT_EQ(h.peekFirst(), "date");
}

TEST(HeapStringTest, StringHeapProperty) {
  Heap<string, 10> h;

  string values[] = {"zebra", "lion", "elephant", "cat", "dog", "bear", "ant", "giraffe", "horse", "monkey"};
  size_t valuesCount = 10;

  for (size_t i = 0; i < valuesCount; i++) {
    h.add(values[i]);
  }
  string extracted[10];
  size_t cnt = 0;

  while (!h.isEmpty()) {
    extracted[cnt] = h.getFirst();
    cnt++;
  }
  EXPECT_EQ(extracted[0], "ant");       // a...
  EXPECT_EQ(extracted[1], "bear");      // b...
  EXPECT_EQ(extracted[2], "cat");       // c...
  EXPECT_EQ(extracted[3], "dog");       // d...
  EXPECT_EQ(extracted[4], "elephant");  // e...
  EXPECT_EQ(extracted[5], "giraffe");   // g...
  EXPECT_EQ(extracted[6], "horse");     // h...
  EXPECT_EQ(extracted[7], "lion");      // l...
  EXPECT_EQ(extracted[8], "monkey");    // m...
  EXPECT_EQ(extracted[9], "zebra");     // z...

  EXPECT_EQ(cnt, valuesCount);
}

// ============================
// Тесты краевых случаев
// ============================

TEST(HeapEdgeCasesTest, SingleElement) {
  Heap<int, 5> h;
  h.add(42);
  EXPECT_EQ(h.peekFirst(), 42);
  EXPECT_EQ(h.getFirst(), 42);
  EXPECT_TRUE(h.isEmpty());
}

TEST(HeapEdgeCasesTest, DuplicateValues) {
  Heap<int, 10> h;
  h.add(5);
  h.add(5);
  h.add(3);
  h.add(3);
  h.add(7);

  EXPECT_EQ(h.getFirst(), 3);
  EXPECT_EQ(h.getFirst(), 3);
  EXPECT_EQ(h.getFirst(), 5);
  EXPECT_EQ(h.getFirst(), 5);
  EXPECT_EQ(h.getFirst(), 7);
}

TEST(HeapEdgeCasesTest, ReverseOrderInsertion) {
  Heap<int, 10> h;
  for (int i = 9; i >= 0; i--) {
    h.add(i);
  }

  for (int i = 0; i < 10; i++) {
    EXPECT_EQ(h.getFirst(), i);
  }
}

TEST(HeapEdgeCasesTest, AlreadySortedInsertion) {
  Heap<int, 10> h;
  for (int i = 0; i < 10; i++) {
    h.add(i);
  }

  for (int i = 0; i < 10; i++) {
    EXPECT_EQ(h.getFirst(), i);
  }
}

// ============================
// Комплексный тест
// ============================

TEST(HeapComplexTest, MixedOperations) {
  Heap<int, 10> h;

  // Добавляем элементы
  h.add(50);
  h.add(30);
  h.add(20);
  h.add(40);

  EXPECT_EQ(h.peekFirst(), 20);
  EXPECT_EQ(h.size(), 4);

  // Извлекаем минимальный
  EXPECT_EQ(h.getFirst(), 20);
  EXPECT_EQ(h.peekFirst(), 30);

  // Добавляем ещё
  h.add(10);
  h.add(60);

  EXPECT_EQ(h.peekFirst(), 10);
  EXPECT_EQ(h.size(), 5);

  // Извлекаем всё
  EXPECT_EQ(h.getFirst(), 10);
  EXPECT_EQ(h.getFirst(), 30);
  EXPECT_EQ(h.getFirst(), 40);
  EXPECT_EQ(h.getFirst(), 50);
  EXPECT_EQ(h.getFirst(), 60);

  EXPECT_TRUE(h.isEmpty());
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}