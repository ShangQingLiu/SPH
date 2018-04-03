//
// Created by ShangChingLiu on 4/4/2018.
//

#ifndef FIBONACCIHEAP_FIBONACCIHEAP_H
#define FIBONACCIHEAP_FIBONACCIHEAP_H

#include <iostream>

class FibonacciNode{
public:
    FibonacciNode();
    FibonacciNode(int NI);
    ~FibonacciNode();
    FibonacciNode &operator =(const FibonacciNode & other);
    int nodeNumber;
    int listNumber;
    FibonacciNode * L;
    FibonacciNode * R;
    FibonacciNode * parent;
    FibonacciNode * child;
    bool flag;
};
typedef FibonacciNode FN;
FN::FibonacciNode(int NI) {
    this->nodeNumber = NI;
}
FN::~FibonacciNode() {}
FibonacciNode& FN::operator=(const FibonacciNode &other) {
   nodeNumber = other.nodeNumber;
    listNumber = other.listNumber;
    L = new FibonacciNode();
    R = new FibonacciNode();
    parent = new FibonacciNode();
    child = new FibonacciNode();
    *L = *(other.L);
    *R = *(other.R);
    *parent = *(other.parent);
    *child = *(other.child);
     flag = other.flag;
}
class FibonacciHeap{
public:
    FibonacciHeap();
    ~FibonacciHeap();
    FibonacciHeap&operator=(const FibonacciHeap rhs);
    FibonacciNode * start;
    int nodeNumber;
    int maxDegree;
    FibonacciNode * * temp;
};
typedef FibonacciHeap FH;
FH::FibonacciHeap() {}
FH::~FibonacciHeap() {}
FibonacciHeap& FH::operator=(const FibonacciHeap rhs) {
 start = new FibonacciNode();
 *start = *(rhs.start);
 nodeNumber = rhs.nodeNumber;
 maxDegree = rhs.maxDegree;
 //don't know if cause problem -- sql
 *temp = new FibonacciNode();
 *temp = *(rhs.temp);
}
//port
//create heap
void insert(FH *heap,FN *node);
void findMin(FH *heap);
void merge(FH *heap1, FH *heap2);
void deleteMin(FH *heap);
void decreaseNode(FH *heap,int number, int newNumber);
void deleteNode(FH *heap,int number);

#endif //FIBONACCIHEAP_FIBONACCIHEAP_H
