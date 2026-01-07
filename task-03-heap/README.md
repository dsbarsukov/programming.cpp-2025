# Heap - Реализация Min-Heap на C++

Реализация шаблонного класса для работы с минимальной кучей (Min-Heap) с использованием статического массива.
##  Быстрый старт

### Вариант 1: Через Makefile (только программа)
```bash
# Клонирование
git clone https://github.com/dsbarsukov/programming.cpp-2025.git
cd programming.cpp-2025/task-03-heap

# Сборка программы
make
# Запуск демонстрационной программы
./heap
```
### Вариант 2: Через CMake (программа и тесты)

```bash
# Клонирование
git clone https://github.com/dsbarsukov/programming.cpp-2025.git
cd programming.cpp-2025/task-03-heap

# Сборка проекта
mkdir build && cd build
cmake ..    # Автоматически скачает GoogleTest
make        # Компиляция проекта

# Запуск тестов
./heap_tests

# Запуск демонстрационной программы
./heap
```

##  Структура проекта

- `Heap.h` - заголовочный файл шаблонного класса Heap
- `main.cpp` - пример использования
- `test.cpp` - unit-тесты (GoogleTest)
- `CMakeLists.txt` - конфигурация сборки

##  Функциональность

### Основные методы:
- `Heap<T, MaxSize>()` - конструктор кучи
- `add(const T& value)` - добавление элемента
- `getFirst()` - извлечение минимального элемента
- `peekFirst()` - просмотр минимального элемента без извлечения
- `size()`, `isEmpty()`, `isFull()` - информация о состоянии

## Особенности:
- Шаблонный класс работает с любыми типами, поддерживающими оператор <
- Статическое хранение в массиве фиксированного размера
- Поддерживает int, double, string и пользовательские типы

##  Пример использования

```cpp
#include "Heap.h"
#include <iostream>
#include <string>

using namespace std;

int main() {
    // Пример с целыми числами
    Heap<int, 10> intHeap;
    
    intHeap.add(5);
    intHeap.add(3);
    intHeap.add(7);
    intHeap.add(1);
    
    cout << "Минимальный элемент: " << intHeap.peekFirst() << endl;
    
    while (!intHeap.isEmpty()) {
        cout << intHeap.getFirst() << " ";
    }
    
    // Пример со строками
    Heap<string, 5> stringHeap;
    
    stringHeap.add("banana");
    stringHeap.add("apple");
    stringHeap.add("cherry");
    
    cout << "\nПервая строка: " << stringHeap.getFirst() << endl;
    
    return 0;
}
```
