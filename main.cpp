#include "Stronghold.h"
#include <iostream>
#include <limits>
#include <cstdlib>
#include <ctime>

using namespace std;


void militaryMenu(Kingdom& kingdom) {
    int choice;
    cout << "\nMilitary Menu\n";
    cout << "1. Recruit Soldiers\n";
    cout << "2. View Soldier Count\n";
    cout << "3. Train Soldiers\n";
    cout << "4. View Training Status\n";
    cout << "5. View Military Strength\n";
    cout << "0. Back to Main Menu\n";
    cout << "Choice: ";
    cin >> choice;

    switch (choice) {
        case 1: {
            int soldiers;
            cout << "Enter number of soldiers to recruit: ";
            cin >> soldiers;
            if (soldiers > 0)
                kingdom.getMilitary().recruitSoldiers(soldiers);
            else
                cout << "Invalid number.\n";
            break;
        }
        case 2:
            cout << "Current soldiers: " << kingdom.getMilitary().getSoldierCount() << endl;
            break;
        case 3:
            int trainCount;
            cout << "Enter number of soldiers to train: ";
            cin >> trainCount;
            if (trainCount > 0)
                kingdom.getMilitary().trainSoldiers(trainCount);
            else
                cout << "Invalid number.\n";
            break;
        case 4:
            cout << "Training status: " << kingdom.getMilitary().getMorale() << endl;
            break;
        case 5:
            cout << "Military strength: " << kingdom.getMilitary().getSoldierCount() * kingdom.getMilitary().getMorale() << endl;
            break;
        case 0: return;
        default:
            cout << "Invalid choice.\n";
    }
}

void economyMenu(Kingdom& kingdom) {
    int choice;
    cout << "\nEconomy Menu\n";
    cout << "1. Adjust Tax Rate\n";
    cout << "2. View Tax Rate\n";
    cout << "3. View Corruption Level\n";
    cout << "4. View Inflation Rate\n";
    cout << "0. Back to Main Menu\n";
    cout << "Choice: ";
    cin >> choice;

    switch (choice) {
        case 1: {
            double rate;
            cout << "Enter new tax rate (0.0 - 1.0): ";
            cin >> rate;
            if (rate >= 0 && rate <= 1.0)
                kingdom.getEconomy().adjustTaxRate(rate);
            else
                cout << "Invalid rate.\n";
            break;
        }
        case 2:
            cout << "Current tax rate: " << kingdom.getEconomy().getTaxRate() << endl;
            break;
        case 3:
            cout << "Current corruption level: " << kingdom.getCorruption().getCorruptionLevel() << endl;
            break;
        case 4:
            cout << "Current inflation rate: " << kingdom.getEconomy().getInflation() << endl;
            break;
        case 0: return;
        default:
            cout << "Invalid choice.\n";
    }
}

void resourceMenu(Kingdom& kingdom) {
    int choice;
    cout << "\nResource Menu\n";
    cout << "1. Gather Resources\n";
    cout << "2. View Resource Stockpile\n";
    cout << "0. Back to Main Menu\n";
    cout << "Choice: ";
    cin >> choice;

    switch (choice) {
        case 1: {
            int resChoice, amount;
            cout << "Select Resource to Gather:\n";
            cout << "0. Food  1. Wood  2. Stone  3. Iron  4. Gold\n";
            cin >> resChoice;
            cout << "Enter amount to gather: ";
            cin >> amount;
            if (resChoice >= 0 && resChoice < RESOURCE_TYPE_COUNT && amount > 0)
                kingdom.getResourceManager().gather(static_cast<ResourceType>(resChoice), amount);
            else
                cout << "Invalid input.\n";
            break;
        }
        case 2: {
            const char* resourceNames[] = { "Food", "Wood", "Stone", "Iron", "Gold" };
            cout << "Current Resource Stockpile:\n";
            for (int i = 0; i < RESOURCE_TYPE_COUNT; ++i) {
                cout << resourceNames[i] << " - Amount: "
                     << kingdom.getResourceManager().get(static_cast<ResourceType>(i)) << endl;
            }
            break;
        }
        case 0: return;
        default:
            cout << "Invalid choice.\n";
    }
}

void populationMenu(Kingdom& kingdom) {
    const char* classNames[] = { "Peasants", "Merchants", "Nobles", "Soldiers", "Civilians" };
    cout << "\nPopulation Status\n";
    for (int i = 0; i < SOCIAL_CLASS_COUNT; ++i) {
        cout << classNames[i] << " - Count: " << kingdom.getPopulation().getCount(static_cast<SocialClass>(i))
             << ", Happiness: " << kingdom.getPopulation().getHappiness(static_cast<SocialClass>(i)) << endl;
    }
}

void leadershipMenu(Kingdom& kingdom) {
    cout << "\nLeadership Overview\n";
    cout << "Leader Name: " << kingdom.getLeadership().getLeaderName() << endl;
    cout << "Leadership Level: " << kingdom.getLeadership().getLeadershipLevel() << endl;
}

// Events

void randomEvent(Kingdom& kingdom) {
    int eventRoll = rand() % 5;

    switch (eventRoll) {
        case 0:
            cout << "\nA bountiful harvest increases food by 200.\n";
            kingdom.getResourceManager().gather(FOOD, 200);
            break;
        case 1:
            cout << "\nA fire destroys 100 wood.\n";
            kingdom.getResourceManager().gather(WOOD, -100);
            break;
        case 2:
            cout << "\nA rival kingdom attacks. You lose 20 soldiers.\n";
            kingdom.getMilitary().recruitSoldiers(-20);
            break;
        case 3:
            cout << "\nThe economy booms. You gain 300 gold.\n";
            kingdom.getResourceManager().gather(GOLD, 300);
            break;
        case 4:
            cout << "\nUnrest spreads. Happiness of peasants drops.\n";
            kingdom.getPopulation().adjustHappiness(PEASANT, -10);
            break;
    }
}

// Main Menu

void displayMainMenu() {
    cout << "\nStronghold Management\n";
    cout << "1. Military\n";
    cout << "2. Economy\n";
    cout << "3. Resources\n";
    cout << "4. Population\n";
    cout << "5. Leadership\n";
    cout << "6. Next Turn\n";
    cout << "0. Exit Game\n";
    cout << "Select a category: ";
}

int main() {
    srand(time(0)); // For random events

    Kingdom myKingdom;
    int mainChoice;
    int turn = 1;

    cout << "\nWelcome to Stronghold Management\n";

    while (true) {
        cout << "\nTurn " << turn << "\n";
        displayMainMenu();
        cin >> mainChoice;

        switch (mainChoice) {
            case 1: militaryMenu(myKingdom); break;
            case 2: economyMenu(myKingdom); break;
            case 3: resourceMenu(myKingdom); break;
            case 4: populationMenu(myKingdom); break;
            case 5: leadershipMenu(myKingdom); break;
            case 6:
                cout << "\nProcessing Turn " << turn << "...\n";
                myKingdom.update();
                myKingdom.handleEvents();
                randomEvent(myKingdom);
                myKingdom.checkFinancialHealth();
                ++turn;
                break;
            case 0:
                cout << "\nExiting game. Thank you for playing.\n";
                return 0;
            default:
                cout << "Invalid choice.\n";
        }

        system("pause");
        system("cls"); // Use "clear" for Linux/Mac
    }

    return 0;
}
