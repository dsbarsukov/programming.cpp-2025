# RPN Calculator - Калькулятор обратной польской записи

Реализация калькулятора для вычисления выражений в обратной польской записи (Reverse Polish Notation).

## Быстрый старт

### Вариант 1: Через Makefile (только программа)
```bash
# Клонирование
git clone https://github.com/dsbarsukov/programming.cpp-2025.git
cd programming.cpp-2025/task-01-rpn-calculator

# Сборка программы
make
# Запуск демонстрационной программы
./rpn_calculator input.txt output.txt
```
### Вариант 2: Через CMake (программа и тесты)

```bash
# Клонирование
git clone https://github.com/dsbarsukov/programming.cpp-2025.git
cd programming.cpp-2025/task-01-rpn-calculator

# Сборка проекта
mkdir build && cd build
cmake ..    # Автоматически скачает GoogleTest
make        # Компиляция проекта

# Запуск тестов
./rpn_calculator_tests

# Запуск демонстрационной программы
./rpn_calculator ../input.txt ../output.txt
```

##  Структура проекта

- `RPNCalculator.h` - заголовочный файл с объявлениями функций
- `RPNCalculator.cpp` - реализация функций калькулятора
- `main.cpp` - основная программа с обработкой файлов
- `test.cpp` - unit-тесты (GoogleTest)
- `CMakeLists.txt` - конфигурация сборки CMake
- `Makefile` - для быстрой сборки через make

##  Функциональность

### Основные методы:
- `isNumber(const string& str)` - проверка, является ли строка числом
- `isOperator(const string& str)` - проверка, является ли строка оператором
- `applyOperator(const string& op, double a, double b)` - выполнение арифметической операции
- `evaluateRPN(const string& expression)` - вычисление RPN выражения

## Особенности:
- Поддержка целых и дробных чисел (включая отрицательные)
- Основные арифметические операции: +, -, *, /
- Проверка деления на ноль
- Обработка ошибок (некорректные токены, недостаток операндов)
- Работа с файлами ввода/вывода

## Формат входных данных
Каждая строка во входном файле содержит одно выражение в RPN формате:
- Числа и операторы разделены пробелами
- Поддерживаются целые, дробные и отрицательные числа

### Пример input.txt:
```text
3 4 +
5 1 2 + 4 * + 3 -
2 3 * 4 5 * +
10 3 /
7 2 - 3 *
4 2 /
```

### Пример output.txt:
```text
3 4 + = 7
5 1 2 + 4 * + 3 - = 14
2 3 * 4 5 * + = 26
10 3 / = 3.33333
7 2 - 3 * = 15
4 2 / = 2
```
##  Пример использования

```cpp
#include "RPNCalculator.h"
#include <iostream>

using namespace std;

int main() {
    try {
        // Простое выражение
        double result1 = evaluateRPN("3 4 +");
        cout << "3 4 + = " << result1 << endl; // 7
        
        // Более сложное выражение
        double result2 = evaluateRPN("5 1 2 + 4 * + 3 -");
        cout << "5 1 2 + 4 * + 3 - = " << result2 << endl;  // 14
    
        // Выражение с делением
        double result3 = evaluateRPN("10 4 /");
        cout << "10 4 / = " << result3 << endl;  // 2.5
       } catch (const exception& e) {
            cerr << "Ошибка: " << e.what() << endl;
       }
       
    return 0;
}
```
