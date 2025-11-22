#include <iostream>
#include <string>
struct Node{
    string name;
    int contryID;
    int score;
    Node* left;
    Node* right;

    Node(int id, string n, int s){
        contryID = id;
        name = n;
        score = s;
        left = nullptr;
        right = nullptr;
    }
};

void insert(Node* root, int score, int id, string name){
    if(root == nullptr){
        return new Node(id, name);
    }

    if()
}