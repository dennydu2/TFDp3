//
// Created by seany on 4/20/2025.
//

#ifndef PROJECT3_PLAYERMAP_H
#define PROJECT3_PLAYERMAP_H


#ifndef PLAYERMAP_H
#define PLAYERMAP_H

#include "Player.h"
#include <unordered_map>
#include <vector>
#include <string>

using namespace std;

class PlayerMap {
private:
    unordered_map<string, vector<Player>> data;

public:
    void loadFromCSV(const string& filename);
    void getPlayerSeasons(const string& name);
    unordered_map<string, vector<Player>>& getAll();
    Player* getCareerAverages(const string &name);
    void compare(const string player1, const string player2);
    void findBestSeasonByStat(const string& playerName, const string& statName);

};

#endif

#endif //PROJECT3_PLAYERMAP_H
