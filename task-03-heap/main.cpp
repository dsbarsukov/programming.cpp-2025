#include <iostream>
#include <string>

#include "Heap.h"

using namespace std;

int main() {
  cout << "=== Демонстрация шаблонной кучи (Min-Heap) ===\n\n";

  cout << "1. Куча целых чисел:\n";
  Heap<int, 5> intHeap;

  intHeap.add(30);
  intHeap.add(10);
  intHeap.add(50);
  intHeap.add(20);
  intHeap.add(40);

  cout << "   Добавлено: 30, 10, 50, 20, 40\n";
  cout << "   Минимальный элемент: " << intHeap.peekFirst() << "\n";

  cout << "   Извлечение: ";
  while (!intHeap.isEmpty()) {
    cout << intHeap.getFirst() << " ";
  }
  cout << "\n\n";

  cout << "2. Куча дробных чисел:\n";
  Heap<double, 4> doubleHeap;

  doubleHeap.add(3.14);
  doubleHeap.add(2.71);
  doubleHeap.add(1.41);
  doubleHeap.add(1.73);

  cout << "   Добавлено: 3.14, 2.71, 1.41, 1.73\n";
  cout << "   Минимальный элемент: " << doubleHeap.peekFirst() << "\n";

  cout << "   Извлечение: ";
  while (!doubleHeap.isEmpty()) {
    cout << doubleHeap.getFirst() << " ";
  }
  cout << "\n\n";

  cout << "3. Куча строк:\n";
  Heap<string, 4> stringHeap;

  stringHeap.add("orange");
  stringHeap.add("apple");
  stringHeap.add("banana");
  stringHeap.add("cherry");

  cout << "   Добавлено: \"orange\", \"apple\", \"banana\", \"cherry\"\n";
  cout << "   Первая строка: \"" << stringHeap.peekFirst() << "\"\n";

  cout << "   Извлечение: ";
  while (!stringHeap.isEmpty()) {
    cout << "\"" << stringHeap.getFirst() << "\" ";
  }
  cout << "\n\n";

  cout << "=== Демонстрация завершена ===\n";
  return 0;
}