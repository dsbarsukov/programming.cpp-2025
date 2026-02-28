#ifndef SHAPES_H
#define SHAPES_H

#include <memory>
#include <vector>
#include <string>

using namespace std;

enum class ShapeType { Circle, Rect };

class Shape {
public:
  virtual ~Shape() = default;
  virtual double area() const = 0;
  virtual ShapeType type() const noexcept = 0;
  virtual string name() const = 0;
};

class Circle final : public Shape {
public:
  explicit Circle(double r);
  double area() const override;
  ShapeType type() const noexcept override;
  string name() const override;
private:
  double r_;
};

class Rect final : public Shape {
public:
  Rect(double w, double h);
  double area() const override;
  ShapeType type() const noexcept override;
  string name() const override;
private:
  double w_, h_;
};

unique_ptr<Shape> make_shape(ShapeType t, double a, double b = 0.0);
unique_ptr<Shape> parse_shape(const string& line);

double total_area(const vector<unique_ptr<Shape>>& v);

#endif