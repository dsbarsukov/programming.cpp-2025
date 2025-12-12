#ifndef SPARSEVECTOR_H
#define SPARSEVECTOR_H

class SparseVector {
 private:
  int size_;

  struct node {
    int index;
    int value;
    node* next;

    node(int index, int value, node* next = nullptr);
  };

  node* head_;

  void clear();                                            // Очистка всего списка
  void copyList(const SparseVector& other);                // Копирование всего списка
  void insertNode(int index, int value);                   // Вставка узла
  void removeNode(int index);                              // Удаление узла
  void addSubVector(const SparseVector& other, bool add);  // Сложение/вычитание двух векторов
  void removeZeros();                                      // Удаление нулей
  void checkListOrder() const;                             // Выводит узлы вектора

 public:
  // Конструкторы и деструктор
  SparseVector(int size);
  SparseVector(const SparseVector& other);
  ~SparseVector();

  int getSize() const;                 // Получение размера вектора
  int getElem(int index) const;        // Получение элемента
  void setElem(int index, int value);  // Установка элемента
  void printAllNodes() const;          // Вывод связанного списка

  // Перегрузка операторов
  SparseVector& operator=(const SparseVector& other);
  SparseVector& operator+=(const SparseVector& other);
  SparseVector& operator-=(const SparseVector& other);
  SparseVector operator+(const SparseVector& other) const;
  SparseVector operator-(const SparseVector& other) const;
  bool operator==(const SparseVector& other) const;
  bool operator!=(const SparseVector& other) const;
};

#endif