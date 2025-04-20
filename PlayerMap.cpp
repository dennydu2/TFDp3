//
// Created by seany on 4/20/2025.
//

#include "PlayerMap.h"

#include "PlayerMap.h"
#include <fstream>
#include <sstream>
#include <iostream>

void PlayerMap::loadFromCSV(const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Failed to open file: " << filename << endl;
        return;
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

        if (row.size() < 22 || stoi(row[21]) == 0) {
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

        data[playerName].push_back(p);
    }

    file.close();
}

void PlayerMap::getPlayerSeasons(const string& name) {
    //If found data print out each season.
    if (data.find(name) != data.end()) {
        for (const Player &s: data[name]) {
            s.print();
        }
    }else{
        cout << "No statistics found." << endl;
    }
}

Player* PlayerMap::getCareerAverages(const string& name){
    if (data.find(name) != data.end()) {
        int numSeasons = 0;
        double totPts = 0.0;
        double totAsts = 0.0;
        double totRebs = 0.0;
        double totNetRating = 0.0;
        double totOrebPct = 0.0;
        double totDrebPct = 0.0;
        double totUsgPct = 0.0;
        double totTsPct = 0.0;
        double totAstPct = 0.0;

        for(const Player&s : data[name]){
            totPts += s.pts;
            totAsts += s.ast;
            totRebs += s.reb;
            totNetRating += s.netRating;
            totOrebPct += s.orebPct;
            totDrebPct += s.drebPct;
            totUsgPct += s.usgPct;
            totTsPct += s.tsPct;
            totAstPct += s.astPct;

            numSeasons++;
        }
        if(numSeasons == 0){
            return nullptr;
        }

        Player* career = new Player(
                name,
                numSeasons,
                totPts / numSeasons,
                totAsts / numSeasons,
                totRebs / numSeasons,
                totNetRating / numSeasons,
                totOrebPct / numSeasons,
                totDrebPct / numSeasons,
                totUsgPct / numSeasons,
                totTsPct / numSeasons,
                totAstPct / numSeasons
        );

        return career;

    }else{
        return nullptr;
    }
}




unordered_map<string, vector<Player>>& PlayerMap::getAll() {
    return data;
}
