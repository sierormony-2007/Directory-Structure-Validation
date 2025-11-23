#include <iostream>
#include <vector>
#include <string>
#include "code.hpp"
using namespace std;
int main(){
// tNode<int> *root =  new tNode<int>(6);
// tNode<int> *left =  new tNode<int>(9);
// tNode<int> *right =  new tNode<int>(3);

// root->left = left;
// root->right = right;
vector<string> players={"Camboida", "Japan", "Malaysia", "Indonesia", "Philippines", "Singapore"};
vector<int> scores={50, 80, 70, 60, 90, 85};
Btree tournament;
tournament.buildTree(players, scores);
cout<<"Initial Bracket:"<<endl;
tournament.printBracket();


    return 0;
}