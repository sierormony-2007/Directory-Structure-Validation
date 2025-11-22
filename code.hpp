#ifndef TNODE_H
#define TNODE_H
#include <iostream>
#include <string>
using namespace std;

template <typename T>
struct tNode{
    T value;
    T name;
    T match = 0;
    tNode<T> *left;
    tNode<T> *right;
    tNode( T val, T name){
        value = val;
        name = n;
        left = nullptr;
        right = nullptr;
    }
};



#endif