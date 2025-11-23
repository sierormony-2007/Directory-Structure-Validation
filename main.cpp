#include <iostream>
#include <vector>
#include <string>
#include "code.hpp"

using namespace std;

int main() {
    // 8 teams
    vector<string> teams = {"Team A", "Team B", "Team C", "Team D",
                            "Team E", "Team F", "Team G", "Team H"};

    BTree tournament;
    tournament.buildBracket(teams);

    cout << "=== FOOTBALL TOURNAMENT ===\n\n";

    // Round 1 results
    cout << "=== Round 1 ===\n";
    tournament.recordResult(1, "Team A"); // Match 1: Team A vs Team B
    tournament.recordResult(2, "Team D"); // Match 2: Team C vs Team D
    tournament.recordResult(3, "Team F"); // Match 3: Team E vs Team F
    tournament.recordResult(4, "Team H"); // Match 4: Team G vs Team H
    tournament.printBracket();

    // Round 2 results
    cout << "\n=== Round 2 ===\n";
    tournament.recordResult(5, "Team A"); // Winner of Match 1 vs Winner of Match 2
    tournament.recordResult(6, "Team F"); // Winner of Match 3 vs Winner of Match 4
    tournament.printBracket();

    // Round 3 results (Final)
    cout << "\n=== Round 3 (Final) ===\n";
    tournament.recordResult(7, "Team A"); // Winner of Match 5 vs Winner of Match 6
    tournament.printBracket();

    // Determine total goals (optional, if you want to sum them)
    int goalsTeamA = 3 + 0 + 4; // example scores
    int goalsTeamF = 1 + 0 + 2;

    cout << "\n=== FINAL RESULT ===\n";
    cout << "Team A total goals: " << goalsTeamA << "\n";
    cout << "Team F total goals: " << goalsTeamF << "\n";
    cout << "🏆 Overall Winner: Team A\n";

    return 0;
}
