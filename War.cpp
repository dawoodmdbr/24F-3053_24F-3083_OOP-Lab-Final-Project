#include "Stronghold.h"
#include <iostream>
#include <cstdlib> 
#include <ctime>   

using namespace std;


War::War() {
    attacker = nullptr;
    defender = nullptr;
    isActive = false;
    duration = 0;
}


War::War(Kingdom* atk, Kingdom* def) {
    attacker = atk;
    defender = def;
    isActive = true;
    duration = 0;
}


void War::start() {
    if (!isActive || attacker == nullptr || defender == nullptr) return;

    cout << "War has started between " << attacker->getName() << " and " << defender->getName() << "!\n";
    simulateRound();
}


void War::simulateRound() {
    if (!isActive || attacker == nullptr || defender == nullptr) return;

    cout << "Simulating battle round...\n";
    duration++;

    
    int atkSoldiers = attacker->getMilitary().getSoldierCount();
    int defSoldiers = defender->getMilitary().getSoldierCount();

    double atkMorale = attacker->getMilitary().getMorale();
    double defMorale = defender->getMilitary().getMorale();

    int atkPower = atkSoldiers * atkMorale;
    int defPower = defSoldiers * defMorale;

    
    atkPower -= rand() % 10;
    defPower -= rand() % 10;

    
    attacker->getMilitary().setSoldierCount(max(0, atkPower / (int)atkMorale));
    defender->getMilitary().setSoldierCount(max(0, defPower / (int)defMorale));

    
    if (atkPower <= 0 || defPower <= 0) {
        end();
    } else {
        showStatus();
    }
}


void War::end() {
    isActive = false;
    cout << "War ended after " << duration << " rounds.\n";

    string winner = getWinner();
    if (winner == "Draw")
        cout << "The war ended in a draw.\n";
    else
        cout << "Winner: " << winner << "!\n";
}


bool War::getStatus() const {
    return isActive;
}


string War::getWinner() const {
    if (!attacker || !defender) return "Unknown";

    int atkSoldiers = attacker->getMilitary().getSoldierCount();
    int defSoldiers = defender->getMilitary().getSoldierCount();

    double atkMorale = attacker->getMilitary().getMorale();
    double defMorale = defender->getMilitary().getMorale();

    int atkPower = atkSoldiers * atkMorale;
    int defPower = defSoldiers * defMorale;

    if (atkPower <= 0 && defPower <= 0)
        return "Draw";
    else if (atkPower <= 0)
        return defender->getName();
    else if (defPower <= 0)
        return attacker->getName();

    return "Undecided";
}


void War::showStatus() const {
    if (!attacker || !defender) return;

    cout << "Attacker (" << attacker->getName() << ") Soldiers: " << attacker->getMilitary().getSoldierCount() << endl;
    cout << "Defender (" << defender->getName() << ") Soldiers: " << defender->getMilitary().getSoldierCount() << endl;
}
