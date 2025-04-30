#include "Stronghold.h"

Corruption::Corruption() : corruptionLevel(0.1) {
    // Initialize with low corruption
}

Corruption::Corruption(double initialCorruption) : corruptionLevel(initialCorruption) {
    // Ensure corruption is within bounds
    if (corruptionLevel < 0.0) corruptionLevel = 0.0;
    if (corruptionLevel > 1.0) corruptionLevel = 1.0;
}

void Corruption::update(Kingdom& kingdom) {
    // Corruption is affected by financial health
    if (kingdom.getEconomy().getGoldReserve() < 1000.0) {
        increaseCorruption(0.05);
    } else {
        decreaseCorruption(0.02);
    }
    
    // Popularity affects corruption
    if (kingdom.getLeadership().getPopularity() < 30.0) {
        increaseCorruption(0.03);
    }
}

void Corruption::increaseCorruption(double amount) {
    corruptionLevel += amount;
    if (corruptionLevel > 1.0) {
        corruptionLevel = 1.0;
    }
}

void Corruption::decreaseCorruption(double amount) {
    corruptionLevel -= amount;
    if (corruptionLevel < 0.0) {
        corruptionLevel = 0.0;
    }
}

double Corruption::getCorruptionLevel() const {
    return corruptionLevel;
}

bool Corruption::isCorrupted() const {
    return corruptionLevel > 0.5;
}
