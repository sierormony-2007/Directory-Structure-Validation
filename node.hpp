#ifndef NODE_HPP
#define NODE_HPP

#include <string> // include string

struct Node {
    int matchId;           // Unique match ID
    std::string pL;        // Left participant
    std::string pR;        // Right participant
    std::string winner;    // Winner of this match
    Node* left;            // Pointer to left child
    Node* right;           // Pointer to right child

    // Constructor
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
