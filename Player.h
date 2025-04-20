//
// Created by seany on 4/20/2025.
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

    Player(string name, int season, double pts, double ast, double reb,
           double netRating, double orebPct, double drebPct,
           double usgPct, double tsPct, double astPct);

    void print() const;
};


#endif //PROJECT3_PLAYER_H
