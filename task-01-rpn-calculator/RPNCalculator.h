#ifndef RPN_CALCULATOR_H
#define RPN_CALCULATOR_H

#include <string>

using namespace std;

// Проверяет, является ли строка числом
bool isNumber(const string& str);

// Проверяет, является ли строка оператором
bool isOperator(const string& str);

// Применяет оператор к двум операндам
double applyOperator(const string& op, double a, double b);

// Вычисляет RPN выражение
double evaluateRPN(const string& expression);

#endif