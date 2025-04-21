//
// Created by seany on 4/20/2025.
//

#include "Player.h"
#include <iostream>

using namespace std;

Player::Player(string name, int season, double pts, double ast, double reb,
               double netRating, double orebPct, double drebPct,
               double usgPct, double tsPct, double astPct)
        : playerName(name), season(season), pts(pts), ast(ast), reb(reb),
          netRating(netRating), orebPct(orebPct), drebPct(drebPct),
          usgPct(usgPct), tsPct(tsPct), astPct(astPct) {}

void Player::print() const {
    cout << "Name: " << playerName << ", Season: " << season
         << ", PTS: " << pts << ", AST: " << ast << ", REB: " << reb
         << ", NET: " << netRating << ", OREB%: " << orebPct
         << ", DREB%: " << drebPct << ", USG%: " << usgPct
         << ", TS%: " << tsPct << ", AST%: " << astPct << endl;
}

Player Player::getSelf() {
    return *this;
}