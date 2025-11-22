#ifndef TNODE_H
#define TNODE_H
#include <iostream>
#include <string>
using namespace std;

template <typename T>
struct tNode{
    T value;
    string name;
    int match = 0;
    tNode<T> *left;
    tNode<T> *right;
    tNode( T val){
        value = val;
        left = nullptr;
        right = nullptr;
    }
};



#endif