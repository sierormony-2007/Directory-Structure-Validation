#ifndef BTREE
#define BTREE
#include <iostream>
#include <string>
#include <vector>
#include "node.hpp"
using namespace std;

template <typename T>
class BTree{
    
    private:
        string tName;
        int ID;
        int score;
        int match;
        Node<T>* root;
        Node<T>* left;
        Node<T>* right;
    public:
    BTree(){
        root = nullptr;
        left = nullptr;
        right = nullptr;
    }
    void insert(string tName, int score, int match){
            if(root == nullptr){
                root = new Node<T>(score);
                return;
            }
            Node<T>* cur = root;
            while(true){
                if(cur->score < score){
                    if(cur->right == nullptr){
                        cur->right = new Node<T>(score);
                        break;
                    }else{
                        cur = cur->right;
                    }
                } else if(cur->score > score){
                    if(cur->left == nullptr){
                        cur->left = new Node<T>(score);
                        break;
                    }else{
                        cur = cur->left;
                    }
                }
            }
        }
        Node<T>* get_root(){
            return root;
        }
        vector<T>pos_order(Node<T>){
            vector<T>result;
            if(root == nullptr){
                return result;
            }
            //left
            vector<T>left = pos_order(r->left);
            result.insert(result.end(), left.begin(), left.end());
            //right
            vector<T>right = pos_order(r->right);
            result.insert(result.end(), right.begin(), right.end());
            //root
            result.push_back(r->value);
        }

};










#endif