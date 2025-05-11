#include "Stronghold.h"
#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

TradeSystem::TradeSystem() : priceFluctuation(0.15) {
    marketPrices[FOOD] = 0.5;
    marketPrices[WOOD] = 1.0;
    marketPrices[STONE] = 1.5;
    marketPrices[IRON] = 2.0;
    marketPrices[GOLD] = 1.0;
    srand(static_cast<unsigned>(time(0)));
}

void TradeSystem::updateMarket() {
    for (int i = 0; i < RESOURCE_TYPE_COUNT; i++) {
        if (i != GOLD) {
            double change = ((rand() % 31) - 15) / 100.0;
            marketPrices[i] = max(0.1, marketPrices[i] * (1.0 + change));
        }
    }
}

void TradeSystem::displayMarket() const {
    cout << "\n=== MARKET PRICES ===" << endl;
    cout << "1. Food:  " << marketPrices[FOOD] << " gold" << endl;
    cout << "2. Wood:  " << marketPrices[WOOD] << " gold" << endl;
    cout << "3. Stone: " << marketPrices[STONE] << " gold" << endl;
    cout << "4. Iron:  " << marketPrices[IRON] << " gold" << endl;
}

bool TradeSystem::executeTrade(Kingdom& kingdom, ResourceType give, int giveAmount, ResourceType receive) {
    if (giveAmount <= 0) {
        cout << "Trade amount must be positive!\n";
        return false;
    }

    ResourceManager& resources = kingdom.getResourceManager();

    if (resources.get(give) < giveAmount) {
        cout << "Not enough resources to trade!\n";
        return false;
    }

    double exchangeRate = marketPrices[give] / marketPrices[receive];
    int receiveAmount = static_cast<int>(giveAmount * exchangeRate);

    if (receiveAmount < 1) {
        cout << "Trade amount too small!\n";
        return false;
    }

    resources.consume(give, giveAmount);
    resources.gather(receive, receiveAmount);

    cout << "\nTrade successful!\n";
    cout << "Gave: " << giveAmount << " units of ";
    switch (give) {
    case FOOD: cout << "Food"; break;
    case WOOD: cout << "Wood"; break;
    case STONE: cout << "Stone"; break;
    case IRON: cout << "Iron"; break;
    default: break;
    }

    cout << "\nReceived: " << receiveAmount << " units of ";
    switch (receive) {
    case FOOD: cout << "Food"; break;
    case WOOD: cout << "Wood"; break;
    case STONE: cout << "Stone"; break;
    case IRON: cout << "Iron"; break;
    case GOLD: cout << "Gold"; break;
    default: break;
    }
    cout << endl;

    return true;
}

double TradeSystem::getPrice(ResourceType resource) const {
    if (resource < 0 || resource >= RESOURCE_TYPE_COUNT) {
        return 0.0;
    }
    return marketPrices[resource];
}
