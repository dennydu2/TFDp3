#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include "Player.h"
#include "MaxHeap.h"

using namespace std;

int main() {
    vector<Player> players;
    ifstream file("../all_seasons.csv");

    if (!file.is_open()) {
        cerr << "Failed to open the file!" << endl;
        return 1;
    }

    string line;
    getline(file, line); // skip header

    while (getline(file, line)) {
        stringstream ss(line);
        string token;
        vector<string> row;

        while (getline(ss, token, ',')) {
            row.push_back(token);
        }

        if (stoi(row[21]) == 0) {
            //Skips if a singular game and not a season
            continue;
        }

        string playerName = row[1];
        int season = stoi(row[21]);
        double pts = stod(row[12]);
        double reb = stod(row[13]);
        double ast = stod(row[14]);
        double netRating = stod(row[15]);
        double orebPct = stod(row[16]);
        double drebPct = stod(row[17]);
        double usgPct = stod(row[18]);
        double tsPct = stod(row[19]);
        double astPct = stod(row[20]);

        Player p(playerName, season, pts, ast, reb,
                 netRating, orebPct, drebPct, usgPct, tsPct, astPct);
        players.push_back(p);
    }

    file.close();

    MaxHeap points("pts");
    points.buildHeap(players);

    cout << "Top 5 Players by Points:" << endl;
    points.printTopN(5);

    MaxHeap assists("ast");
    assists.buildHeap(players);

    cout << "Top 5 Players by Assists:" << endl;
    assists.printTopN(5);

    return 0;
}
