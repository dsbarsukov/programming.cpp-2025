#include "SparseVector.h"

#include <iostream>
#include <stdexcept>

using namespace std;

// Конструктор узла
SparseVector::node::node(int index, int value, node* next) : index(index), value(value), next(next) {}

// Основной конструктор
SparseVector::SparseVector(int size) : size_(size), head_(nullptr) {
  if (size <= 0) {
    throw invalid_argument("Размер вектора должен быть положительным");
  }
}

// Конструктор копирования
SparseVector::SparseVector(const SparseVector& other) : size_(other.size_), head_(nullptr) {
  copyList(other);
  checkListOrder();
}

// Деструктор
SparseVector::~SparseVector() { clear(); }

// Очистка всего списка
void SparseVector::clear() {
  node* current = head_;
  while (current != nullptr) {
    node* next = current->next;
    delete current;
    current = next;
  }
  head_ = nullptr;
}

// Копирование списка
void SparseVector::copyList(const SparseVector& other) {
  node* otherCurrent = other.head_;
  node* tail = nullptr;

  while (otherCurrent != nullptr) {
    node* newNode = new node(otherCurrent->index, otherCurrent->value);

    if (tail == nullptr) {
      head_ = newNode;
    } else {
      tail->next = newNode;
    }
    tail = newNode;
    otherCurrent = otherCurrent->next;
  }
}

// Вставка узла
void SparseVector::insertNode(int index, int value) {
  // head_ = new node(index, value, head_); // Оставил старую версию, чтобы
  // посмотреть на checkListOrder()
  node* current = head_;
  node* prev = nullptr;

  while (current != nullptr && current->index < index) {
    prev = current;
    current = current->next;
  }

  if (current != nullptr && current->index == index) {
    current->value = value;
    return;
  }

  node* newNode = new node(index, value);

  if (prev == nullptr) {
    newNode->next = head_;
    head_ = newNode;
  } else {
    newNode->next = current;
    prev->next = newNode;
  }
  checkListOrder();
}

// Удаление узла
void SparseVector::removeNode(int index) {
  if (head_ == nullptr) return;

  if (head_->index == index) {
    node* temp = head_;
    head_ = head_->next;
    delete temp;
    return;
  }

  node* current = head_;
  while (current->next != nullptr && current->next->index != index) {
    current = current->next;
  }

  if (current->next != nullptr && current->next->index == index) {
    node* temp = current->next;
    current->next = current->next->next;
    delete temp;
  }
  checkListOrder();
}

// Сложение (add=true) или вычитание (add=false) векторов
void SparseVector::addSubVector(const SparseVector& other, bool add) {
  int sign = (add ? 1 : -1);
  node* thisCurrent = head_;
  node* thisPrev = nullptr;
  node* otherCurrent = other.head_;

  while (otherCurrent != nullptr) {
    int otherIndex = otherCurrent->index;
    int otherValue = sign * otherCurrent->value;

    while (thisCurrent != nullptr && thisCurrent->index < otherIndex) {
      thisPrev = thisCurrent;
      thisCurrent = thisCurrent->next;
    }

    if (thisCurrent != nullptr && thisCurrent->index == otherIndex) {
      thisCurrent->value += otherValue;
    } else {
      node* newNode = new node(otherIndex, otherValue);

      if (thisPrev == nullptr) {
        newNode->next = head_;
        head_ = newNode;
      } else {
        newNode->next = thisCurrent;
        thisPrev->next = newNode;
      }
      thisPrev = newNode;
    }

    otherCurrent = otherCurrent->next;
  }
  checkListOrder();
}

// Удаление нулей
void SparseVector::removeZeros() {
  node* current = head_;
  node* prev = nullptr;

  while (current != nullptr) {
    if (current->value == 0) {
      node* toDelete = current;
      if (prev == nullptr) {
        head_ = current->next;
      } else {
        prev->next = current->next;
      }
      current = current->next;
      delete toDelete;
    } else {
      prev = current;
      current = current->next;
    }
  }
}

// Выводит узлы вектора для отладки
void SparseVector::checkListOrder() const {
  node* current = head_;

  while (current != nullptr && current->next != nullptr) {
    if (current->index >= current->next->index) {
      cerr << "=== ОШИБКА В ВЕКТОРЕ ===" << endl;
      cerr << "Размер вектора: " << size_ << endl;
      cerr << "Нарушен порядок узлов!" << endl;
      cerr << "Узел [" << current->index << "," << current->value << "] должен быть ПЕРЕД узлом ["
           << current->next->index << "," << current->next->value << "]" << endl;
      cerr << "Текущий список: ";

      cerr << "head_ → ";
      node* current = head_;
      while (current != nullptr) {
        cerr << "[" << current->index << ", " << current->value << "] → ";
        current = current->next;
      }
      cerr << "nullptr" << endl;

      cerr << "========================" << endl;

      throw runtime_error("Нарушен порядок");
    }
    current = current->next;
  }
}

// Получение элемента
int SparseVector::getElem(int index) const {
  checkListOrder();
  if (index < 0 || index >= size_) {
    throw out_of_range("Индекс вне диапазона");
  }

  node* current = head_;
  while (current != nullptr) {
    if (current->index == index) {
      return current->value;
    }

    if (current->index > index) {
      break;
    }
    current = current->next;
  }

  return 0;
}

// Установка элемента
void SparseVector::setElem(int index, int value) {
  if (index < 0 || index >= size_) {
    throw out_of_range("Индекс вне диапазона");
  }

  if (value == 0) {
    removeNode(index);
  } else {
    insertNode(index, value);
  }
  checkListOrder();
}

// Получение размера вектора
int SparseVector::getSize() const { return size_; }

// Вывод связанного списка
void SparseVector::printAllNodes() const {
  cout << "head_ → ";
  node* current = head_;
  while (current != nullptr) {
    cout << "[" << current->index << ", " << current->value << "] → ";
    current = current->next;
  }
  cout << "nullptr" << endl;
}

// Оператор присваивания
SparseVector& SparseVector::operator=(const SparseVector& other) {
  if (this == &other) {
    return *this;
  }

  if (size_ != other.size_) {
    throw invalid_argument("Векторы должны иметь одинаковый размер");
  }

  clear();
  copyList(other);
  checkListOrder();
  return *this;
}

// Оператор +=
SparseVector& SparseVector::operator+=(const SparseVector& other) {
  if (size_ != other.size_) {
    throw invalid_argument("Векторы должны иметь одинаковый размер");
  }

  addSubVector(other, true);
  removeZeros();
  checkListOrder();
  return *this;
}

// Оператор -=
SparseVector& SparseVector::operator-=(const SparseVector& other) {
  if (size_ != other.size_) {
    throw invalid_argument("Векторы должны иметь одинаковый размер");
  }

  addSubVector(other, false);
  removeZeros();
  checkListOrder();
  return *this;
}

// Оператор +
SparseVector SparseVector::operator+(const SparseVector& other) const {
  SparseVector result(*this);
  result += other;
  return result;
}

// Оператор -
SparseVector SparseVector::operator-(const SparseVector& other) const {
  SparseVector result(*this);
  result -= other;
  return result;
}

// Оператор ==
bool SparseVector::operator==(const SparseVector& other) const {
  if (size_ != other.size_) return false;

  for (int i = 0; i < size_; i++) {
    if (getElem(i) != other.getElem(i)) {
      return false;
    }
  }
  return true;
}

// Оператор !=
bool SparseVector::operator!=(const SparseVector& other) const { return !(*this == other); }