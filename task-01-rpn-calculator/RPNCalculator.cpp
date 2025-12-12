#include "RPNCalculator.h"

#include <cctype>     // для isdigit()
#include <sstream>    // для istringstream
#include <stack>      // для stack
#include <stdexcept>  // для исключений
#include <string>

using namespace std;

// Проверяет, является ли строка числом
bool isNumber(const string& str) {
  if (str.length() == 0) {
    return false;
  }

  size_t start = 0;
  if (str[0] == '-' && str.length() > 1) {
    start = 1;
  }

  bool hasDecimalPoint = false;
  bool hasDigit = false;

  for (size_t i = start; i < str.length(); i++) {
    if (str[i] == '.') {
      if (hasDecimalPoint) {
        return false;
      }
      hasDecimalPoint = true;
    } else if (isdigit(str[i])) {
      hasDigit = true;
    } else {
      return false;
    }
  }

  return hasDigit;
}

// Проверяет, является ли строка оператором
bool isOperator(const string& str) { return str == "+" || str == "-" || str == "*" || str == "/"; }

// Применяет оператор к двум операндам
double applyOperator(const string& op, double a, double b) {
  if (op == "+") return a + b;
  if (op == "-") return a - b;
  if (op == "*") return a * b;
  if (op == "/") {
    if (b == 0) {
      throw runtime_error("Деление на ноль");
    }
    return a / b;
  }
  throw runtime_error("Неизвестный оператор: " + op);
}

// Вычисляет RPN выражение
double evaluateRPN(const string& expression) {
  stack<double> numbers;

  istringstream iss(expression);
  string token;

  while (iss >> token) {
    if (isNumber(token)) {
      double number = stod(token);
      numbers.push(number);

    } else if (isOperator(token)) {
      if (numbers.size() < 2) {
        throw runtime_error("Недостаточно операндов для оператора " + token);
      }

      double b = numbers.top();
      numbers.pop();

      double a = numbers.top();
      numbers.pop();

      double result = applyOperator(token, a, b);

      numbers.push(result);

    } else {
      throw runtime_error("Некорректный токен: " + token);
    }
  }

  if (numbers.size() != 1) {
    throw runtime_error("Некорректное выражение");
  }

  return numbers.top();
}