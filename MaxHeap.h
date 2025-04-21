//
// Created by seany on 4/6/2025.
//

#ifndef PROJECT3_MAXHEAP_H
#define PROJECT3_MAXHEAP_H


#include <vector>
#include <string>
#include "Player.h"

using namespace std;

class MaxHeap {
private:
    vector<Player> heap;
    string stat;
    vector<string> allStats = {
            "pts", "ast", "reb", "net_rating",  "usg_pct", "ts_pct"
    };



    int parent(int i) const;
    int left(int i) const;
    int right(int i) const;

    void heapifyUp(int i);
    void heapifyDown(int i);
    double getStat(const Player& p) const;

public:
    MaxHeap(const string& stat);
    void insert(const Player& player);
    Player extractMax();
    void buildHeap(const vector<Player>& players);
    bool isEmpty() const;
    void printTopN(int n) const;
    void sortBy(const string& newStat);
    void rankByAllStats(int topN, bool uniqueSeasons);


};



#endif //PROJECT3_MAXHEAP_H
