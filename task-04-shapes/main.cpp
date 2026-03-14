#include <iostream>

#include "Shapes.h"

using namespace std;

int main() {
  vector<unique_ptr<Shape>> shapes;

  shapes.push_back(make_shape(ShapeType::Circle, 5.0));
  shapes.push_back(make_shape(ShapeType::Rect, 2.0, 3.0));

  shapes.push_back(parse_shape("circle 10"));
  shapes.push_back(parse_shape("rect 4 5"));

  cout << "Суммарная площадь: " << total_area(shapes) << endl;

  print_shapes(shapes);

  return 0;
}