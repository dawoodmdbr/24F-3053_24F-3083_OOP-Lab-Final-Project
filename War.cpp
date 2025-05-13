#include "Stronghold.h"

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

    cout << "⚔️ War has started between two kingdoms!\n";
    simulateRound();
}

void War::simulateRound() {
    if (!isActive || attacker == nullptr || defender == nullptr) return;

    cout << "💥 Simulating battle round...\n";
    duration++;

    // Calculate attack and defense power based on soldiers and morale
    int atkSoldiers = attacker->getMilitary().getSoldierCount();
    int defSoldiers = defender->getMilitary().getSoldierCount();

    double atkMorale = attacker->getMilitary().getMorale();
    double defMorale = defender->getMilitary().getMorale();

    int atkPower = atkSoldiers * atkMorale;
    int defPower = defSoldiers * defMorale;

    // Random casualties
    atkPower -= rand() % 10;
    defPower -= rand() % 10;

    // Update soldier counts after battle
    attacker->getMilitary().setSoldierCount(max(0, atkPower / (int)atkMorale));
    defender->getMilitary().setSoldierCount(max(0, defPower / (int)defMorale));

    // End war if either side is wiped out
    if (atkPower <= 0 || defPower <= 0) {
        end();
    } else {
        showStatus();
    }
}


void War::end() {
    isActive = false;
    cout << "🛑 War ended after " << duration << " rounds.\n";

    string winner = getWinner();
    if (winner == "Draw")
        cout << "🏳️ It ended in a draw.\n";
    else
        cout << "🏆 Winner: " << winner << "!\n";
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
        return "Defender";
    else if (defPower <= 0)
        return "Attacker";

    return "Undecided";
}

void War::showStatus() const {
    if (!attacker || !defender) return;

    cout << "Attacker Soldiers: " << attacker->getMilitary().getSoldierCount() << endl;
    cout << "Defender Soldiers: " << defender->getMilitary().getSoldierCount() << endl;
}
