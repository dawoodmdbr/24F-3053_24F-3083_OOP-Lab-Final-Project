#include "Stronghold.h"

Population::Population() {
    groups[PEASANT] = {PEASANT, 1000, 50.0};
    groups[MERCHANT] = {MERCHANT, 500, 60.0};
    groups[NOBLE] = {NOBLE, 100, 80.0};
    groups[SOLDIER] = {SOLDIER, 200, 40.0};
    
    growthRate = 0.05;
    health = 75.0;
}

void Population::update(Kingdom& kingdom) {
    for (int i = 0; i < SOCIAL_CLASS_COUNT; i++) {
        groups[i].count += (groups[i].count * growthRate);
    }
    
    double overallHappiness = getOverallHappiness();
    health += (overallHappiness - 50) * 0.1;
}

void Population::adjustHappiness(SocialClass sClass, double amount) {
    if (sClass >= 0 && sClass < SOCIAL_CLASS_COUNT) {
        groups[sClass].happiness += amount;
    }
}

void Population::addPopulation(SocialClass sClass, int count) {
    if (sClass >= 0 && sClass < SOCIAL_CLASS_COUNT) {
        groups[sClass].count += count;
    }
}

bool Population::removePopulation(SocialClass sClass, int count) {
    if (sClass >= 0 && sClass < SOCIAL_CLASS_COUNT && groups[sClass].count >= count) {
        groups[sClass].count -= count;
        return true;
    }
    return false;
}

int Population::getCount(SocialClass sClass) const {
    if (sClass >= 0 && sClass < SOCIAL_CLASS_COUNT) {
        return groups[sClass].count;
    }
    return 0;
}

double Population::getHappiness(SocialClass sClass) const {
    if (sClass >= 0 && sClass < SOCIAL_CLASS_COUNT) {
        return groups[sClass].happiness;
    }
    return 0;
}

double Population::getOverallHappiness() const {
    double totalHappiness = 0;
    for (int i = 0; i < SOCIAL_CLASS_COUNT; i++) {
        totalHappiness += groups[i].happiness;
    }
    return totalHappiness / SOCIAL_CLASS_COUNT;
}

void Population::affectHealth(double amount) {
    health += amount;
}
