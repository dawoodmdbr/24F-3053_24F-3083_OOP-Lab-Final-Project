
#include "Stronghold.h"
#include <iostream>
#include <limits>
#include <cstdlib>
#include <ctime>

using namespace std;


void militaryMenu(Kingdom& kingdom) {
    Military& military = kingdom.getMilitary();

    while (true) {
        cout << endl << " ===MILITARY MENU===" << endl;
        cout << "1. Attempt Recruitment" << endl;
        cout << "2. View Soldier Count" << endl;
        cout << "3. Train Soldiers" << endl;
        cout << "4. View Morale" << endl;
        cout << "0. Back to Main Menu" << endl;
        cout << "Choice: ";

        int choice;
        cin >> choice;

        if (cin.fail()) {
            cin.clear();
            cin.ignore();
            cout << "Invalid input" << endl;
            continue;
        }

        switch (choice) {
        case 1:
            military.recruitSoldiers();
            break;

        case 2:
            cout << "Total soldiers: " << military.getSoldierCount() << endl;
            break;

        case 3: {
            cout << "Available soldiers: " << military.getSoldierCount() << endl;
            cout << "Enter number to train: ";
            int num;
            cin >> num;
            military.trainSoldiers(num);
            break;
        }
        case 4:
            cout << "Current morale: " << (military.getMorale() * 100) << "%" << endl;
            break;

        case 0:
            return;

        default:
            cout << "Invalid choice" << endl;
        }

        cout << "Press Enter to continue...";
        cin.ignore();
        cin.get();
    }
}

void economyMenu(Kingdom& kingdom) {
    int choice;
    cout << endl << " ===ECONOMY MENU===" << endl;
    cout << "1. Adjust Tax Rate" << endl;
    cout << "2. View Tax Rate" << endl;
    cout << "3. View Corruption Level" << endl;
    cout << "4. View Inflation Rate" << endl;
    cout << "0. Back to Main Menu" << endl;
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
            cout << "Invalid rate." << endl;
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
        cout << "Invalid choice." << endl;
    }
}

void resourceMenu(Kingdom& kingdom) {
    int choice;
    cout << endl << " ===RESOURCE MENU===" << endl;
    cout << "1. Gather Resources" << endl;
    cout << "2. View Resource Stockpile" << endl;
    cout << "0. Back to Main Menu" << endl;
    cout << "Choice: ";
    cin >> choice;

    switch (choice) {
    case 1: {
        int resChoice, amount;
        cout << "Select Resource to Gather:" << endl;
        cout << "0. Food  1. Wood  2. Stone  3. Iron  4. Gold" << endl;
        cin >> resChoice;
        cout << "Enter amount to gather: ";
        cin >> amount;
        if (resChoice >= 0 && resChoice < RESOURCE_TYPE_COUNT && amount > 0)
            kingdom.getResourceManager().gather(static_cast<ResourceType>(resChoice), amount);
        else
            cout << "Invalid input." << endl;
        break;
    }
    case 2: {
        const char* resourceNames[] = { "Food", "Wood", "Stone", "Iron", "Gold" };
        cout << "Current Resource Stockpile:" << endl;
        for (int i = 0; i < RESOURCE_TYPE_COUNT; ++i) {
            cout << resourceNames[i] << " - Amount: "
                << kingdom.getResourceManager().get(static_cast<ResourceType>(i)) << endl;
        }
        break;
    }
    case 0: return;
    default:
        cout << "Invalid choice." << endl;
    }
}

void populationMenu(Kingdom& kingdom) {
    const char* classNames[] = { "Peasants", "Merchants", "Nobles", "Soldiers", "Civilians" };
    cout << endl << " Population Status" << endl;
    for (int i = 0; i < SOCIAL_CLASS_COUNT; ++i) {
        cout << classNames[i] << " - Count: " << kingdom.getPopulation().getCount(static_cast<SocialClass>(i))
            << ", Happiness: " << kingdom.getPopulation().getHappiness(static_cast<SocialClass>(i)) << endl;
    }
}

