#include "stronghold.h"
#include <iostream>

using namespace std;

Kingdom::Kingdom()
    : population(), leadership(), economy(), bank(), military(), resourceManager(), eventManager(), corruption() {
}

void Kingdom::update() {
    population.update(*this);
    leadership.update(*this);
    economy.update(*this);
    bank.update(*this);
    military.update(*this);
    resourceManager.update(*this);
    eventManager.update(*this);
    corruption.update(*this);
}

void Kingdom::checkFinancialHealth() {
    // Example: Check if the kingdom's economy is in good shape
    if (economy.getGoldReserve() < 1000.0) {
        cout << "Warning: Low gold reserve!" << endl;
    }
    if (economy.getTaxRate() > 0.5) {
        cout << "Warning: High tax rate!" << endl;
    }
}




Population& Kingdom::getPopulation() {
    return population;
}

Leadership& Kingdom::getLeadership() {
    return leadership;
}

Economy& Kingdom::getEconomy() {
    return economy;
}

Bank& Kingdom::getBank() {
    return bank;
}

Military& Kingdom::getMilitary() {
    return military;
}

ResourceManager& Kingdom::getResourceManager() {
    return resourceManager;
}

EventManager& Kingdom::getEventManager() {
    return eventManager;
}

Corruption& Kingdom::getCorruption() {
    return corruption;
}
