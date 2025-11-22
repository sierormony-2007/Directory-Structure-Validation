#ifndef TNODE_H
#define TNODE_H
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