void leadershipMenu(Kingdom& kingdom) {
    Leadership& leadership = kingdom.getLeadership();
    Population& population = kingdom.getPopulation();

    auto clampPercent = [](double value) {
        return max(0.0, min(100.0, value * 100));
        };

    while (true) {
        cout << endl << " ===LEADERSHIP MENU=== " << endl;
        cout << "1. Leader Overview" << endl;
        cout << "2. Hold Election" << endl;
        cout << "3. Initiate Coup" << endl;
        cout << "4. Change Leader" << endl;
        cout << "5. View Popularity Effects" << endl;
        cout << "0. Return to Main Menu" << endl;
        cout << "Choice: ";

        int choice;
        cin >> choice;


        switch (choice) {
        case 1: {
            cout << endl << " --- LEADER STATS ---" << endl;
            cout << "Name: " << leadership.getLeaderName() << endl;
            cout << "Style: ";
            switch (leadership.getLeadershipStyle()) {
            case 0: cout << "Benevolent"; break;
            case 1: cout << "Neutral"; break;
            case 2: cout << "Tyrannical"; break;
            default: cout << "Unknown"; break;
            }
            cout << endl << " Level: " << leadership.getLeadershipLevel() << endl;
            cout << "Popularity: " << clampPercent(leadership.getPopularity()) << "%" << endl;

            cout << endl << " CLASS HAPPINESS:" << endl;
            cout << "- Peasants: " << clampPercent(population.getHappiness(PEASANT)) << "%" << endl;
            cout << "- Merchants: " << clampPercent(population.getHappiness(MERCHANT)) << "%" << endl;
            cout << "- Nobles: " << clampPercent(population.getHappiness(NOBLE)) << "%" << endl;
            cout << "- Soldiers: " << clampPercent(population.getHappiness(SOLDIER)) << "%" << endl;
            cout << "- Civilians: " << clampPercent(population.getHappiness(CIVILAN)) << "%" << endl;
            break;
        }

        case 2: {
            cout << endl << " Holding elections..." << endl;
            leadership.holdElection(kingdom);

            double popChange = (rand() % 30 - 10) / 100.0;
            leadership.affectPopularity(popChange);

            cout << "New leader: " << leadership.getLeaderName() << endl;
            cout << "Popularity " << (popChange >= 0 ? "+" : "")
                << clampPercent(popChange) << "%" << endl;
            break;
        }

        case 3: {
            if (leadership.getPopularity() < 0.3) {
                cout << endl << " Initiating coup..." << endl;
                leadership.initiateCoup(kingdom);

                population.adjustHappiness(SOLDIER, 0.15);
                population.adjustHappiness(PEASANT, -0.1);
                cout << "Coup successful! New leader: "
                    << leadership.getLeaderName() << endl;
            }
            else {
                cout << endl << " The people still support the current leader!" << endl;
                cout << "Coup attempt failed (-15% popularity)." << endl;
                leadership.affectPopularity(-0.15);
            }
            break;
        }

        case 4: {
            cout << endl << " Enter new leader name: ";
            string newName;
            cin.ignore();
            getline(cin, newName);

            cout << "Select leadership style:" << endl;
            cout << "0 - Benevolent" << endl << " 1 - Neutral" << endl << " 2 - Tyrannical" << endl;
            cout << "Choice: ";
            int style;
            cin >> style;

            if (style >= 0 && style <= 2) {
                leadership.changeLeader(newName, style);
                cout << "New leader appointed: " << newName << endl;

                double popEffect = (style == 0) ? 0.1 :
                    (style == 2) ? -0.1 : 0.0;
                leadership.affectPopularity(popEffect);
            }
            else {
                cout << "Invalid style selection." << endl;
            }
            break;
        }

        case 5: {
            cout << endl << " ---POPULARITY MENU---" << endl;
            cout << "Current: " << clampPercent(leadership.getPopularity()) << "%" << endl;
            cout << "Effects:" << endl;
            cout << "- Tax collection efficiency: "
                << clampPercent(leadership.getPopularity() * 0.2) << "%" << endl;
            cout << "- Military morale: +"
                << clampPercent(leadership.getPopularity() * 0.15) << "%" << endl;
            cout << "- Rebellion risk: "
                << clampPercent((1.0 - leadership.getPopularity()) * 0.5) << "%" << endl;
            break;
        }

        case 0:
            return;

        default:
            cout << "Invalid choice." << endl;
        }

        cout << endl << " Press Enter to continue...";
        cin.ignore();
        cin.get();
    }
}
void tradeMenu(Kingdom& kingdom) {
    TradeSystem& trade = kingdom.getTradeSystem();
    int choice;

    while (true) {
        cout << endl << " === TRADING CENTER ===" << endl;
        cout << "1. View Market Prices" << endl;
        cout << "2. Trade Resources" << endl;
        cout << "3. Sell Resources for Gold" << endl;
        cout << "0. Back to Main Menu" << endl;
        cout << "Choice: ";

        cin >> choice;

        if (cin.fail()) {
            cin.clear();
            cin.ignore();
            cout << "Invalid input" << endl;
            continue;
        }

        switch (choice) {
        case 1:
            trade.displayMarket();
            break;

        case 2: {
            int give, receive, amount;

            cout << endl << " Select resource to give:" << endl;
            cout << "1. Food" << endl;
            cout << "2. Wood" << endl;
            cout << "3. Stone" << endl;
            cout << "4. Iron" << endl;
            cout << "Choice: ";
            cin >> give;
            give--;

            cout << "Amount to trade: ";
            cin >> amount;

            cout << endl << " Select resource to receive:" << endl;
            cout << "1. Food" << endl;
            cout << "2. Wood" << endl;
            cout << "3. Stone" << endl;
            cout << "4. Iron" << endl;
            cout << "Choice: ";
            cin >> receive;
            receive--;

            if (give >= 0 && give <= 3 && receive >= 0 && receive <= 3) {
                trade.executeTrade(kingdom,
                    static_cast<ResourceType>(give),
                    amount,
                    static_cast<ResourceType>(receive));
            }
            else {
                cout << "Invalid resource selection!" << endl;
            }
            break;
        }

        case 3: {
            int give, amount;

            cout << endl << " Select resource to sell:" << endl;
            cout << "1. Food" << endl;
            cout << "2. Wood" << endl;
            cout << "3. Stone" << endl;
            cout << "4. Iron" << endl;
            cout << "Choice: ";
            cin >> give;
            give--;

            cout << "Amount to sell: ";
            cin >> amount;

            if (give >= 0 && give <= 3) {
                trade.executeTrade(kingdom,
                    static_cast<ResourceType>(give),
                    amount,
                    GOLD);
            }
            else {
                cout << "Invalid resource selection!" << endl;
            }
            break;
        }

        case 0:
            return;

        default:
            cout << "Invalid choice" << endl;
        }

        cout << endl << " Press Enter to continue...";
        cin.ignore();
        cin.get();
    }
}

