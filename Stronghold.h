#ifndef STRONGHOLD_H
#define STRONGHOLD_H

#include <string>
#include <iostream>
#include<fstream>
#include <random>

using namespace std;

enum SocialClass
{
    PEASANT,
    MERCHANT,
    NOBLE,
    SOLDIER,
    CIVILAN,
    SOCIAL_CLASS_COUNT
};
enum ResourceType
{
    FOOD,
    WOOD,
    STONE,
    IRON,
    GOLD,
    RESOURCE_TYPE_COUNT
};
enum EventType {
    PLAGUE,
    FAMINE,
    REBELLION,
    DISCOVERY_OF_GOLD,
    NATURAL_DISASTER,
    TAX_EVASION_SCANDAL,
    MERCHANTS_STRIKE,
    DRAGON_SIGHTING,
    COMEDY_FESTIVAL,
    ASTRONOMICAL_EVENT,
    EVENT_TYPE_COUNT
};


struct SocialGroup
{
    SocialClass socialClass;
    int count;
    double happiness;
};

class Kingdom;


class Corruption
{
protected:
    double corruptionLevel;

public:
    Corruption();
    Corruption(double initialCorruption);
    void update(Kingdom& kingdom);
    void increaseCorruption(double amount);
    void decreaseCorruption(double amount);
    double getCorruptionLevel() const;
    bool isCorrupted() const;
};

class Bank : public Corruption {
private:
    double loanAmount;
    double interestRate;
    double treasuryBalance;
    bool fraudDetected;

public:
    Bank();
    Bank(double loan, double interest, double balance);
    void setLoanAmount(double a);
    void update(Kingdom& kingdom);
    void issueLoan(double a);
    void repayLoan(double a);
    void auditTreasury();
    void detectFraud();
    void applyInterest();
    void deductGold(double amount);
};


class Economy {
private:
    double taxRate;
    double inflationRate;
    double goldReserve;

public:
    Economy();
    void update(Kingdom& kingdom);
    void adjustTaxRate(double a);
    void adjustInflation(double a);
    void tradeResources();
    void fundPublicServices();
    double getTaxRate() const;
    double getInflation() const;
    double getGoldReserve() const;
};

class Event
{
private:
    EventType type;
    string description;
    int impact;

public:
    Event();
    Event(EventType t, const string& desc, int imp);
    void update(Kingdom& kingdom);
    void triggerEvent();
    EventType getType() const;
    string getDescription() const;
    int getImpact() const;
};

class EventManager
{
private:
    Event events[10];
    int eventCount;

public:
    EventManager();
    void update(Kingdom& kingdom);
    void generateRandomEvent();
    Event getLatestEvent() const;
    void applyEvent(Event& event);
    void handleEvent(Kingdom& kingdom, Event& event);
};


class Leadership
{
private:
    string leaderName;
    int leadershipStyle;
    double popularity;

public:
    Leadership();
    Leadership(const string& name);
    void update(Kingdom& kingdom);
    void holdElection(Kingdom& kingdom);
    void initiateCoup(Kingdom& kingdom);
    void changeLeader(const string& newName, int style);
    void affectPopularity(double a);
    string getLeaderName() const;
    int getLeadershipStyle() const;
    int getLeadershipLevel() const;
    double getPopularity() const;
};


class Military : public Corruption
{
private:
    int soldierCount;
    double morale;
    double foodRequired;
    double payRequired;
    int trainedSoldiers;
public:
    Military();
    void update(Kingdom& kingdom);
    void recruitSoldiers();
    void paySoldiers();
    void trainSoldiers(int count);
    void declareWar(Kingdom& kingdom);
    void manageMorale();
    void setSoldierCount(int count);
    int getSoldierCount() const;
    double getMorale() const;
};


class Population
{
private:
    SocialGroup groups[SOCIAL_CLASS_COUNT];
    double growthRate;
    double happiness[SOCIAL_CLASS_COUNT];
    double health;

public:
    Population();
    void update(Kingdom& kingdom);
    void adjustHappiness(SocialClass type, double delta);
    void addPopulation(SocialClass sClass, int count);
    bool removePopulation(SocialClass sClass, int count);
    int getCount(SocialClass sClass) const;
    double getHappiness(SocialClass sClass) const;
    double getOverallHappiness() const;
    int getTotalPopulation() const;
    void affectHappiness(double amount);
    void affectHealth(double amount);
};


