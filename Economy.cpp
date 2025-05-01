#include "Stronghold.h"

Economy::Economy() :taxRate(0.2),inflationRate(0.02),goldReserve(10000.0){}

void Economy::update(Kingdom& kingdom) {
    inflationRate += taxRate * 0.005;
    inflationRate += (rand() % 100) / 10000.0;

    if (inflationRate < 0.01) 
        inflationRate = 0.01;
    if (inflationRate > 0.25) 
        inflationRate = 0.25;
    goldReserve *= (1.0 - inflationRate / 4.0); 
    
    Population& pop = kingdom.getPopulation();

    double taxRevenue = 0.0;
    taxRevenue += pop.getCount(PEASANT) * taxRate * 0.5;  
    taxRevenue += pop.getCount(MERCHANT) * taxRate * 1.5; 
    taxRevenue += pop.getCount(NOBLE) * taxRate * 0.2;   

    goldReserve += taxRevenue;

 
    pop.adjustHappiness(PEASANT, -taxRate * 0.1);
    pop.adjustHappiness(MERCHANT, -taxRate * 0.05);
    pop.adjustHappiness(NOBLE, -taxRate * 0.02);
}

void Economy::adjustTaxRate(double newRate) {
    if (newRate >= 0.0 && newRate <= 0.5) {
        taxRate = newRate;
    }
}

void Economy::adjustInflation(double adjustment) {
    inflationRate += adjustment;
    if (inflationRate < 0.01) 
        inflationRate = 0.01;
    if (inflationRate > 0.30) 
        inflationRate = 0.30;
}

void Economy::tradeResources(Kingdom& kingdom) {
    ResourceManager& resources = kingdom.getResourceManager();
    if (resources.get(FOOD) > 1500) {
        int tradeAmount = resources.get(FOOD) * 0.15;
        resources.consume(FOOD, tradeAmount);
        goldReserve += tradeAmount * 0.8; 
    }
    if (resources.get(WOOD) > 800) {
        int tradeAmount = resources.get(WOOD) * 0.2; 
        resources.consume(WOOD, tradeAmount);
        goldReserve += tradeAmount * 1.2; 
    }
    if (resources.get(STONE) > 500 && resources.get(IRON) > 300) {
        int stoneAmount = resources.get(STONE) * 0.1;
        int ironAmount = resources.get(IRON) * 0.1;
        resources.consume(STONE, stoneAmount);
        resources.consume(IRON, ironAmount);
        goldReserve += (stoneAmount * 1.5) + (ironAmount * 2.0);
    }

    double corruptionLoss = goldReserve * (kingdom.getCorruption().getCorruptionLevel() * 0.3);
    goldReserve -= corruptionLoss;
    kingdom.getPopulation().adjustHappiness(MERCHANT, 0.08);
}

void Economy::fundPublicServices() {
    double cost = 500.0;

    if (goldReserve >= cost) {
        goldReserve -= cost;
    }
}

double Economy::getTaxRate() const {
    return taxRate;
}

double Economy::getInflation() const {
    return inflationRate;
}

double Economy::getGoldReserve() const {
    return goldReserve;
}
