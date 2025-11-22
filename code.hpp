#ifndef FILE_H
#define FILE_H
template <typename T>
struct tNode{
    T value;
    tNode<T> *left;
    tNode<T> *right;
    tNode(T val){
        value = val;
        left = nullptr;
        right = nullptr;
    }
};



#endif