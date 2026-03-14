# C++ Programming Course 2025


[![CI](https://github.com/dsbarsukov/programming.cpp-2025/actions/workflows/ci.yml/badge.svg)](https://github.com/dsbarsukov/programming.cpp-2025/actions/workflows/ci.yml)
[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)
[![C++ Standard](https://img.shields.io/badge/C%2B%2B-14-blue.svg)](https://en.cppreference.com/w/cpp/14)

Репозиторий для выполнения практических заданий по курсу C++. Каждое задание размещается в отдельной директории и имеет собственную структуру проекта. В репозитории настроен общий CI для автоматической проверки всех заданий.

## Структура проекта
```text
programming.cpp-2025/
├── task-01-rpn-calculator/     # Задание 1: RPN калькулятор
├── task-02-sparse-vector/      # Задание 2: Разреженный вектор
├── task-03-heap/               # Задание 3: Куча
├── task-04-shapes/             # Задание 4: Фигуры
├── .github/workflows/          # CI
├── CMakeLists.txt              # Общий CMake файл (для IDE)
├── LICENSE                     # MIT лицензия
├── .clang-format               
├── .gitignore   
└── README.md                   
```

## Быстрый старт

### Клонирование репозитория
```bash
git clone https://github.com/dsbarsukov/programming.cpp-2025.git
cd programming.cpp-2025
```
### Выбор задания
Каждое задание независимо. Перейдите в нужную директорию:
```bash 
cd task-01-rpn-calculator                     # Задание 1
cd task-02-sparse-vector                      # Задание 2
cd task-03-heap                               # Задание 3
cd task-04-shapes                             # Задание 4
```
### Сборка и запуск
Для каждого задания доступны два варианта сборки:

#### Вариант 1: Через Makefile (только программа)
```bash 
make        
./rpn_calculator input.txt output.txt         # Задание 1
./sparse_vector                               # Задание 2  
./heap                                        # Задание 3
./shapes                                      # Задание 4
make clean  
```

#### Вариант 2: Через CMake (программа и тесты)
```bash 
# Сборка проекта
mkdir build && cd build
cmake ..    # Автоматически скачает GoogleTest
make        # Компиляция проекта

# Запуск тестов
./rpn_calculator_tests                        # Задание 1
./sparse_vector_tests                         # Задание 2  
./heap_tests                                  # Задание 3

# Запуск демонстрационной программы
./rpn_calculator ../input.txt ../output.txt   # Задание 1
./sparse_vector                               # Задание 2  
./heap                                        # Задание 3
./shapes                                      # Задание 4
```

## Технологии и инструменты
- **Язык**: C++14 
- **Сборка**: Makefile (обязательно), CMake (опционально)
- **Тестирование**: GoogleTest - **CI**: GitHub Actions 
- **Лицензия**: MIT 

## Code Style 
Код соответствует [Google C++ Style Guide](https://google.github.io/styleguide/cppguide.html) с адаптациями:
- **Длина строки:** 120 символов (вместо стандартных 80) 
- **Проверка:** автоматически через `clang-format` в CI 
- **Конфигурация:** файл [.clang-format](.clang-format) в корне репозитория