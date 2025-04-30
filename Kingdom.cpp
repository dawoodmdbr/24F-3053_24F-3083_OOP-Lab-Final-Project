#include "Stronghold.h"
#include <fstream>

Kingdom::Kingdom() : kingdomName("Unnamed Kingdom"), day(1) {
    // Initialize all subsystems with default values
}

Kingdom::Kingdom(const string& name) : kingdomName(name), day(1) {
    // Initialize all subsystems with default values
}

void Kingdom::update() {
    // Update all subsystems in a specific order to ensure dependencies
    
    // First update resource production
    resourceManager.update(*this);
    
    // Update population dynamics
    population.update(*this);
    
    // Update leadership
    leadership.update(*this);
    
    // Update economy
    economy.update(*this);
    
    // Update banking
    bank.update(*this);
    
    // Update military
    military.update(*this);
    
    // Update corruption
    corruption.update(*this);
    
    // Handle events last
    eventManager.update(*this);
    
    // Check financial health
    checkFinancialHealth();
    
    // Increment day counter
    day++;
}

void Kingdom::checkFinancialHealth() {
    // Verify the kingdom's economic health
    if (economy.getGoldReserve() < 1000.0) {
        cout << "WARNING: Low gold reserve! Current: " << economy.getGoldReserve() << endl;
    }
    
    if (economy.getTaxRate() > 0.3) {
        cout << "WARNING: High tax rate! Current: " << economy.getTaxRate() * 100 << "%" << endl;
    }
    
    if (bank.getLoanAmount() > 3000.0) {
        cout << "WARNING: High loan amount! Current: " << bank.getLoanAmount() << endl;
    }
}

void Kingdom::handleEvents() {
    // Generate a random event
    eventManager.generateRandomEvent();
    
    // Get and handle the latest event
    Event latestEvent = eventManager.getLatestEvent();
    eventManager.applyEvent(latestEvent);
    eventManager.handleEvent(*this, latestEvent);
}

void Kingdom::saveGameState(const string& filename) {
    ofstream file(filename);
    if (!file.is_open()) {
        throw StrongholdException("Failed to open file for saving: " + filename);
    }
    
    // Save basic kingdom info
    file << kingdomName << endl;
    file << day << endl;
    
    // Save resource information
    for (int i = 0; i < RESOURCE_TYPE_COUNT; i++) {
        file << resourceManager.getAmount(static_cast<ResourceType>(i)) << endl;
    }
    
    // Save population information
    file << population.getTotalPopulation() << endl;
    for (int i = 0; i < SOCIAL_CLASS_COUNT; i++) {
        file << population.getCount(static_cast<SocialClass>(i)) << endl;
        file << population.getHappiness(static_cast<SocialClass>(i)) << endl;
    }
    
    // Save leadership information
    file << leadership.getLeaderName() << endl;
    file << leadership.getLeadershipStyle() << endl;
    file << leadership.getPopularity() << endl;
    
    // Save economy information
    file << economy.getGoldReserve() << endl;
    file << economy.getTaxRate() << endl;
    file << economy.getInflation() << endl;
    
    // Save bank information
    file << bank.getTreasuryBalance() << endl;
    file << bank.getLoanAmount() << endl;
    file << bank.getInterestRate() << endl;
    
    // Save military information
    file << military.getSoldierCount() << endl;
    file << military.getMorale() << endl;
    
    // Save corruption level
    file << corruption.getCorruptionLevel() << endl;
    
    file.close();
    cout << "Game saved successfully to " << filename << endl;
}

void Kingdom::loadGameState(const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        throw StrongholdException("Failed to open file for loading: " + filename);
    }
    
    // This is a simplified loading function, in a real game you'd need
    // more robust error checking and data validation
    
    // Load basic kingdom info
    getline(file, kingdomName);
    file >> day;
    
    // Load resource information
    double resourceAmount;
    for (int i = 0; i < RESOURCE_TYPE_COUNT; i++) {
        file >> resourceAmount;
        resourceManager.gather(static_cast<ResourceType>(i), resourceAmount);
    }
    
    // Load population information
    int totalPop;
    file >> totalPop;
    
    int count;
    double happiness;
    for (int i = 0; i < SOCIAL_CLASS_COUNT; i++) {
        file >> count >> happiness;
        SocialClass sc = static_cast<SocialClass>(i);
        population.addPopulation(sc, count);
        population.adjustHappiness(sc, happiness);
    }
    
    // Load leadership information
    string leaderName;
    int style;
    double popularity;
    file >> leaderName >> style >> popularity;
    leadership.changeLeader(leaderName, style);
    leadership.affectPopularity(popularity);
    
    // Other subsystems would be loaded similarly
    
    file.close();
    cout << "Game loaded successfully from " << filename << endl;
}

void Kingdom::logScore(const string& filename) {
    ofstream file(filename, ios::app); // Append mode
    if (!file.is_open()) {
        throw StrongholdException("Failed to open score file: " + filename);
    }
    
    // Calculate a simple score based on various factors
    int score = 
        population.getTotalPopulation() * 10 +
        static_cast<int>(economy.getGoldReserve()) +
        military.getSoldierCount() * 50 -
        static_cast<int>(bank.getLoanAmount()) -
        static_cast<int>(corruption.getCorruptionLevel() * 1000);
    
    // Write score with timestamp
    file << "Day " << day << " - " << kingdomName << ": " << score << " points" << endl;
    
    file.close();
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

string Kingdom::getKingdomName() const {
    return kingdomName;
}

int Kingdom::getDay() const {
    return day;
}
