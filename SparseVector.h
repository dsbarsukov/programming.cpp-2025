#ifndef SPARSEVECTOR_H
#define SPARSEVECTOR_H

class SparseVector {
private:
    int size_;
    
    struct node {
        int index;
        int value;
        node* next;
        
        node(int index, int value, node* next = nullptr);
    };
    
    node* head_;

public:
    SparseVector(int size);
    ~SparseVector();
    
    int getSize() const;
};

#endif