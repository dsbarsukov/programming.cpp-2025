#include "SparseVector.h"
#include <iostream>

using namespace std;

int main() {

    SparseVector v(10);
    v.setElem(1, 3);
    v.setElem(3, 4);
    v.setElem(7, 10);
    v.setElem(4, -10);

    for ( int i = 0; i < v.getSize(); i ++ ) {
        cout << "[ " << i << " ] = " << v.getElem(i) << endl;
    }

    cout << endl;

    v.printAllNodes();
    return 0;
}