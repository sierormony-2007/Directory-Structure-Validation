#include <iostream>
#include <vector>
#include <string>
#include "code.hpp"
using namespace std;

// tNode<int> *root =  new tNode<int>(6);
// tNode<int> *left =  new tNode<int>(9);
// tNode<int> *right =  new tNode<int>(3);

// root->left = left;
// root->right = right;

struct MatchScore {
    int scoreL;
    int scoreR;
};
    // Example list of players
//     vector<string> players = {"Alice", "Bob", "Charlie", "David", "Eve"};

//     // Create tournament
//     BTree tournament;
//     tournament.buildBra(players);

//     cout << "Initial Bracket:" << endl;
//     tournament.printBracket();

//     // Simulate recording results
//     cout << "\nRecording Results:" << endl;
//     tournament.recRes(1, "Alice");   // first match
//     tournament.recRes(2, "Charlie"); // second match
//     tournament.recRes(3, "Eve");     // third match

//     tournament.recRes(4, "Alice");   // semifinal
//     tournament.recRes(5, "Alice");   // final

//     cout << "\nUpdated Bracket:" << endl;
//     tournament.printBracket();

//     // Path to final for a player
//     string player = "Alice";
//     vector<int> path = tournament.pathtoFinal(player);
//     cout << "\nPath to final for " << player << ": ";
//     for (int id : path) {
//         cout << id << " ";
//     }
//     cout << endl;

//     // When two players would meet
//     auto [matchId, round] = tournament.wouldMeet("Bob", "Charlie");
//     if (matchId != -1) {
//         cout << "\nBob and Charlie would meet at match " << matchId 
//              << " in round " << round << endl;
//     } else {
//         cout << "\nBob and Charlie never meet." << endl;
//     }

//     return 0;

int main() {
    // Teams
    vector<string> players = {"Team A", "Team B"};

    // Create tournament
    BTree tournament;
    tournament.buildBra(players);

    cout << "=== FOOTBALL GAME (3 ROUNDS) ===\n" << endl;

    // Scores for each round
    vector<MatchScore> scores = {
        {3, 1}, // Round 1
        {0, 0}, // Round 2
        {4, 2}  // Round 3
    };

    int totalA = 0;
    int totalB = 0;

    for (int round = 0; round < scores.size(); ++round) {
        cout << "Round " << round + 1 << endl;
        cout << players[0] << " score: " << scores[round].scoreL << endl;
        cout << players[1] << " score: " << scores[round].scoreR << endl;

        totalA += scores[round].scoreL;
        totalB += scores[round].scoreR;

        // Determine round winner
        if (scores[round].scoreL > scores[round].scoreR) {
            cout << "Winner: " << players[0] << "\n" << endl;
        } else if (scores[round].scoreL < scores[round].scoreR) {
            cout << "Winner: " << players[1] << "\n" << endl;
        } else {
            cout << "Result: Draw\n" << endl;
        }
    }

    // Final result
    cout << "=== FINAL RESULT ===" << endl;
    cout << players[0] << " total goals: " << totalA << endl;
    cout << players[1] << " total goals: " << totalB << endl;

    // Overall winner
    if (totalA > totalB) {
        cout << "🏆 Overall Winner: " << players[0] << endl;
    } else if (totalB > totalA) {
        cout << "🏆 Overall Winner: " << players[1] << endl;
    } else {
        cout << "🏆 Overall Result: Draw" << endl;
    }

    return 0;
 }