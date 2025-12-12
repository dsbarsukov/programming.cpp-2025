#include <iostream>

#include "SparseVector.h"

using namespace std;

int main() {
  SparseVector v1(10);
  v1.setElem(1, 3);
  v1.setElem(3, 4);
  v1.setElem(7, 10);
  v1.setElem(4, -10);

  SparseVector v2(10);
  v2.setElem(1, 3);
  v2.setElem(3, -4);
  v2.setElem(7, 70);
  v2.setElem(2, -10);

  v1.printAllNodes();
  v2.printAllNodes();
  (v1 + v2).printAllNodes();
  (v1 - v2).printAllNodes();

  return 0;
}