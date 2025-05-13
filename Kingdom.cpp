#include "Stronghold.h"
#include <iostream>

using namespace std;

Kingdom::Kingdom()
{
    population = Population();
    leadership = Leadership("Leader");
    economy = Economy();
    bank = Bank();
    military = Military();
    resourceManager = ResourceManager();
    eventManager = EventManager();
    corruption = Corruption();
    comms = CommunicationSystem("chatHistory.txt");
    tradeSystem = TradeSystem();
    diplomacy = Diplomacy();
}

Kingdom::Kingdom(string name)
{
    this->name = name;
    population = Population();
    leadership = Leadership("Leader");
    economy = Economy();
    bank = Bank();
    military = Military();
    resourceManager = ResourceManager();
    eventManager = EventManager();
    corruption = Corruption();
    comms = CommunicationSystem("chatHistory.txt");
    tradeSystem = TradeSystem();
    diplomacy = Diplomacy();
}

string Kingdom::getName() const
{
    return name;
}

int Kingdom::getId() const
{
    return id;
}

void Kingdom::update()
{
    population.update(*this);
    leadership.update(*this);
    bank.update(*this);
    military.update(*this);
    resourceManager.update(*this);
    eventManager.update(*this);
    corruption.update(*this);
}

void Kingdom::checkFinancialHealth()
{

    if (economy.getGoldReserve() < 1000.0)
    {
        cout << "Warning: Low gold reserve!" << endl;
    }
    if (economy.getTaxRate() > 0.5)
    {
        cout << "Warning: High tax rate!" << endl;
    }
}

void Kingdom::updateAllianceStatus(int otherKingdomId, AllianceStatus status, const string& message) {
    
    if (otherKingdomId >= 0 && otherKingdomId < 100) {  
        allianceStatus[otherKingdomId] = status;
    }
    cout << message << endl;
}


AllianceStatus Kingdom::getAllianceStatus(int otherKingdomId) const {
    if (otherKingdomId >= 0 && otherKingdomId < 100) {  
        return allianceStatus[otherKingdomId];
    }
    return AllianceStatus::NONE;  
}

void Kingdom::handleEvents()
{
    eventManager.generateRandomEvent();
    Event latestEvent = eventManager.getLatestEvent();
    eventManager.applyEvent(latestEvent);
    eventManager.handleEvent(*this, latestEvent);
}

TradeSystem &Kingdom::getTradeSystem()
{
    return tradeSystem;
}
Population &Kingdom::getPopulation()
{
    return population;
}

Leadership &Kingdom::getLeadership()
{
    return leadership;
}

Bank &Kingdom::getBank()
{
    return bank;
}

Military &Kingdom::getMilitary()
{
    return military;
}

ResourceManager &Kingdom::getResourceManager()
{
    return resourceManager;
}

Economy &Kingdom::getEconomy()
{
    return economy;
}

EventManager &Kingdom::getEventManager()
{
    return eventManager;
}

Corruption &Kingdom::getCorruption()
{
    return corruption;
}
CommunicationSystem &Kingdom::getComms()
{
    return comms;
}
Diplomacy &Kingdom::getDiplomacy()
{
    return diplomacy;
}