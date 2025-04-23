#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <set>
#include "Player.h"
#include "MaxHeap.h"
#include "PlayerMap.h"

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

    MaxHeap heap("pts");
    heap.buildHeap(players);


    PlayerMap playerData;
    playerData.loadFromCSV("../all_seasons.csv");



    //Making career averages heap
   set<string> playerNames;
    for(const Player& s : players){
        playerNames.insert(s.playerName);
    }

    vector<Player> averages;
    for (string name : playerNames) {
        averages.push_back(playerData.getCareerAverages(name)->getSelf());
    }
    MaxHeap careerHeap("pts");
    careerHeap.buildHeap(averages);



    while (true) {
        cout << "\nMenu:\n";
        cout << "1. View Top Seasons by Stat\n";
        cout << "2. Rank Best Seasons of All Time\n";
        cout << "3. View Top Careers by Stat\n";
        cout << "4. Rank Best Careers of All Time\n";
        cout << "5. View a Player's Career Averages\n";
        cout << "6. Compare Two Players\n";
        cout << "7. Find a Player's Best Season by Stat\n";
        cout << "8. Insert Season\n";
        cout << "9. Exit\n";
        cout << "Enter your choice: ";

        int choice;
        cin >> choice;
        cin.ignore();

        if (choice == 1) {
            string stat;
            int n;
            cout << "Enter stat (pts, ast, reb, net_rating, usg_pct, ts_pct): " << endl;
            cin >> stat;
            cout << "How many top seasons to show? "<< endl;
            cin >> n;

            heap.sortBy(stat);
            heap.printTopN(n);
        }

        else if (choice == 2) {
            int n;
            char unique;
            cout << "How many players to show? "<< endl;
            cin >> n;
            cout << "Show only best season per player? (y/n): "<< endl;
            cin >> unique;

            heap.rankByAllStats(n, unique == 'y' || unique == 'Y');
        }

        else if (choice == 3) {
            string stat;
            int n;
            cout << "Enter stat (pts, ast, reb, net_rating, usg_pct, ts_pct): "<< endl;
            cin >> stat;
            cout << "How many top careers to show? "<< endl;
            cin >> n;

            careerHeap.sortBy(stat);
            careerHeap.printTopN(n);
        }


        else if (choice == 4) {
            int n;
            cout << "How many players to show? "<< endl;
            cin >> n;

            careerHeap.rankByAllStats(n, true);
        }


        else if (choice == 5) {
            string name;
            cout << "Enter player name: "<< endl;
            getline(cin, name);

            Player* avg = playerData.getCareerAverages(name);
            if (avg) {
                avg->print();
                delete avg;
            } else {
                cout << "Player not found." << endl;
            }
        }

        else if (choice == 6) {
            string p1, p2;
            cout << "Enter first player name: "<< endl;
            cin.ignore();
            getline(cin, p1);
            cout << "Enter second player name: "<< endl;
            getline(cin, p2);
            playerData.compare(p1, p2);
        }

        else if (choice == 7) {
            string name, stat;
            cout << "Enter player name: "<< endl;
            getline(cin, name);
            cout << "Enter stat (pts, ast, reb, net_rating, usg_pct, ts_pct): "<< endl;
            cin >> stat;
            playerData.findBestSeasonByStat(name, stat);
        }

        else if (choice == 8) {
            string name;
            int season;
            double pts, ast, reb, net, usg, ts;

            cout << "Enter player name: ";
            cin.ignore();
            getline(cin, name);

            cout << "Enter season (e.g., 2018): ";
            cin >> season;
            cout << "Enter points per game: ";
            cin >> pts;
            cout << "Enter assists per game: ";
            cin >> ast;
            cout << "Enter rebounds per game: ";
            cin >> reb;
            cout << "Enter net rating: ";
            cin >> net;
            cout << "Enter usage percentage (e.g., 0.31): ";
            cin >> usg;
            cout << "Enter true shooting percentage (e.g., 0.59): ";
            cin >> ts;

            Player newPlayer(name, season, pts, ast, reb, net,
                             0.0, 0.0, usg, ts, 0.0); // dummy values for oreb/dreb/ast%

            // Insert into main season heap
            heap.insert(newPlayer);

            // Update player map
            playerData.insertSeason(newPlayer);

            // Rebuild career heap
            playerNames.insert(name);

            vector<Player> updatedCareerAverages;
            for (const string& pname : playerNames) {
                Player* avg = playerData.getCareerAverages(pname);
                if (avg) {
                    updatedCareerAverages.push_back(avg->getSelf());
                    delete avg;
                }
            }

            careerHeap = MaxHeap("pts");
            careerHeap.buildHeap(updatedCareerAverages);

            cout << "Season inserted and career averages updated!\n";
        }


        else if (choice == 9) {
            cout << "Goodbye!" << endl;
            break;
        }

        else {
            cout << "Invalid choice. Try again." << endl;
        }
    }


    return 0;


}
