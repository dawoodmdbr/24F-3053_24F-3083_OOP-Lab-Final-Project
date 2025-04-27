#ifndef STRONGHOLD_H
#define STRONGHOLD_H

#include <iostream>
#include <string>
#include <array>
using namespace std;

enum SocialClass { PEASANT, MERCHANT, NOBLE, SOLDIER, SOCIAL_CLASS_COUNT };
enum ResourceType { FOOD, WOOD, STONE, IRON, GOLD, RESOURCE_TYPE_COUNT };

class Population;
class Military;
class Economy;
class Leadership;

class Kingdom {
private:
    Population* population;
    Military* military;
    Economy* economy;
    Leadership* leadership;

public:
    Kingdom();
    ~Kingdom();

    Population* getPopulation() const;
    Military* getMilitary() const;
    Economy* getEconomy() const;
    Leadership* getLeadership() const;

    void update();
};

class Population {
private:
    struct SocialGroup {
        SocialClass sClass;
        int count;
        double happiness;
    };

    array<SocialGroup, static_cast<int>(SocialClass::SOCIAL_CLASS_COUNT)> groups; // Fixed-size array using std::array
    double growthRate;
    double health;

public:
    Population();
    void update(Kingdom& kingdom);
    void adjustHappiness(SocialClass sClass, double amount);
    void addPopulation(SocialClass sClass, int count);
    bool removePopulation(SocialClass sClass, int count);
    int getCount(SocialClass sClass) const;
    double getHappiness(SocialClass sClass) const;
    double getOverallHappiness() const;
    double getHealth() const;
    void affectHealth(double amount);
};

class Military {
private:
    int soldiers;
    int trainedSoldiers;
    double morale;
    double trainingProgress;
    double corruptionLevel;

public:
    Military();
    void update(Kingdom& kingdom);
    bool recruit(int count, Population& population);
    void train(double resourcesSpent);
    void affectMorale(double amount);
    void affectCorruption(double amount);
    int getSoldierCount() const;
    int getTrainedSoldierCount() const;
    double getMorale() const;
    double getCorruptionLevel() const;
};

class Economy {
private:
    double treasury;
    double taxRate;
    double inflation;

public:
    Economy();
    void update(Kingdom& kingdom);
    void collectTaxes(Population& population);
    void setTaxRate(double rate);
    double getTreasury() const;
    double getTaxRate() const;
    double getInflation() const;
    bool spend(double amount);
    void earn(double amount);
};

class Leadership {
private:
    string leaderName;
    int leadershipStyle; // 0:autocratic, 1:democratic
    double popularity;

public:
    Leadership(const string& name);
    void update(Kingdom& kingdom);
    void changeLeader(const string& newName, int style);
    void affectPopularity(double amount);
    string getLeaderName() const;
    int getLeadershipStyle() const;
    double getPopularity() const;
};

#endif // STRONGHOLD_H
