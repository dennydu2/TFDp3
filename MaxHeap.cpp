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
    if (heap.empty()) {
        throw runtime_error("Heap is empty!");
    }

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
    int count = min(n, (int)heap.size());
    for (int i = 0; i < count; i++) {
        cout << i + 1 << ". ";
        heap[i].print();
    }
}
