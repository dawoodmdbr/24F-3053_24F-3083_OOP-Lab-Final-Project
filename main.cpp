#include "Stronghold.h"
#include "Population.cpp"
#include "Leadership.cpp"
#include "Bank.cpp"
#include "Military.cpp"
#include "ResourceManager.cpp"
#include "EventManager.cpp"
#include "Corruption.cpp"
#include "Event.cpp"
#include "Kingdom.cpp"
#include <iostream>

using namespace std;

void displayMenu() {
    cout << "\n--- Stronghold: Kingdom Management ---\n";
    cout << "1. Gather Resources\n";
    cout << "2. Recruit Soldiers\n";
    cout << "3. Adjust Tax Rate\n";
    cout << "4. View Population Status\n";
    cout << "5. View Resource Status\n";
    cout << "6. Next Turn\n";
    cout << "0. Exit Game\n";
    cout << "Choose an action: ";
}

int main() {
    Kingdom myKingdom;
    int choice;
    int turn = 1;

    cout << "Welcome to the Stronghold Simulation!" << endl;

    while (true) {
        cout << "\n=== Turn " << turn << " ===";
        displayMenu();
        cin >> choice;

        switch (choice) {
            case 1: {
                int resChoice, amount;
                cout << "Select Resource to Gather:\n";
                cout << "0. Food  1. Wood  2. Stone  3. Iron  4. Gold\n";
                cin >> resChoice;
                cout << "Enter amount to gather: ";
                cin >> amount;
                myKingdom.getResourceManager().gather(static_cast<ResourceType>(resChoice), amount);
                break;
            }

            case 2: {
                int soldiers;
                cout << "Enter number of soldiers to recruit: ";
                cin >> soldiers;
                myKingdom.getMilitary().recruitSoldiers(soldiers);
                break;
            }

            case 3: {
                double rate;
                cout << "Enter new tax rate (0.0 - 1.0): ";
                cin >> rate;
                myKingdom.getEconomy().adjustTaxRate(rate);
                break;
            }

            case 4: {
                cout << "\n--- Population Status ---" << endl;
                for (int i = 0; i < SOCIAL_CLASS_COUNT; ++i) {
                    cout << "Class " << i << " - Count: " 
                         << myKingdom.getPopulation().getCount(static_cast<SocialClass>(i))
                         << ", Happiness: "
                         << myKingdom.getPopulation().getHappiness(static_cast<SocialClass>(i))
                         << endl;
                }
                break;
            }

            case 5: {
                cout << "\n--- Resource Status ---" << endl;
                for (int i = 0; i < RESOURCE_TYPE_COUNT; ++i) {
                    cout << "Resource " << i << " - Amount: "
                         << myKingdom.getResourceManager().get(static_cast<ResourceType>(i))
                         << endl;
                }
                break;
            }

            case 6: {
                myKingdom.update();
                myKingdom.handleEvents();
                myKingdom.checkFinancialHealth();
                ++turn;
                break;
            }

            case 0: {
                cout << "Exiting simulation. Farewell!" << endl;
                return 0;
            }

            default:
                cout << "Invalid choice. Please try again.\n";
        }
    }

    return 0;
}
