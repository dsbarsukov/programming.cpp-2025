# SparseVector - Разреженный вектор на C++

Реализация класса для работы с разреженными векторами с использованием односвязного списка.

## Быстрый старт

### Вариант 1: Через Makefile (только программа)
```bash
# Клонирование
git clone https://github.com/dsbarsukov/programming.cpp-2025.git
cd programming.cpp-2025/task-02-sparse-vector

# Сборка программы
make
# Запуск демонстрационной программы
./sparse_vector
```
### Вариант 2: Через CMake (программа и тесты)

```bash
# Клонирование
git clone https://github.com/dsbarsukov/programming.cpp-2025.git
cd programming.cpp-2025/task-02-sparse-vector

# Сборка проекта
mkdir build && cd build
cmake ..    # Автоматически скачает GoogleTest
make        # Компиляция проекта

# Запуск тестов
./tests

# Запуск демонстрационной программы
./sparse_vector_tests
```

##  Структура проекта

- `SparseVector.h` - заголовочный файл класса
- `SparseVector.cpp` - реализация класса
- `main.cpp` - пример использования
- `test.cpp` - unit-тесты (GoogleTest)
- `CMakeLists.txt` - конфигурация сборки

##  Функциональность

### Основные методы:
- `SparseVector(int size)` - конструктор
- `getSize()`, `getElem()`, `setElem()` - базовые операции
- Конструктор копирования и оператор присваивания

### Перегруженные операторы:
- `+`, `-` - арифметические операции
- `+=`, `-=` - составные присваивания
- `==`, `!=` - сравнение векторов



##  Пример использования

```cpp
#include "SparseVector.h"

int main() {
    SparseVector v1(100), v2(100);
    
    v1.setElem(5, 10);
    v1.setElem(2, 7);
    
    v2.setElem(1, 4);
    v2.setElem(5, 3);
    
    SparseVector result = v1 + v2;
    // result: [1,4] → [2,7] → [5,13]
    
    return 0;
}
```
