#include "Stronghold.h"
#include <iostream>
#include <string>

using namespace std;


Diplomacy::Diplomacy() {
    kingdomCount = 0;
    historyCount = 0;
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            alliances[i][j] = false;
        }
    }
}


void Diplomacy::registerKingdom(Kingdom& kingdom) {
    if (kingdomCount < 10) {
        kingdomNames[kingdomCount++] = kingdom.getName();
        cout << "Kingdom " << kingdom.getName() << " registered successfully.\n";
    } else {
        cout << "Cannot register more kingdoms, limit reached.\n";
    }
}


void Diplomacy::proposeAlliance(Kingdom& kingdom1, Kingdom& kingdom2) {
    int index1 = -1, index2 = -1;
    for (int i = 0; i < kingdomCount; i++) {
        if (kingdomNames[i] == kingdom1.getName()) index1 = i;
        if (kingdomNames[i] == kingdom2.getName()) index2 = i;
    }

    if (index1 != -1 && index2 != -1) {
        cout << "Alliance proposed between " << kingdom1.getName() << " and " << kingdom2.getName() << ".\n";
    } else {
        cout << "One or both kingdoms not found.\n";
    }
}


void Diplomacy::acceptAlliance(Kingdom& kingdom1, Kingdom& kingdom2) {
    int index1 = -1, index2 = -1;
    for (int i = 0; i < kingdomCount; i++) {
        if (kingdomNames[i] == kingdom1.getName()) index1 = i;
        if (kingdomNames[i] == kingdom2.getName()) index2 = i;
    }

    if (index1 != -1 && index2 != -1) {
        alliances[index1][index2] = true;
        alliances[index2][index1] = true;
        allianceHistory[historyCount++] = kingdom1.getName() + " and " + kingdom2.getName() + " formed an alliance.";
        cout << "Alliance accepted between " << kingdom1.getName() << " and " << kingdom2.getName() << ".\n";
    } else {
        cout << "One or both kingdoms not found.\n";
    }
}


void Diplomacy::breakAlliance(Kingdom& kingdom1, Kingdom& kingdom2) {
    int index1 = -1, index2 = -1;
    for (int i = 0; i < kingdomCount; i++) {
        if (kingdomNames[i] == kingdom1.getName()) index1 = i;
        if (kingdomNames[i] == kingdom2.getName()) index2 = i;
    }

    if (index1 != -1 && index2 != -1 && alliances[index1][index2]) {
        alliances[index1][index2] = false;
        alliances[index2][index1] = false;
        allianceHistory[historyCount++] = kingdom1.getName() + " and " + kingdom2.getName() + " broke their alliance.";
        cout << "Alliance broken between " << kingdom1.getName() << " and " << kingdom2.getName() << ".\n";
    } else {
        cout << "No alliance exists between " << kingdom1.getName() << " and " << kingdom2.getName() << ".\n";
    }
}


bool Diplomacy::isAllied(Kingdom& kingdom1, Kingdom& kingdom2) const {
    int index1 = -1, index2 = -1;
    for (int i = 0; i < kingdomCount; i++) {
        if (kingdomNames[i] == kingdom1.getName()) index1 = i;
        if (kingdomNames[i] == kingdom2.getName()) index2 = i;
    }

    if (index1 != -1 && index2 != -1) {
        return alliances[index1][index2];
    }

    return false;
}


void Diplomacy::showAlliances() const {
    cout << "\n=== Current Alliances ===\n";
    for (int i = 0; i < kingdomCount; i++) {
        for (int j = i + 1; j < kingdomCount; j++) {
            if (alliances[i][j]) {
                cout << kingdomNames[i] << " and " << kingdomNames[j] << " are allied.\n";
            }
        }
    }
}


void Diplomacy::showAllianceHistory() const {
    cout << "\n=== Alliance History ===\n";
    for (int i = 0; i < historyCount; i++) {
        cout << allianceHistory[i] << endl;
    }
}