#ifndef BTREE
#define BTREE

#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <cmath>
#include "node.hpp"

using namespace std;

class BTree {
private:
    Node* root;
    int nextMatch;

    // Find node by match id
    Node* findNode(Node* node, int matchId) {
        if (!node) return nullptr;
        if (node->matchId == matchId) return node;

        Node* leftResult = findNode(node->left, matchId);
        if (leftResult) return leftResult;

        return findNode(node->right, matchId);
    }

    // Check if both participants are known
    bool bothParKnown(Node* node) {
        return !node->pL.empty() && !node->pR.empty();
    }

    // Promote winner to parent match
    void proWinner(Node* node, const string& winnerName) {
        Node* parent = findParent(root, node);
        if (parent) {
            if (parent->left == node) parent->pL = winnerName;
            else parent->pR = winnerName;

            // Auto win using BYE
            if (parent->pL == "BYE" && !parent->pR.empty()) {
                parent->winner = parent->pR;
                proWinner(parent, parent->pR);
            } else if (parent->pR == "BYE" && !parent->pL.empty()) {
                parent->winner = parent->pL;
                proWinner(parent, parent->pL);
            }
        }
    }

    Node* findParent(Node* cur, Node* target) {
        if (!cur || cur == target) return nullptr;
        if (cur->left == target || cur->right == target) return cur;

        Node* leftResult = findParent(cur->left, target);
        if (leftResult) return leftResult;

        return findParent(cur->right, target);
    }

public:
    BTree() {
        root = nullptr;
        nextMatch = 1;
    }

    // Build bracket
    void buildBra(vector<string> players) {
        if (players.empty()) return;

        int n = players.size();
        int rounds = ceil(log2(n));
        int totalLeaves = pow(2, rounds);

        while (players.size() < totalLeaves) players.push_back("BYE");

        queue<Node*> curLevel;

        // Create leaf matches
        for (int i = 0; i < players.size(); i += 2) {
            Node* match = new Node(nextMatch++);
            match->pL = players[i];
            match->pR = players[i + 1];

            if (players[i] == "BYE") match->winner = players[i + 1];
            else if (players[i + 1] == "BYE") match->winner = players[i];

            curLevel.push(match);
        }

        // Build tree bottom-up
        while (curLevel.size() > 1) {
            queue<Node*> nextLevel;
            while (curLevel.size() > 1) {
                Node* left = curLevel.front(); curLevel.pop();
                Node* right = curLevel.front(); curLevel.pop();

                Node* parent = new Node(nextMatch++);
                parent->left = left;
                parent->right = right;

                if (!left->winner.empty()) parent->pL = left->winner;
                if (!right->winner.empty()) parent->pR = right->winner;

                // Auto advance BYE
                if (parent->pL == "BYE" && !parent->pR.empty()) parent->winner = parent->pR;
                else if (parent->pR == "BYE" && !parent->pL.empty()) parent->winner = parent->pL;

                nextLevel.push(parent);
            }
            if (!curLevel.empty()) nextLevel.push(curLevel.front());
            curLevel = nextLevel;
        }

        root = curLevel.front();
    }

    // Record a result
    bool recRes(int matchId, string winnerName) {
        Node* match = findNode(root, matchId);
        if (!match) {
            cout << "Match not found!" << endl;
            return false;
        }

        if (!bothParKnown(match)) {
            cout << "Cannot record result: both participants not yet known." << endl;
            return false;
        }

        if (winnerName != match->pL && winnerName != match->pR) {
            cout << "Cannot record result: must be one of the participants." << endl;
            return false;
        }

        match->winner = winnerName;
        proWinner(match, winnerName);
        return true;
    }

    // Returns match path from first match to final
    vector<int> pathtoFinal(string player) {
        vector<int> path;
        ptfinalhelper(root, player, path);
        return path;
    }

    bool ptfinalhelper(Node* node, const string& player, vector<int>& path) {
        if (!node) return false;

        bool isInMatch = (node->pL == player || node->pR == player);
        if (isInMatch) {
            path.push_back(node->matchId);
            return true;
        }

        if (ptfinalhelper(node->left, player, path) || ptfinalhelper(node->right, player, path)) {
            path.push_back(node->matchId);
            return true;
        }

        return false;
    }

    // When two players would meet
    pair<int, int> wouldMeet(string p1, string p2) {
        Node* meeting = findAvaiTime(root, p1, p2);
        if (!meeting) return {-1, -1};
        int round = getRoundNum(meeting);
        return {meeting->matchId, round};
    }

    Node* findAvaiTime(Node* node, const string& p1, const string& p2) {
        if (!node) return nullptr;

        bool curHasP1 = (node->pL == p1 || node->pR == p1);
        bool curHasP2 = (node->pL == p2 || node->pR == p2);

        if (curHasP1 && curHasP2) return node;

        Node* leftAvai = findAvaiTime(node->left, p1, p2);
        Node* rightAvai = findAvaiTime(node->right, p1, p2);

        if (leftAvai && rightAvai) return node;
        else if (leftAvai) return leftAvai;
        else return rightAvai;
    }

    // Round number
    int getRoundNum(Node* target) {
        return getRoundHelper(root, target, 1);
    }

    int getRoundHelper(Node* node, Node* target, int level) {
        if (!node) return -1;
        if (node == target) return level;

        int leftLevel = getRoundHelper(node->left, target, level + 1);
        if (leftLevel != -1) return leftLevel;

        return getRoundHelper(node->right, target, level + 1);
    }

    // Print bracket grouped by round
    void printBracket() {
        if (!root) return;

        queue<pair<Node*, int>> q;
        q.push({root, 1});
        int curRound = 1;

        cout << "Round " << curRound << ":\n";

        while (!q.empty()) {
            auto [node, round] = q.front(); q.pop();

            if (round != curRound) {
                curRound = round;
                cout << "\nRound " << curRound << ":\n";
            }

            cout << " Match " << node->matchId << ": "
                 << node->pL << " vs " << node->pR
                 << " -> winner: " << (node->winner.empty() ? "?" : node->winner)
                 << endl;

            if (node->left) q.push({node->left, round + 1});
            if (node->right) q.push({node->right, round + 1});
        }
    }

    Node* getRoot() { return root; }
};

#endif
