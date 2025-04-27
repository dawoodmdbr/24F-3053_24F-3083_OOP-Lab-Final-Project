#ifndef STRONGHOLD_H
#define STRONGHOLD_H
#include <iostream>
#include <string>
using namespace std;

enum SocialClass { PEASANT, MERCHANT, NOBLE, SOLDIER, SOCIAL_CLASS_COUNT };
enum ResourceType { FOOD, WOOD, STONE, IRON, GOLD, RESOURCE_TYPE_COUNT };

class Population;
class Military;
class Economy;
class Leadership;

//main kingdom class
class Kingdom {
};

//population handling
class Population {
private:
    struct SocialGroup {
        SocialClass sClass;
        int count;
        double happiness;
    };

    SocialGroup groups[SOCIAL_CLASS_COUNT];
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
    double getHealth() const { 
        return health; 
    }
    void affectHealth(double amount);
};

//military system
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
    int getSoldierCount() const { 
        return soldiers; 
    }
    int getTrainedSoldierCount() const { 
        return trainedSoldiers; 
    }
    double getMorale() const { 
        return morale; 
    }
    double getCorruptionLevel() const { 
        return corruptionLevel; 
    }
};

//economy system
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
    double getTreasury() const { 
        return treasury; 
    }
    double getTaxRate() const { 
        return taxRate; 
    }
    double getInflation() const { 
        return inflation; 
    }
    bool spend(double amount);
    void earn(double amount);
};

//leadership system
class Leadership {
private:
    string leaderName;
    int leadershipStyle; 
    double popularity;

public:
    Leadership(const string& name);
    void update(Kingdom& kingdom);
    void changeLeader(const string& newName, int style);
    void affectPopularity(double amount);
    string getLeaderName() const { 
        return leaderName; 
    }
    int getLeadershipStyle() const { 
        return leadershipStyle; 
    }
    double getPopularity() const { 
        return popularity; 
    }
};

#endif