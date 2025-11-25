#include <iostream>
#include <vector>
#include "code.hpp"

using namespace std;

int main() {
    vector<string> teams = {"Team A", "Team B", "Team C", "Team D",
                            "Team E", "Team F", "Team G", "Team H"};//8 teams

    BTree tournament;
    tournament.buildBra(teams);

    // Record results
    tournament.recRes(1, "Team A");
    tournament.recRes(2, "Team D");
    tournament.recRes(3, "Team F");
    tournament.recRes(4, "Team H");
    tournament.recRes(5, "Team A");
    tournament.recRes(6, "Team H");
    tournament.recRes(7, "Team H"); // determine the winner

      cout << "=== FOOTBALL TOURNAMENT ===\n";
    tournament.printBracketByRound();

    Node* root = tournament.getRoot();
    cout << "\nOverall Winner: " << root->winner << "\n";

    return 0;
}
