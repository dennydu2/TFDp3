//
// Created by seany on 4/6/2025.
//

#ifndef PROJECT3_PLAYER_H
#define PROJECT3_PLAYER_H


#include <string>
using namespace std;
class Player {
public:
    string playerName;
    int season;
    double pts, ast, reb;
    double netRating, orebPct, drebPct, usgPct, tsPct, astPct;
    int statRanks[6]; // index for each stat's rank
    int totalRank = 0; // sum of statRanks

    Player(string name, int season, double pts, double ast, double reb,
           double netRating, double orebPct, double drebPct,
           double usgPct, double tsPct, double astPct);

    void print() const;
    Player getSelf();

};


#endif //PROJECT3_PLAYER_H
