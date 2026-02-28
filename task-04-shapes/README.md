# Shapes - Иерархия геометрических фигур на C++

Реализация абстрактного базового класса Shape и производных классов Circle и Rect с использованием полиморфизма, умных указателей и фабричных функций.

## Быстрый старт

### Вариант 1: Через Makefile (только программа)
```bash
# Клонирование
git clone https://github.com/dsbarsukov/programming.cpp-2025.git
cd programming.cpp-2025/task-04-shapes

# Сборка программы
make
# Запуск демонстрационной программы
./shapes
```
### Вариант 2: Через CMake (только программа, тестов нет)

```bash
# Клонирование
git clone https://github.com/dsbarsukov/programming.cpp-2025.git
cd programming.cpp-2025/task-04-shapes

# Сборка проекта
mkdir build && cd build
cmake ..    
make        # Компиляция проекта

# Запуск демонстрационной программы
./shapes
```

##  Структура проекта

- `Shapes.h` - заголовочный файл классов
- `Shapes.cpp` - реализация методов классов и функций
- `main.cpp` - пример использования
- `CMakeLists.txt` - конфигурация сборки

##  Функциональность

### Основные методы:
- `area()` - вычисление площади фигуры
- `type()` - получение типа фигуры (ShapeType::Circle / ShapeType::Rect)
- `name()` - получение названия фигуры ("Circle" / "Rect")

### Фабричные функции:
- `make_shape(ShapeType t, double a, double b = 0.0)` - создание фигуры по типу и параметрам
- `parse_shape(const string& line)` - создание фигуры из строки вида "circle 10" или "rect 3 4"

### Вспомогательные функции:
- `total_area(const vector<unique_ptr<Shape>>& v)` - подсчёт суммарной площади всех фигур в векторе
- `print_shapes(const vector<unique_ptr<Shape>>& v);` - вывод таблицы всех фигур вектора

##  Пример использования

```cpp
#include "Shapes.h"

#include <iostream>

using namespace std;

int main() {
  vector<unique_ptr<Shape>> shapes;

  shapes.push_back(make_shape(ShapeType::Circle, 5.0));
  shapes.push_back(parse_shape("rect 4 5"));

  cout << "Суммарная площадь: " << total_area(shapes) << endl;

  print_shapes(shapes);

  return 0;
}
```
