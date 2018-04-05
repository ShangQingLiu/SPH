//
// Created by ShangChingLiu on 4/4/2018.
//
#include "FibonacciHeap.h"
#include <map>
void insert(FH *heap,FN *node){
    if(!heap->start){
        heap->start = node;
        node->L = node;
        node->R = node;
    }
    else{
        //add node
        node->R = heap->start->R;
        node->R->L = node;
        heap->start->R = node;
        node->L = heap->start;
        //if smaller than the minimum number
        if(node->nodeNumber < heap->start->nodeNumber){
            heap->start = node;
        }
    }
}
int findMin(FH *heap){
    return heap->start->nodeNumber;
}
FH* merge(FH *heap1, FH *heap2){
    FN* tmpNode1 = new FN();
    FN* tmpNode2 = new FN();
    FH* tmpHeap = new FH();
    tmpNode1 = heap1->start;
    tmpNode2 = heap2->start;
    if(!tmpNode1){
        tmpHeap = heap2;
        return tmpHeap;
    }
    if(!tmpNode2){
        tmpHeap = heap1;
        return tmpHeap;
    }
    while(tmpNode1->R){
        tmpNode1 = tmpNode1->R;
    }
    tmpNode1->R = tmpNode2;
    tmpHeap->start = tmpNode1;
    tmpHeap->nodeNumbers = heap1->nodeNumbers + heap2->nodeNumbers;
    tmpHeap->maxDegree = heap1->maxDegree > heap2->maxDegree ? heap1->maxDegree: heap2->maxDegree;
    delete(heap1);
    delete(heap2);
    return tmpHeap;
}
FH* deleteMin(FH *heap){
    std::map<int,FN*> mymap;
   int degreeCount = 0;
    int number = 5555;
    FN * tmpHeadNode = new FN();
    if(!heap->start){
        printf("There is nothing can be delete");
    } else {
        tmpHeadNode = heap->start;
        if (tmpHeadNode->child) {//one line tree
            if (tmpHeadNode->R = tmpHeadNode) {
                heap->start = tmpHeadNode->child;
                tmpHeadNode->child->parent = NULL;
                delete (tmpHeadNode);
                return heap;
            } else {//forest
                heap->start = tmpHeadNode->child;//temporary
                tmpHeadNode->child->L = tmpHeadNode->L;
                tmpHeadNode->L->R = tmpHeadNode->child;
                tmpHeadNode->child->R = tmpHeadNode->R;
                tmpHeadNode->R->L = tmpHeadNode->child;
                tmpHeadNode->child->parent = NULL;
                delete (tmpHeadNode);
            }
        } else if (tmpHeadNode->R == tmpHeadNode) {
            delete (tmpHeadNode);
            heap->start = NULL;
            return heap;
        } else {//no child
            heap->start = tmpHeadNode->R;//temporary
            tmpHeadNode->R->L = tmpHeadNode->L;
            tmpHeadNode->L->R = tmpHeadNode->R;
        }
        /*find the min node*/
        FN *MINNode = new FN();
        tmpHeadNode = heap->start;
        MINNode = tmpHeadNode;
        while (1) {
           if(tmpHeadNode->R == heap->start) {
               break;
           }
            if (tmpHeadNode->nodeNumber > tmpHeadNode->R->nodeNumber) {
                MINNode = tmpHeadNode->R;
            }
            tmpHeadNode = tmpHeadNode->R;
        }
        heap->start = MINNode;
        /*--------------done finding the min node-----------------*/
        /*--------------start combine the same degree of tree-----*/
        tmpHeadNode = MINNode;
        FN * tmpNode = new FN();
        int flag = 0;
        while(1){
            if(flag == 1){
                break;
            }
           if(tmpHeadNode->R==heap->start){
               flag = 1;
           }
            number = tmpHeadNode->nodeNumber;
            tmpNode = tmpHeadNode;
            degreeCount = 1;
            while (tmpNode->child) {
                degreeCount++;
                tmpNode = tmpNode->child;
            }
            FN* node = new FN();
            auto iter = mymap.find(degreeCount);
            if(iter != mymap.end()){
               //merge two same degree tree
                node = iter->second;
                FN* tmpChildNode = new FN();
                FN* tmpFChildNode = new FN();
                //if the one in the map have smaller headnode
                if(tmpHeadNode->nodeNumber > node->nodeNumber){
                    //if this node have no child
                    if(!node->child){//situation in degree 1
                        node->R = tmpHeadNode->R;
                        tmpHeadNode->R->L = node;
                        node->child = tmpHeadNode;
                        tmpHeadNode->parent = node;
                        tmpHeadNode->L = tmpHeadNode;
                        tmpHeadNode->R = tmpHeadNode;
                        mymap.erase(degreeCount);
                        mymap.insert(std::pair<int,FN*>(degreeCount*2,node));
                    }else{//if this node have child
                        tmpChildNode = node->child;
                        tmpFChildNode = node->child;
                        //finde the last node of the child chain
                        while(tmpChildNode->R != tmpChildNode){
                            tmpChildNode = tmpChildNode->R;
                        }
                        //add another tree there
                        tmpChildNode->R = tmpHeadNode;
                        tmpHeadNode->L = tmpChildNode;
                        tmpHeadNode->R = tmpFChildNode;
                        tmpFChildNode->L = tmpHeadNode;
                        mymap.erase(degreeCount);
                        mymap.insert(std::pair<int,FN*>(degreeCount*2,node));
                    }
                }else{//if new one coming has smaller head node
                   if(tmpHeadNode->child){//if got the child
                       tmpChildNode = tmpHeadNode->child;
                       tmpFChildNode = tmpChildNode;
                       //find the last of the child
                       while(tmpChildNode->R!=tmpChildNode){
                           tmpChildNode = tmpChildNode->R;
                       }
                       //add another head of the tree here
                       tmpChildNode->R = node;
                       node->L = tmpChildNode;
                       node->R = tmpFChildNode;
                       tmpFChildNode->L = node;
                       mymap.erase(degreeCount);
                       mymap.insert(std::pair<int,FN*>(degreeCount*2,tmpHeadNode));
                   }else{//situation in degree 1
                       tmpHeadNode->R = node->R;
                       node->R->L = tmpHeadNode;
                       tmpHeadNode->child = node;
                       node->parent = tmpHeadNode;
                       node->L = node;
                       node->R = node;
                       mymap.erase(degreeCount);
                       mymap.insert(std::pair<int,FN*>(degreeCount*2,tmpHeadNode));
                   }

                }
            } else{
                mymap.insert(std::pair<int,FN*>(degreeCount,tmpHeadNode));
            }
            tmpHeadNode = tmpHeadNode->R;
        }

    }
    /*---------------finish combine the tree-----*/
    return heap;
}
void decreaseNode(FH *heap,int numaber, int newNumber);
void deleteNode(FH *heap,int number);
FN::FibonacciNode(){}
FibonacciNode::FibonacciNode(int NI) {
    this->nodeNumber = NI;
}

FN::~FibonacciNode() {}
FibonacciNode& FN::operator=(const FibonacciNode &other) {
    nodeNumber = other.nodeNumber;
    listNumber = other.listNumber;
    childNumber = other.childNumber;
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

//init function
FH::FibonacciHeap() {}
FH::~FibonacciHeap() {}
FibonacciHeap& FH::operator=(const FibonacciHeap rhs) {
    start = new FibonacciNode();
    *start = *(rhs.start);
    nodeNumbers = rhs.nodeNumbers;
    maxDegree = rhs.maxDegree;
    //don't know if cause problem -- sql
    // *temp = new FibonacciNode();
}