void randomEvent(Kingdom& kingdom) {
    int eventRoll = rand() % 5;

    switch (eventRoll) {
    case 0:
        cout << endl << " A bountiful harvest increases food by 200." << endl;
        kingdom.getResourceManager().gather(FOOD, 200);
        break;
    case 1:
        cout << endl << " A fire destroys 100 wood." << endl;
        kingdom.getResourceManager().gather(WOOD, -100);
        break;
    case 2:
        cout << endl << " A rival kingdom attacks. You lose 20 soldiers." << endl;
        kingdom.getMilitary().recruitSoldiers();
        break;
    case 3:
        cout << endl << " The economy booms. You gain 300 gold." << endl;
        kingdom.getResourceManager().gather(GOLD, 300);
        break;
    case 4:
        cout << endl << " Unrest spreads. Happiness of peasants drops." << endl;
        kingdom.getPopulation().adjustHappiness(PEASANT, -10);
        break;
    }
}

void diplomacyMenu(Kingdom& currentPlayer, Kingdom& opponent, Diplomacy& diplomacy) {
    int choice;
    cout << endl << " === DIPLOMACY MENU ===" << endl;
    cout << "1. Declare War on Kingdom" << endl;
    cout << "2. Offer Alliance to Kingdom" << endl;
    cout << "3. Break Alliance with Kingdom" << endl;
    cout << "0. Back to Main Menu" << endl;
    cout << "Choice: ";
    cin >> choice;

    switch (choice) {
    case 1: {
        if (!diplomacy.isAtWar(currentPlayer, opponent)) {
            diplomacy.declareWar(currentPlayer, opponent);
        }
        else {
            cout << "War already declared with " << opponent.getName() << ".\n";
        }
        break;
    }
    case 2: {
        if (!diplomacy.isAllied(currentPlayer, opponent)) {
            diplomacy.formAlliance(currentPlayer, opponent);
        }
        else {
            cout << "Already allied with " << opponent.getName() << ".\n";
        }
        break;
    }
    case 3: {
        if (diplomacy.isAllied(currentPlayer, opponent)) {
            diplomacy.breakAlliance(currentPlayer, opponent);
        }
        else {
            cout << "No alliance to break with " << opponent.getName() << ".\n";
        }
        break;
    }
    case 0:
        cout << "Returning to Main Menu...\n";
        break;
    default:
        cout << "Invalid choice! Please try again.\n";
    }
}


