#include <iostream>
#include <string>
// struct Node{
//     string name;
//     int contryID;
//     int score;
//     Node* left;
//     Node* right;

//     Node(int id, string n, int s){
//         contryID = id;
//         name = n;
//         score = s;
//         left = nullptr;
//         right = nullptr;
//     }
// };
struct Node{
    int matchId;
    string pL;
    string pR;
    string winner;
    Node* left;
    Node *right;
Node(int  id) {
   matchId = id;
   pL = ("");
   pR = ("");
   winner = ("");
   left = nullptr;
   right = nullptr;
}
};
