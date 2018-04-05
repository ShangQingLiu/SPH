#include <iostream>
#include "FibonacciHeap.h"

int main() {
    FH* h1 = new FH();
    FH* h2 = new FH();
    FN* N[5] ;
    for(int i = 0; i<5; i++){
        N[i] = new FN(i+1);
    }
    for(int i = 0; i<2; i++){
        insert(h1,N[i]);
    }
    for(int i = 2; i <5; i++){
        insert(h2,N[i]);
    }
    int a = findMin(h1);
    int b = findMin(h2);
    std::cout<<"h1: " << a<< "h2: " << b<<std::endl;
    deleteMin(h2);
    int c = findMin(h2);
    std::cout<<"h1: " << a<< "h2: " << c<<std::endl;
    return 0;
}