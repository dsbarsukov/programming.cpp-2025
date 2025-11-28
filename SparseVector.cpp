#include "SparseVector.h"
#include <stdexcept>

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

// Вставка узла (упрощенная версия: Нужно 1. Поиск позиции для вставки + перелинковкой указателей 2. Проверка существования узла с таким индексом + Обновление значения)
void SparseVector::insertNode(int index, int value) {
    head_ = new node(index, value, head_);
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