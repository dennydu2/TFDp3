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

void PlayerMap::compare(const string player1, const string player2) {
    Player* p1 = getCareerAverages(player1);
    Player* p2 = getCareerAverages(player2);

    if (!p1 || !p2) {
        cout << "Could not find data for one or both players." << endl;
        return;
    }

    cout << "\nCareer Averages Comparison:\n";

    cout << "\n" << player1 << ":\n";
    p1->print();

    cout << "\n" << player2 << ":\n";
    p2->print();

    cout << "\nStat differences:\n";

    if (p1->pts > p2->pts) {
        cout << player1 << " averaged " << (p1->pts - p2->pts) << " more points than " << player2 << "." << endl;
    } else if (p2->pts > p1->pts) {
        cout << player2 << " averaged " << (p2->pts - p1->pts) << " more points than " << player1 << "." << endl;
    } else {
        cout << "Both players averaged the same points." << endl;
    }

    if (p1->ast > p2->ast) {
        cout << player1 << " averaged " << (p1->ast - p2->ast) << " more assists than " << player2 << "." << endl;
    } else if (p2->ast > p1->ast) {
        cout << player2 << " averaged " << (p2->ast - p1->ast) << " more assists than " << player1 << "." << endl;
    } else {
        cout << "Both players averaged the same assists." << endl;
    }

    if (p1->reb > p2->reb) {
        cout << player1 << " averaged " << (p1->reb - p2->reb) << " more rebounds than " << player2 << "." << endl;
    } else if (p2->reb > p1->reb) {
        cout << player2 << " averaged " << (p2->reb - p1->reb) << " more rebounds than " << player1 << "." << endl;
    } else {
        cout << "Both players averaged the same rebounds." << endl;
    }

    if (p1->netRating > p2->netRating) {
        cout << player1 << " had " << (p1->netRating - p2->netRating) << " higher net rating than " << player2 << "." << endl;
    } else if (p2->netRating > p1->netRating) {
        cout << player2 << " had " << (p2->netRating - p1->netRating) << " higher net rating than " << player1 << "." << endl;
    } else {
        cout << "Both players had the same net rating." << endl;
    }

    if (p1->usgPct > p2->usgPct) {
        cout << player1 << " had " << (p1->usgPct - p2->usgPct) << " higher USG% than " << player2 << "." << endl;
    } else if (p2->usgPct > p1->usgPct) {
        cout << player2 << " had " << (p2->usgPct - p1->usgPct) << " higher USG% than " << player1 << "." << endl;
    } else {
        cout << "Both players had the same USG%." << endl;
    }

    if (p1->tsPct > p2->tsPct) {
        cout << player1 << " had " << (p1->tsPct - p2->tsPct) << " higher TS% than " << player2 << "." << endl;
    } else if (p2->tsPct > p1->tsPct) {
        cout << player2 << " had " << (p2->tsPct - p1->tsPct) << " higher TS% than " << player1 << "." << endl;
    } else {
        cout << "Both players had the same TS%." << endl;
    }

    delete p1;
    delete p2;
}

void PlayerMap::findBestSeasonByStat(const string& playerName, const string& statName) {
    if (data.find(playerName) == data.end()) {
        cout << "Player not found." << endl;
        return;
    }

    const vector<Player>& seasons = data[playerName];
    if (seasons.empty()) {
        cout << "No seasons found for " << playerName << "." << endl;
        return;
    }

    double bestValue = -1e9;
    int bestSeason = -1;

    for (const Player& p : seasons) {
        double value = 0;

        if (statName == "pts") value = p.pts;
        else if (statName == "ast") value = p.ast;
        else if (statName == "reb") value = p.reb;
        else if (statName == "net_rating") value = p.netRating;
        else if (statName == "oreb_pct") value = p.orebPct;
        else if (statName == "dreb_pct") value = p.drebPct;
        else if (statName == "usg_pct") value = p.usgPct;
        else if (statName == "ts_pct") value = p.tsPct;
        else if (statName == "ast_pct") value = p.astPct;
        else {
            cout << "Invalid stat name: " << statName << endl;
            return;
        }

        if (value > bestValue) {
            bestValue = value;
            bestSeason = p.season;
        }
    }

    if (bestSeason != -1) {
        cout << playerName << "'s best " << statName << " season was "
             << bestSeason << ": " << fixed << bestValue << endl;
    } else {
        cout << "Could not determine best season for " << playerName << " in stat " << statName << "." << endl;
    }
}


