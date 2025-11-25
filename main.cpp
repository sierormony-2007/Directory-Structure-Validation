#include <iostream>
#include <vector>
#include "code.hpp"

using namespace std;

int main() {
<<<<<<< HEAD
    vector<string> teams = { "Team A", "Team B","Team C", "Team D",
                            "Team E", "Team F", "Team G", "Team H"};
=======
    vector<string> teams = {"Team A", "Team B", "Team C", "Team D",
                            "Team E", "Team F", "Team G", "Team H"};//8 teams
>>>>>>> d958885a3c8fb529e703ca4e9c82fb01fbe91d27

    BTree tournament;
    tournament.buildBra(teams);
     cout << "=== FOOTBALL TOURNAMENT ===\n";

    // Record results
    tournament.recRes(1, "Team A");
    tournament.recRes(2, "Team D");
    tournament.recRes(3, "Team F");
    tournament.recRes(4, "Team H");
    tournament.recRes(5, "Team A");
    tournament.recRes(6, "Team H");
    tournament.recRes(7, "Team H"); // determine the winner

    
    tournament.printBracketByRound();

    Node* root = tournament.getRoot();
<<<<<<< HEAD
    cout << "\n=== FINAL RESULTS ===\n";
    cout << "\n Overall Winner: " << root->winner << "\n";
=======
    cout << "\nOverall Winner: " << root->winner << "\n";
>>>>>>> d958885a3c8fb529e703ca4e9c82fb01fbe91d27

    return 0;
}
