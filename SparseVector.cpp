#include "SparseVector.h"

SparseVector::node::node(int index, int value, node* next)
    : index(index), value(value), next(next) {
}

SparseVector::SparseVector(int size) : size_(size), head_(nullptr) {
}

SparseVector::~SparseVector() {
}

int SparseVector::getSize() const {
    return size_;
}