void displayMainMenuSingle() {
    cout << endl << " Stronghold Management" << endl;
    cout << "1. Military" << endl;
    cout << "2. Economy" << endl;
    cout << "3. Resources" << endl;
    cout << "4. Population" << endl;
    cout << "5. Leadership" << endl;
    cout << "6. Trade Center" << endl;
    cout << "7. Next Turn" << endl;
    cout << "0. Exit Game" << endl;
    cout << "Select a category: ";
}

void displayMainMenuMulti() {
    cout << endl << " Stronghold Management" << endl;
    cout << "1. Military" << endl;
    cout << "2. Economy" << endl;
    cout << "3. Resources" << endl;
    cout << "4. Population" << endl;
    cout << "5. Leadership" << endl;
    cout << "6. Trade Center" << endl;
    cout << "7. Diplomacy" << endl;
	cout << "8. Communication" << endl;
    cout << "9. Next Turn" << endl;
    cout << "0. Exit Game" << endl;
    cout << "Select a category: ";
}


int main() {
    srand(time(0));
    int mainChoice;
    int turn = 1;

    cout << endl << " Welcome to Stronghold Management" << endl;
    cout << endl << "1. Single Player" << endl;
    cout << "2. Multiplayer" << endl;
    cout << "Choice: ";

    int gameMode;
    cin >> gameMode;

    if (gameMode == 1) {

        Kingdom singlePlayerKingdom;
        while (true) {
            cout << endl << " Day " << turn << "" << endl;
            displayMainMenuSingle();
            cin >> mainChoice;

            switch (mainChoice) {
            case 1: militaryMenu(singlePlayerKingdom); break;
            case 2: economyMenu(singlePlayerKingdom); break;
            case 3: resourceMenu(singlePlayerKingdom); break;
            case 4: populationMenu(singlePlayerKingdom); break;
            case 5: leadershipMenu(singlePlayerKingdom); break;
            case 6: tradeMenu(singlePlayerKingdom); break;
            case 7:
                cout << endl << " Processing Turn " << turn << "..." << endl;
                singlePlayerKingdom.update();
                singlePlayerKingdom.handleEvents();
                randomEvent(singlePlayerKingdom);
                singlePlayerKingdom.checkFinancialHealth();
                ++turn;
                break;
            case 0:
                cout << endl << " Exiting game. Thank you for playing." << endl;
                return 0;
            default:
                cout << "Invalid choice." << endl;
            }

            system("pause");
            system("cls");
        }
    }
    else if (gameMode == 2) {
        MultiplayerSystem multiplayer;
        multiplayer.startGame();
        Diplomacy diplomacy;

        while (true) {
            cout << endl << " Day " << multiplayer.getCurrentTurn() << "" << endl;
            cout << multiplayer.getCurrentPlayerName() << "'s Turn" << endl;
            displayMainMenuMulti();
            cin >> mainChoice;


            switch (mainChoice) {
            case 1: militaryMenu(multiplayer.getCurrentPlayer()); break;
            case 2: economyMenu(multiplayer.getCurrentPlayer()); break;
            case 3: resourceMenu(multiplayer.getCurrentPlayer()); break;
            case 4: populationMenu(multiplayer.getCurrentPlayer()); break;
            case 5: leadershipMenu(multiplayer.getCurrentPlayer()); break;
            case 6: tradeMenu(multiplayer.getCurrentPlayer()); break;
            case 7:diplomacyMenu(multiplayer.getCurrentPlayer(), multiplayer.getOpponentPlayer(), diplomacy); break;
			case 8:multiplayer.communicationMenu(); break;
            case 9:
                cout << endl << " Processing Turn " << multiplayer.getCurrentTurn() << "..." << endl;
                multiplayer.processCurrentTurn();
                randomEvent(multiplayer.getCurrentPlayer());
                multiplayer.switchTurn();
                break;
            case 0:
                cout << endl << " Exiting game. Thank you for playing." << endl;
                return 0;
            default:
                cout << "Invalid choice." << endl;
            }

            system("pause");
            system("cls");
        }
    }
    else {
        cout << "Invalid game mode selected." << endl;
        return 0;
    }
}
