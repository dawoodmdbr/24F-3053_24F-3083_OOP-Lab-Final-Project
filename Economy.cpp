#include"Stronghold.h"

Economy::Economy() : goldReserve(1000.0), taxRate(10.0) {}

void Economy::adjustTaxRate(double newRate) {
    taxRate = newRate;
}

void Economy::update(Kingdom& kingdom) {
    // Simulate economy changes: e.g., tax income from population
    double income = kingdom.getPopulation().getTotalPopulation() * taxRate * 0.1;
    goldReserve += income;
}

double Economy::getGoldReserve() const {
    return goldReserve;
}

double Economy::getTaxRate() const {
    return taxRate;
}
