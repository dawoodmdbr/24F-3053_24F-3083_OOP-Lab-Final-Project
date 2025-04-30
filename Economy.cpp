#include "Stronghold.h"

Economy::Economy() : taxRate(0.1), inflationRate(0.02), goldReserve(1000.0) {
    // Initialize with default values
}

void Economy::update(Kingdom& kingdom) {
    // Calculate tax income based on population and tax rate
    double income = kingdom.getPopulation().getTotalPopulation() * taxRate * 0.1;
    
    // High tax rates reduce happiness
    if (taxRate > 0.2) {
        kingdom.getPopulation().adjustHappiness(PEASANT, -0.1);
        kingdom.getPopulation().adjustHappiness(MERCHANT, -0.2);
    }
    
    // Apply inflation effects
    goldReserve *= (1.0 + inflationRate);
    
    // Add tax income
    goldReserve += income;
    
    // Fund public services
    fundPublicServices();
}

void Economy::adjustTaxRate(double amount) {
    taxRate += amount;
    
    // Ensure tax rate is within reasonable bounds
    if (taxRate < 0.05) taxRate = 0.05;
    if (taxRate > 0.5) taxRate = 0.5;
}

void Economy::adjustInflation(double amount) {
    inflationRate += amount;
    
    // Ensure inflation rate is within reasonable bounds
    if (inflationRate < 0.0) inflationRate = 0.0;
    if (inflationRate > 0.2) inflationRate = 0.2;
}

void Economy::tradeResources() {
    // Simulate trading resources with other kingdoms
    goldReserve += 500.0; // Basic trade income
}

void Economy::fundPublicServices() {
    // Simulate funding public services
    double serviceCost = 200.0;
    
    if (goldReserve >= serviceCost) {
        goldReserve -= serviceCost;
    } else {
        // Not enough gold for services
        throw EconomyException("Insufficient funds for public services");
    }
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
