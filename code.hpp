#ifndef BTREE_HPP
#define BTREE_HPP

#include <iostream>
#include <vector>
#include <queue>
#include <cmath>
#include "node.hpp"
using namespace std;

class BTree {
private:
    Node* root;
    int nextMatch;

    Node* findNode(Node* node, int matchId) {
        if (!node) return nullptr;
        if (node->matchId == matchId) return node;

        Node* leftResult = findNode(node->left, matchId);
        if (leftResult) return leftResult;
        return findNode(node->right, matchId);
    }

    Node* findParent(Node* cur, Node* target) {
        if (!cur || cur == target) return nullptr;
        if (cur->left == target || cur->right == target) return cur;

        Node* leftResult = findParent(cur->left, target);
        if (leftResult) return leftResult;
        return findParent(cur->right, target);
    }

    void proWinner(Node* node, const string& winnerName) {
        Node* parent = findParent(root, node);
        if (!parent) return;

        if (parent->left == node) parent->pL = winnerName;
        else parent->pR = winnerName;

        // Auto-advance BYE
        if (parent->pL == "BYE" && !parent->pR.empty()) {
            parent->winner = parent->pR;
            proWinner(parent, parent->pR);
        }
        else if (parent->pR == "BYE" && !parent->pL.empty()) {
            parent->winner = parent->pL;
            proWinner(parent, parent->pL);
        }
    }

public:
    BTree() {
        root = nullptr;
        nextMatch = 1;
    }

    void buildBra(vector<string> players) {
        if (players.empty()) return;
        int n = players.size();
        int rounds = ceil(log2(n));
        int totalLeaves = pow(2, rounds);

        while (players.size() < totalLeaves) {
            players.push_back("BYE");
        }

        queue<Node*> curLevel;
        for (int i = 0; i < players.size(); i += 2) {//create rounds
            Node* match = new Node(nextMatch++);
            match->pL = players[i];
            match->pR = players[i + 1];

            if (players[i] == "BYE") match->winner = players[i + 1];
            else if (players[i + 1] == "BYE") match->winner = players[i];

            curLevel.push(match);
        }
        while (curLevel.size() > 1) {
            queue<Node*> nextLevel;
            while (curLevel.size() > 1) {//check pairs
                Node* left = curLevel.front(); curLevel.pop();
                Node* right = curLevel.front(); curLevel.pop();
                Node* parent = new Node(nextMatch++);
                parent->left = left;//subtrees
                parent->right = right;//subtrees

                if (!left->winner.empty()) parent->pL = left->winner;//contains winnner from left so we push it up to compare with the right
                if (!right->winner.empty()) parent->pR = right->winner;

                nextLevel.push(parent);//add it to the next level
            }
            if (!curLevel.empty()) nextLevel.push(curLevel.front());//check odd
            curLevel = nextLevel;//push to nexe level
        }
        root = curLevel.front();//update root to cur level
    }

    bool recRes(int matchId, const string& winnerName) {
        Node* match = findNode(root, matchId);
        if (!match) {
            cout << "Match not found!" << endl;
            return false;
        }

        if (match->pL.empty() || match->pR.empty()) {
            cout << "Cannot record result: both participants not yet known." << endl;
            return false;
        }

        if (winnerName != match->pL && winnerName != match->pR) {
            cout << "Cannot record result: winner must be one of the participants." << endl;
            return false;
        }

        match->winner = winnerName;
        proWinner(match, winnerName);
        return true;
    }

    void printBracketByRound() {
        if (!root) return;

        vector<vector<Node*>> rounds;
        queue<pair<Node*, int>> q;
        q.push({root, 0}); // 0 = final level
        int maxLevel = 0;

        while (!q.empty()) {
            auto [node, level] = q.front(); q.pop();
            if (rounds.size() <= level) rounds.push_back({});
            rounds[level].push_back(node);
            maxLevel = max(maxLevel, level);

            if (node->left) q.push({node->left, level + 1});
            if (node->right) q.push({node->right, level + 1});
        }

        int roundNum = 1;
        for (int i = maxLevel; i >= 0; i--) {
            cout << "\n=== Round " << roundNum++ << " ===\n";
            for (Node* n : rounds[i]) {
                cout << "Match " << n->matchId << ": "
                     << (n->pL.empty() ? "?" : n->pL) << " vs "
                     << (n->pR.empty() ? "?" : n->pR)
                     << " -> Winner: " << (n->winner.empty() ? "?" : n->winner)
                     << "\n";
            }
        }
    }

    Node* getRoot() { return root; }
};

#endif
