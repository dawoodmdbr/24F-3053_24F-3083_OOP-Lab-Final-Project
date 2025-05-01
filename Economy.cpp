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
void Economy::adjustInflation(double a) {
    inflationRate = a;
}
void Economy::tradeResources() {
    // Simulate trading resources with other kingdoms
    // For simplicity, let's say we gain some gold from trade
    goldReserve += 500.0; // Example trade income
}
void Economy::fundPublicServices() {
    // Simulate funding public services
    // For simplicity, let's say we spend some gold on public services
    goldReserve -= 200.0; // Example expense for public services
}
double Economy::getInflation() const {
    return inflationRate;
}

double Economy::getGoldReserve() const {
    return goldReserve;
}

double Economy::getTaxRate() const {
    return taxRate;
}

