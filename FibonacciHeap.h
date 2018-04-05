//
// Created by ShangChingLiu on 4/4/2018.
//

#ifndef FIBONACCIHEAP_FIBONACCIHEAP_H
#define FIBONACCIHEAP_FIBONACCIHEAP_H

#include <iostream>
/*  -----------
 * |parentNode |
 * |-----------|
 * |ListOrder  |
 * |-----------|
 * |nodeNumber |
 * |-----------|
 * |left|right |
 * |-----------|
 * |childNumber|
 * |-----------|
 * |    flag   |
 * |-----------|
 * |firstChild |
 *  -----------
 */
class FibonacciNode{
public:
    FibonacciNode();
    FibonacciNode(int NI);
    ~FibonacciNode();
    FibonacciNode &operator =(const FibonacciNode & other);
    //struct
    FibonacciNode * parent;
    int listNumber;
    int nodeNumber;
    FibonacciNode * L; FibonacciNode * R;
    int childNumber;
    FibonacciNode * child;
    bool flag;
};
typedef FibonacciNode FN;

class FibonacciHeap{
public:
    FibonacciHeap();
    ~FibonacciHeap();
    FibonacciHeap&operator=(const FibonacciHeap rhs);
    FibonacciNode * start;
    int nodeNumbers;
    int maxDegree;
};
typedef FibonacciHeap FH;
//port
//create heap
void insert(FH *heap,FN *node);
int findMin(FH *heap);
FH* merge(FH *heap1, FH *heap2);
FH* deleteMin(FH *heap);
void decreaseNode(FH *heap,int number, int newNumber);
void deleteNode(FH *heap,int number);

#endif //FIBONACCIHEAP_FIBONACCIHEAP_H
