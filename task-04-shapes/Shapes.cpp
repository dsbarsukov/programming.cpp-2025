#include "Shapes.h"

#include <iostream>
#include <sstream>
#include <stdexcept>

Circle::Circle(double r) : r_(r) {
  if (r <= 0.0) {
    throw invalid_argument("Радиус круга должен быть положительным");
  }
}

double Circle::area() const { return 3.1415926535897932384 * r_ * r_; }

ShapeType Circle::type() const noexcept { return ShapeType::Circle; }

string Circle::name() const { return "Circle"; }

Rect::Rect(double w, double h) : w_(w), h_(h) {
  if (w <= 0.0 || h <= 0.0) {
    throw invalid_argument("Ширина и высота прямоугольника должны быть положительными");
  }
}

double Rect::area() const { return w_ * h_; }

ShapeType Rect::type() const noexcept { return ShapeType::Rect; }

string Rect::name() const { return "Rect"; }

unique_ptr<Shape> make_shape(ShapeType t, double a, double b) {
  switch (t) {
    case ShapeType::Circle:
      try {
        return make_unique<Circle>(a);
      } catch (const invalid_argument&) {
        return nullptr;
      }

    case ShapeType::Rect:
      try {
        return make_unique<Rect>(a, b);
      } catch (const invalid_argument&) {
        return nullptr;
      }

    default:
      return nullptr;
  }
}

unique_ptr<Shape> parse_shape(const string& line) {
  istringstream input_stream(line);

  string typeStr;
  input_stream >> typeStr;

  if (typeStr == "circle") {
    double r;
    if (input_stream >> r && input_stream.eof()) {
      return make_shape(ShapeType::Circle, r);
    }
  }

  if (typeStr == "rect") {
    double w, h;
    if (input_stream >> w >> h && input_stream.eof()) {
      return make_shape(ShapeType::Rect, w, h);
    }
  }

  return nullptr;
}

double total_area(const vector<unique_ptr<Shape>>& v) {
  double sum = 0.0;

  for (const unique_ptr<Shape>& ptr : v) {
    if (ptr != nullptr) {
      sum += ptr->area();
    }
  }

  return sum;
}

void print_shapes(const vector<unique_ptr<Shape>>& v) {
  cout << "\nСписок фигур:\n";
  cout << "=========================\n";
  int i = 1;
  for (const unique_ptr<Shape>& ptr : v) {
    cout << i << ". " << ptr->name() << ": площадь = " << ptr->area() << endl;
    i += 1;
  }
  cout << "=========================\n";
}