#include <gtest/gtest.h>

#include <stdexcept>

#include "SparseVector.h"

// Тест 1: Конструктор и базовые методы
TEST(SparseVectorTest, ConstructorAndBasicMethods) {
  SparseVector v(100);

  EXPECT_EQ(v.getSize(), 100);  // Проверяем размер

  // Все элементы должны быть 0 изначально
  for (int i = 0; i < 100; i++) {
    EXPECT_EQ(v.getElem(i), 0);
  }
}

// Тест 2: Установка и получение элементов
TEST(SparseVectorTest, SetAndGetElements) {
  SparseVector v(10);

  v.setElem(2, 5);
  v.setElem(5, 8);
  v.setElem(7, 3);

  EXPECT_EQ(v.getElem(2), 5);
  EXPECT_EQ(v.getElem(5), 8);
  EXPECT_EQ(v.getElem(7), 3);
  EXPECT_EQ(v.getElem(1), 0);  // Неустановленный элемент = 0
}

// Тест 3: Проверка границ
TEST(SparseVectorTest, BoundaryChecks) {
  SparseVector v(10);

  // Должны бросаться исключения при неверных индексах
  EXPECT_THROW(v.getElem(-1), std::out_of_range);
  EXPECT_THROW(v.getElem(10), std::out_of_range);
  EXPECT_THROW(v.setElem(-1, 5), std::out_of_range);
  EXPECT_THROW(v.setElem(10, 5), std::out_of_range);
}

// Тест 4: Конструктор копирования
TEST(SparseVectorTest, CopyConstructor) {
  SparseVector v1(10);
  v1.setElem(2, 5);
  v1.setElem(5, 8);

  SparseVector v2(v1);  // Конструктор копирования

  EXPECT_EQ(v2.getSize(), 10);
  EXPECT_EQ(v2.getElem(2), 5);
  EXPECT_EQ(v2.getElem(5), 8);

  // Изменение копии не должно влиять на оригинал
  v2.setElem(2, 10);
  EXPECT_EQ(v1.getElem(2), 5);   // Оригинал не изменился
  EXPECT_EQ(v2.getElem(2), 10);  // Копия изменилась
}

// Тест 5: Оператор присваивания
TEST(SparseVectorTest, AssignmentOperator) {
  SparseVector v1(10), v2(10);
  v1.setElem(2, 5);
  v1.setElem(5, 8);

  v2 = v1;  // Оператор присваивания

  EXPECT_EQ(v2.getElem(2), 5);
  EXPECT_EQ(v2.getElem(5), 8);
}

// Тест 6: Операторы += и -=
TEST(SparseVectorTest, CompoundOperators) {
  SparseVector v1(10), v2(10);

  v1.setElem(2, 5);
  v1.setElem(5, 3);

  v2.setElem(1, 4);
  v2.setElem(5, 2);

  v1 += v2;

  EXPECT_EQ(v1.getElem(1), 4);  // 0 + 4 = 4
  EXPECT_EQ(v1.getElem(2), 5);  // 5 + 0 = 5
  EXPECT_EQ(v1.getElem(5), 5);  // 3 + 2 = 5

  v1 -= v2;
  EXPECT_EQ(v1.getElem(1), 0);  // 4 - 4 = 0
  EXPECT_EQ(v1.getElem(2), 5);  // 5 - 0 = 5
  EXPECT_EQ(v1.getElem(5), 3);  // 5 - 2 = 3
}

// Тест 7: Операторы + и -
TEST(SparseVectorTest, BinaryOperators) {
  SparseVector v1(10), v2(10);

  v1.setElem(2, 5);
  v2.setElem(2, 3);

  SparseVector v3 = v1 + v2;
  SparseVector v4 = v1 - v2;

  EXPECT_EQ(v3.getElem(2), 8);  // 5 + 3 = 8
  EXPECT_EQ(v4.getElem(2), 2);  // 5 - 3 = 2

  // Оригиналы не должны измениться
  EXPECT_EQ(v1.getElem(2), 5);
  EXPECT_EQ(v2.getElem(2), 3);
}

// Тест 8: Операторы сравнения
TEST(SparseVectorTest, ComparisonOperators) {
  SparseVector v1(10), v2(10), v3(10);

  v1.setElem(2, 5);
  v2.setElem(2, 5);
  v3.setElem(2, 3);

  EXPECT_TRUE(v1 == v2);   // Равные вектора
  EXPECT_FALSE(v1 == v3);  // Разные значения
  EXPECT_TRUE(v1 != v3);   // Неравные вектора
}

// Тест 9: Удаление элементов (установка в 0)
TEST(SparseVectorTest, RemoveElements) {
  SparseVector v(10);

  v.setElem(2, 5);
  v.setElem(5, 8);

  EXPECT_EQ(v.getElem(2), 5);

  v.setElem(2, 0);  // Удаляем элемент

  EXPECT_EQ(v.getElem(2), 0);  // Должен стать 0
  EXPECT_EQ(v.getElem(5), 8);  // Другой элемент не изменился
}

// Тест 10: Разные размеры векторов
TEST(SparseVectorTest, DifferentSizes) {
  SparseVector v1(10), v2(5);

  // Операции между векторами разного размера должны бросать исключения
  EXPECT_THROW(v1 + v2, std::invalid_argument);
  EXPECT_THROW(v1 - v2, std::invalid_argument);
  EXPECT_THROW(v1 += v2, std::invalid_argument);
  EXPECT_THROW(v1 -= v2, std::invalid_argument);
  EXPECT_THROW(v1 = v2, std::invalid_argument);
}

// Тест 11: Краевые случаи с нулевыми операциями
TEST(SparseVectorTest, EdgeCases) {
  SparseVector v1(10), v2(10), empty(10);

  // Сложение с пустым вектором
  v1.setElem(2, 5);
  v1 += empty;  // Ничего не должно измениться
  EXPECT_EQ(v1.getElem(2), 5);

  // Вычитание самого себя
  v2.setElem(3, 8);
  v2 -= v2;  // Должен стать пустым
  for (int i = 0; i < 10; i++) {
    EXPECT_EQ(v2.getElem(i), 0);
  }
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}