//
// Created by seany on 4/20/2025.
//

#include "MaxHeap.h"

#include <iostream>

using namespace std;

MaxHeap::MaxHeap(const string& stat) {
    this->stat = stat;
}

int MaxHeap::parent(int i) const {
    return (i - 1) / 2;
}

int MaxHeap::left(int i) const {
    return 2 * i + 1;
}

int MaxHeap::right(int i) const {
    return 2 * i + 2;
}

double MaxHeap::getStat(const Player& p) const {
    if (stat == "pts") {
        return p.pts;
    }
    if (stat == "ast") {
        return p.ast;
    }
    if (stat == "reb") {
        return p.reb;
    }
    if (stat == "net_rating") {
        return p.netRating;
    }
    if (stat == "oreb_pct") {
        return p.orebPct;
    }
    if (stat == "dreb_pct") {
        return p.drebPct;
    }
    if (stat == "usg_pct") {
        return p.usgPct;
    }
    if (stat == "ts_pct") {
        return p.tsPct;
    }
    if (stat == "ast_pct") {
        return p.astPct;
    }
    if (stat == "totalRank") {
        return -p.totalRank;  // Lower rank = better
    }
    return 0;
}

void MaxHeap::heapifyUp(int i) {
    while (i > 0 && getStat(heap[i]) > getStat(heap[parent(i)])) {
        swap(heap[i], heap[parent(i)]);
        i = parent(i);
    }
}

void MaxHeap::heapifyDown(int i) {
    int size = heap.size();
    while (true) {
        int l = left(i);
        int r = right(i);
        int largest = i;

        if (l < size && getStat(heap[l]) > getStat(heap[largest])) {
            largest = l;
        }
        if (r < size && getStat(heap[r]) > getStat(heap[largest])) {
            largest = r;
        }

        if (largest == i) {
            break;
        }

        swap(heap[i], heap[largest]);
        i = largest;
    }
}

void MaxHeap::insert(const Player& player) {
    heap.push_back(player);
    heapifyUp(heap.size() - 1);
}

Player MaxHeap::extractMax() {

    Player max = heap[0];
    heap[0] = heap.back();
    heap.pop_back();
    heapifyDown(0);
    return max;
}

void MaxHeap::buildHeap(const vector<Player>& players) {
    heap = players;
    for (int i = heap.size() / 2 - 1; i >= 0; i--) {
        heapifyDown(i);
    }
}

bool MaxHeap::isEmpty() const {
    return heap.empty();
}

void MaxHeap::printTopN(int n) const {
    vector<Player> temp = heap;
    MaxHeap tempHeap(stat);
    tempHeap.buildHeap(temp);

    for (int i = 0; i < n && !tempHeap.isEmpty(); i++) {
        Player p = tempHeap.extractMax();
        cout << i + 1 << ". ";
        p.print();
    }
}

void MaxHeap::sortBy(const string& newStat) {
    stat = newStat;
    for (int i = heap.size() / 2 - 1; i >= 0; i--) {
        heapifyDown(i);
    }
}

void MaxHeap::rankByAllStats(int topN, bool uniqueSeasons) {
    // Backup of original heap
    vector<Player> original = heap;

    // Initialize totalRank and statRanks
    for (int i = 0; i < original.size(); i++) {
        original[i].totalRank = 0;
        for (int j = 0; j < 6; j++) {
            original[i].statRanks[j] = 0;
        }
    }

    for (int s = 0; s < allStats.size(); s++) {
        string currentStat = allStats[s];

        // Create a heap sorted by current stat
        MaxHeap tempHeap(currentStat);
        tempHeap.buildHeap(original);

        // record ranks in a temporary list of indexes
        vector<Player> rankedPlayers;

        while (!tempHeap.isEmpty()) {
            Player p = tempHeap.extractMax();
            rankedPlayers.push_back(p);
        }

        // Assign ranks to players by searching in original vector
        for (int rank = 0; rank < rankedPlayers.size(); rank++) {
            for (int i = 0; i < original.size(); i++) {
                Player& o = original[i];
                Player& r = rankedPlayers[rank];
                //Had to use abs value because just checking equality was off
                if (o.playerName == r.playerName &&
                    o.season == r.season &&
                    abs(o.pts - r.pts) < 0.001 &&
                    abs(o.ast - r.ast) < 0.001 &&
                    abs(o.reb - r.reb) < 0.001) {
                    int weight = 2;
                    //Weight points, netrating and efficiency as more
                    if (currentStat == "pts" || currentStat == "ts_pct" || currentStat == "net_rating") {
                        weight = 1;
                    }

                        original[i].statRanks[s] = rank + 1;
                        original[i].totalRank += (rank + 1) * weight;
                        break;
                }
            }
        }
    }

    // Now rebuild heap based on totalRank
    heap = original;
    stat = "totalRank";
    for (int i = heap.size() / 2 - 1; i >= 0; i--) {
        heapifyDown(i);
    }

    // Output topN players
    if(!uniqueSeasons) {
        cout << "Top " << topN << " Players by Combined Stat Rankings:" << endl;
        for (int i = 0; i < topN && i < heap.size(); i++) {
            cout << i + 1 << ". " << heap[i].playerName
                 << " (Total Rank Score: " << heap[i].totalRank << ")" << endl;
            heap[i].print();
        }
    }else{
        cout << "Top " << topN << " Players by Combined Stat Rankings:" << endl;

        int printed = 0;
        for (int i = 0; i < heap.size() && printed < topN; i++) {
            bool alreadyPrinted = false;

            // Check if this player's name has already been printed
            for (int j = 0; j < i; j++) {
                if (heap[i].playerName == heap[j].playerName) {
                    alreadyPrinted = true;
                    break;
                }
            }

            if (!alreadyPrinted) {
                cout << printed + 1 << ". " << heap[i].playerName
                     << " (Total Rank Score: " << heap[i].totalRank << ")" << endl;
                heap[i].print();
                printed++;
            }
        }
    }
}


