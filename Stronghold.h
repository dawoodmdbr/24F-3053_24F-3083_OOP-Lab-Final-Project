#ifndef STRONGHOLD_H
#define STRONGHOLD_H

#include <string>
#include <vector>
#include <random>

using namespace std;

enum SocialClass { PEASANT, MERCHANT, NOBLE, SOLDIER, SOCIAL_CLASS_COUNT };

enum ResourceType { FOOD, WOOD, STONE, IRON, GOLD, RESOURCE_TYPE_COUNT };

struct SocialGroup {
    SocialClass socialClass;
    int count;
    double happiness;
};

class Population {
private:
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
    void affectHealth(double amount);
};

class Leadership {
private:
    string leaderName;
    int leadershipStyle;
    double popularity;
    
public:
    Leadership(const string& name);
    void update(Kingdom& kingdom);
    void holdElection(Kingdom& kingdom);
    void initiateCoup(Kingdom& kingdom);
    void changeLeader(const string& newName, int style);
    void affectPopularity(double amount);
    string getLeaderName() const;
    int getLeadershipStyle() const;
    double getPopularity() const;
};

class Economy {
private:
    double taxRate;
    double inflationRate;
    double goldReserve;
    vector<Resource> resources;
    
public:
    Economy();
    void update(Kingdom& kingdom);
    void adjustTaxRate(double amount);
    void adjustInflation(double amount);
    void tradeResources();
    void fundPublicServices();
    double getTaxRate() const;
    double getInflation() const;
    double getGoldReserve() const;
};

class Bank {
private:
    double loanAmount;
    double interestRate;
    double treasuryBalance;
    bool fraudDetected;
    
public:
    Bank();
    void issueLoan(double amount);
    void repayLoan(double amount);
    void auditTreasury();
    void detectFraud();
    void applyInterest();
};

class Military {
private:
    int soldierCount;
    double morale;
    double foodRequired;
    double payRequired;
    
public:
    Military();
    void recruitSoldiers(int count);
    void paySoldiers();
    void trainSoldiers(int count);
    void manageMorale();
};

class Resource {
private:
    ResourceType type;
    double amount;
    
public:
    Resource(ResourceType type, double amount);
    void gather(double amount);
    void consume(double amount);
    void trade(double amount);
    ResourceType getType() const;
    double getAmount() const;
};

class ResourceManager {
private:
    vector<Resource> resources;
    
public:
    ResourceManager();
    void updateResources();
    void tradeResources(Resource& resource, double amount);
    void stockpileResources(Resource& resource, double amount);
};

class Event {
private:
    string description;
    int impact;
    
public:
    Event(string description, int impact);
    void triggerEvent();
};

class EventManager {
private:
    vector<Event> events;
    
public:
    EventManager();
    void generateRandomEvent();
    void applyEvent(Event& event);
};

class Corruption {
private:
    double corruptionLevel;
    
public:
    Corruption();
    void applyCorruption(double amount);
    void removeCorruption();
    bool isCorrupted() const;
};

class Audit {
private:
    
public:
    Audit();
    void conductAudit(Kingdom& kingdom);
    bool detectFraud(Kingdom& kingdom);
};

class Kingdom {
private:
    Population population;
    Leadership leadership;
    Economy economy;
    Bank bank;
    Military military;
    ResourceManager resourceManager;
    EventManager eventManager;
    Audit audit;
    Corruption corruption;
    
public:
    Kingdom();
    void update();
    void checkFinancialHealth();
    void handleEvents();
};

#endif  // STRONGHOLD_H
