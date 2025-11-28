#include "SparseVector.h"
#include <stdexcept>
#include <iostream>

// Конструктор узла
SparseVector::node::node(int index, int value, node* next) : index(index), value(value), next(next) {
}

// Основной конструктор
SparseVector::SparseVector(int size) : size_(size), head_(nullptr) {
    if (size <= 0) {
        throw std::invalid_argument("Размер вектора должен быть положительным");
    }
}

// Конструктор копирования
SparseVector::SparseVector(const SparseVector& other) : size_(other.size_), head_(nullptr) {
    copyList(other);
}

// Деструктор
SparseVector::~SparseVector() {
    clear();
}

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
}

// Получение элемента
int SparseVector::getElem(int index) const {
    if (index < 0 || index >= size_) {
        throw std::out_of_range("Индекс вне диапазона");
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
        throw std::out_of_range("Индекс вне диапазона");
    }

    if (value == 0) {
        removeNode(index);
    } else {
        insertNode(index, value);
    }
}

// Получение размера вектора
int SparseVector::getSize() const {
    return size_;
}

void SparseVector::printAllNodes() const {
    std::cout << "head_ → ";
    node* current = head_;
    while (current != nullptr) {
        std::cout << "[" << current->index << ", " << current->value << "] → ";
        current = current->next;
    }
    std::cout << "nullptr" << std::endl;
}

// Оператор присваивания
SparseVector& SparseVector::operator=(const SparseVector& other) {
    if (this == &other) {
        return *this;
    }

    if (size_ != other.size_) {
        throw std::invalid_argument("Векторы должны иметь одинаковый размер");
    }

    clear();
    copyList(other);
    return *this;
}

// Оператор +=
SparseVector& SparseVector::operator+=(const SparseVector& other) {
    if (size_ != other.size_) {
        throw std::invalid_argument("Векторы должны иметь одинаковый размер");
    }

    node* current = other.head_;
    while (current != nullptr) {
        setElem(current->index, getElem(current->index) + current->value);
        current = current->next;
    }
    return *this;
}

// Оператор -=
SparseVector& SparseVector::operator-=(const SparseVector& other) {
    if (size_ != other.size_) {
        throw std::invalid_argument("Векторы должны иметь одинаковый размер");
    }

    node* сurrent = other.head_;
    while (сurrent != nullptr) {
        setElem(сurrent->index, getElem(сurrent->index) - сurrent->value);
        сurrent = сurrent->next;
    }
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
bool SparseVector::operator!=(const SparseVector& other) const {
    return !(*this == other);
}