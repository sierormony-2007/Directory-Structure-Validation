#ifndef NODE_HPP
#define NODE_HPP

#include <string>

struct Node {
    int matchId;
    std::string pL;      // Left participant
    std::string pR;      // Right participant
    std::string winner;  // Winner
    Node* left;          // Previous match left
    Node* right;         // Previous match right

    Node(int id) {
        matchId = id;
        pL = "";
        pR = "";
        winner = "";
        left = nullptr;
        right = nullptr;
    }
};

#endif
