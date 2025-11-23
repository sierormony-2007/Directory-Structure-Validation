#ifndef BTREE
#define BTREE

#include <iostream>
#include <vector>
#include <queue>
#include <cmath>
#include <string>
#include "node.hpp"

class BTree {
private:
    Node* root;
    int nextMatch;

    Node* findNode(Node* node, int matchId) {
        if(!node) return nullptr;
        if(node->matchId == matchId) return node;
        Node* leftResult = findNode(node->left, matchId);
        if(leftResult) return leftResult;
        return findNode(node->right, matchId);
    }

    Node* findParent(Node* cur, Node* target) {
        if(!cur || cur == target) return nullptr;
        if(cur->left == target || cur->right == target) return cur;
        Node* leftResult = findParent(cur->left, target);
        if(leftResult) return leftResult;
        return findParent(cur->right, target);
    }

    void promoteWinner(Node* node, const std::string& winnerName) {
        Node* parent = findParent(root, node);
        if(!parent) return;
        if(parent->left == node) parent->pL = winnerName;
        else parent->pR = winnerName;

        if(parent->pL == "BYE" && !parent->pR.empty()) {
            parent->winner = parent->pR;
            promoteWinner(parent, parent->pR);
        }
        else if(parent->pR == "BYE" && !parent->pL.empty()) {
            parent->winner = parent->pL;
            promoteWinner(parent, parent->pL);
        }
    }

public:
    BTree() {
        root = nullptr;
        nextMatch = 1;
    }

    void buildBracket(const std::vector<std::string>& players) {
        if(players.size() > 8) {
            std::cout << "Only 8 teams allowed for this bracket.\n";
            return;
        }

        std::vector<std::string> t = players;
        while(t.size() < 8) t.push_back("BYE");  // fill BYE if less than 8

        std::queue<Node*> q;
        for(int i=0; i<8; i+=2) {
            Node* match = new Node(nextMatch++);
            match->pL = t[i];
            match->pR = t[i+1];
            if(t[i] == "BYE") match->winner = t[i+1];
            else if(t[i+1] == "BYE") match->winner = t[i];
            q.push(match);
        }

        while(q.size() > 1) {
            std::queue<Node*> nextLevel;
            while(!q.empty()) {
                Node* left = q.front(); q.pop();
                Node* right = q.front(); q.pop();
                Node* parent = new Node(nextMatch++);
                parent->left = left;
                parent->right = right;
                if(!left->winner.empty()) parent->pL = left->winner;
                if(!right->winner.empty()) parent->pR = right->winner;
                if(parent->pL == "BYE") parent->winner = parent->pR;
                else if(parent->pR == "BYE") parent->winner = parent->pL;
                nextLevel.push(parent);
            }
            q = nextLevel;
        }
        root = q.front();
    }

    bool recordResult(int matchId, const std::string& winnerName) {
        Node* match = findNode(root, matchId);
        if(!match) return false;
        if((winnerName != match->pL) && (winnerName != match->pR)) return false;
        match->winner = winnerName;
        promoteWinner(match, winnerName);
        return true;
    }

    void printBracket() {
        if(!root) return;
        std::queue<std::pair<Node*, int>> q;
        q.push({root, 1});
        int curRound = 1;
        std::cout << "Round " << curRound << ":\n";

        while(!q.empty()) {
            auto [node, round] = q.front(); q.pop();
            if(round != curRound) {
                curRound = round;
                std::cout << "\nRound " << curRound << ":\n";
            }
            std::cout << " Match " << node->matchId << ": " 
                      << node->pL << " vs " << node->pR 
                      << " -> Winner: " << (node->winner.empty() ? "?" : node->winner)
                      << "\n";
            if(node->left) q.push({node->left, round+1});
            if(node->right) q.push({node->right, round+1});
        }
    }

    Node* getRoot() { return root; }
};

#endif
