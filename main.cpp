#include "Stronghold.h"
#include <iostream>

int main() {
    Kingdom myKingdom;

    cout << "Welcome to the Stronghold Simulation!" << endl;

    for (int day = 1; day <= 10; ++day) {
        cout << "\n--- Day " << day << " ---" << endl;
        myKingdom.update();
        myKingdom.handleEvents();
        myKingdom.checkFinancialHealth();
    }

    cout << "\nSimulation Ended." << endl;

    system("pause"); 
    return 0;
}
