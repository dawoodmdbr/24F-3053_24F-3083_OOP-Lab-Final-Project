#include"Stronghold.h"
#include<iostream>

Diplomacy::Diplomacy(){
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
        kingdomNames[kingdomCount] = kingdom.getName();
        kingdomCount++;
    } else {
        cout << "Maximum number of kingdoms reached." << endl;
    }
}

void Diplomacy::proposeAlliance(Kingdom& kingdom1, Kingdom& kingdom2) {
    if (kingdomCount < 10) {
        alliances[kingdom1.getId()][kingdom2.getId()] = true;
    } else {
        cout << "Maximum number of kingdoms reached." << endl;
    }
}

void Diplomacy::breakAlliance(Kingdom& kingdom1, Kingdom& kingdom2) {
    if (kingdomCount < 10) {
        alliances[kingdom1.getId()][kingdom2.getId()] = false;
    } else {
        cout << "Maximum number of kingdoms reached." << endl;
    }
}

bool Diplomacy::isAllied(Kingdom& kingdom1, Kingdom& kingdom2) const {
    return alliances[kingdom1.getId()][kingdom2.getId()];
}

void Diplomacy::showAlliances() const {
    cout << "Alliances:" << endl;
    for (int i = 0; i < kingdomCount; i++) {
        for (int j = 0; j < kingdomCount; j++) {
            if (alliances[i][j]) {
                cout << kingdomNames[i] << " is allied with " << kingdomNames[j] << endl;
            }
        }
    }
}

void Diplomacy::showAllianceHistory() const {
    cout << "Alliance History:" << endl;
    for (int i = 0; i < historyCount; i++) {
        cout << allianceHistory[i] << endl;
    }
}