class Resource
{
private:
    ResourceType type;
    double amount;
    double maxAmount;

public:
    Resource();
    Resource(ResourceType type, double a, double max);
    void update(Kingdom& kingdom);
    void gather(double a);
    void consume(double a);
    void trade(double a);
    ResourceType getType() const;
    double getAmount() const;
    void setAmount(double amt);
    double getMaxAmount() const;
};

class ResourceManager
{
private:
    Resource resources[RESOURCE_TYPE_COUNT];

public:
    ResourceManager();
    void update(Kingdom& kingdom);
    void gather(ResourceType type, int a);
    void consume(ResourceType type, int a);
    void trade(ResourceType fromType, ResourceType toType, int a);
    int get(ResourceType type) const;
};

class CommunicationSystem {
private:
    string fileName;
    string inMemLog[100];
    int logCount;
public:
    CommunicationSystem();
    CommunicationSystem(const string& file);
    void sendMessage(const string& sender, const string& receiver, const string& message);
    void showInMemChat() const;
    void showFileChat() const;
};



class TradeSystem {
private:
    double marketPrices[RESOURCE_TYPE_COUNT];
    double priceFluctuation;

public:
    TradeSystem();
    void updateMarket();
    void displayMarket() const;
    bool executeTrade(Kingdom& kingdom, ResourceType give, int giveAmount, ResourceType receive);
    double getPrice(ResourceType resource) const;
};

enum AllianceStatus {
    NONE,
    ALLIED,
    ENEMY,
    BETRAYED,
    ALLIANCE_STATUS_COUNT
};

class Diplomacy {
public:
    Diplomacy();


    void formAlliance(Kingdom& kingdom1, Kingdom& kingdom2);
    void breakAlliance(Kingdom& kingdom1, Kingdom& kingdom2);
    void declareWar(Kingdom& kingdom1, Kingdom& kingdom2);


    void applyWarConsequences(Kingdom& kingdom1, Kingdom& kingdom2);
    void applyBetrayalConsequences(Kingdom& kingdom1, Kingdom& kingdom2);


    bool isAllied(Kingdom& kingdom1, Kingdom& kingdom2) const;
    bool isAtWar(Kingdom& kingdom1, Kingdom& kingdom2) const;
    bool hasBetrayed(Kingdom& kingdom1, Kingdom& kingdom2) const;

private:

    void logAllianceFormed(Kingdom& kingdom1, Kingdom& kingdom2);
    void logAllianceBroken(Kingdom& kingdom1, Kingdom& kingdom2);
    void logWarDeclared(Kingdom& kingdom1, Kingdom& kingdom2);


};





class Kingdom
{
public:
    TradeSystem tradeSystem;
    string name;
    int id;
    Population population;
    Leadership leadership;
    Economy economy;
    Bank bank;
    Military military;
    ResourceManager resourceManager;
    EventManager eventManager;
    Corruption corruption;
    CommunicationSystem comms;
    Diplomacy diplomacy;
    AllianceStatus allianceStatus[10];
    string lastReceivedMessage;

    Kingdom();
    Kingdom(string name);

    string getName() const;
    int getId() const;
    void update();
    void checkFinancialHealth();
    void handleEvents();
    void updateAllianceStatus(int otherKingdomId, AllianceStatus status, const string& message);
    AllianceStatus getAllianceStatus(int otherKingdomId) const;
    TradeSystem& getTradeSystem();
    Population& getPopulation();
    Leadership& getLeadership();
    Economy& getEconomy();
    Bank& getBank();
    Military& getMilitary();
    ResourceManager& getResourceManager();
    EventManager& getEventManager();
    Corruption& getCorruption();
    CommunicationSystem& getComms();
    Diplomacy& getDiplomacy();
};

class MultiplayerSystem {
private:
    Kingdom player1;
    Kingdom player2;
    bool isPlayer1Turn;
    int currentTurn;
    string player1Name;
    string player2Name;

public:
    MultiplayerSystem();
    void startGame();
	void communicationMenu();
    void switchTurn();
    void processCurrentTurn();
    Kingdom& getCurrentPlayer();
    Kingdom& getOpponentPlayer();
    string getCurrentPlayerName() const;
    bool isCurrentPlayer1() const;
    int getCurrentTurn() const;
};
class Logger {
public:
    void logGameStart(bool isMultiplayer, const string& player1, const string& player2 = "");

};

#endif
