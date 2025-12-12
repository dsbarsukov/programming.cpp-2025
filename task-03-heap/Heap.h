#ifndef HEAP_H
#define HEAP_H

#include <cstddef>    // для size_t
#include <iostream>   // для cout
#include <stdexcept>  // для overflow_error, underflow_error

using namespace std;

template <typename T, size_t MaxSize>
class Heap {
 private:
  T data[MaxSize];
  size_t currentSize = 0;

  // Возвращает индекс родительского узла для узла с заданным индексом
  size_t parent(size_t index) const { return (index - 1) / 2; }

  // Возвращает индекс левого дочернего узла для узла с заданным индексом
  size_t leftChild(size_t index) const { return 2 * index + 1; }

  // Возвращает индекс правого дочернего узла для узла с заданным индексом
  size_t rightChild(size_t index) const { return 2 * index + 2; }

  // Обмен значениями двух элементов кучи по их индексам
  void swap(size_t index1, size_t index2) {
    T temp = data[index1];
    data[index1] = data[index2];
    data[index2] = temp;
  }

  // Восстановление свойства Min-Heap снизу вверх (после добавления элемента)
  void heapifyUp(size_t index) {
    while (index > 0 && data[index] < data[parent(index)]) {
      swap(index, parent(index));
      index = parent(index);
    }
  }

  // Восстановление свойства Min-Heap сверху вниз (после удаления корня)
  void heapifyDown(size_t index) {
    size_t smallest = index;
    size_t left = leftChild(index);
    size_t right = rightChild(index);

    if (left < currentSize && data[left] < data[smallest]) {
      smallest = left;
    }

    if (right < currentSize && data[right] < data[smallest]) {
      smallest = right;
    }

    if (smallest != index) {
      swap(index, smallest);
      heapifyDown(smallest);
    }
  }

 public:
  // Добавление элемента в кучу
  void add(const T& value) {
    if (isFull()) {
      throw overflow_error("Куча заполнена");
    }

    data[currentSize] = value;
    currentSize++;
    heapifyUp(currentSize - 1);
  }

  // Извлечение минимального элемента из кучи
  T getFirst() {
    if (isEmpty()) {
      throw underflow_error("Куча пустая");
    }

    T result = data[0];
    data[0] = data[currentSize - 1];
    currentSize--;

    if (currentSize > 0) {
      heapifyDown(0);
    }

    return result;
  }

  // Просмотр минимального элемента без его извлечения
  const T& peekFirst() const {
    if (isEmpty()) {
      throw underflow_error("Куча пустая");
    }

    return data[0];
  }

  // Текущий размер кучи
  size_t size() const { return currentSize; }

  // Проверка на пустоту
  bool isEmpty() const { return currentSize == 0; }

  // Проверка на полноту
  bool isFull() const { return currentSize == MaxSize; }

  // Простой вывод содержимого
  void print() const {
    cout << "Heap [" << currentSize << "/" << MaxSize << "]: ";

    if (isEmpty()) {
      cout << "empty";
    } else {
      cout << "[";
      for (size_t i = 0; i < currentSize; i++) {
        cout << data[i];
        if (i < currentSize - 1) {
          cout << ", ";
        }
      }
      cout << "]" << endl;
    }
  }
};

#endif