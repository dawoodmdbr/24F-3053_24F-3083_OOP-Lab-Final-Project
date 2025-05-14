#include "Stronghold.h"
#include <iostream>
#include <string>

using namespace std;

Diplomacy::Diplomacy() {
    
}


void Diplomacy::formAlliance(Kingdom& kingdom1, Kingdom& kingdom2) {
    
    kingdom1.updateAllianceStatus(kingdom2.getId(), AllianceStatus::ALLIED, "Alliance formed.");
    kingdom2.updateAllianceStatus(kingdom1.getId(), AllianceStatus::ALLIED, "");
    
    cout << "Alliance formed between " << kingdom1.getName() << " and " << kingdom2.getName() << ".\n";
}


void Diplomacy::breakAlliance(Kingdom& kingdom1, Kingdom& kingdom2) {
    
    kingdom1.updateAllianceStatus(kingdom2.getId(), AllianceStatus::ENEMY, "Alliance broken by betrayal.");
    kingdom2.updateAllianceStatus(kingdom1.getId(), AllianceStatus::ENEMY, "");
    applyWarConsequences(kingdom1, kingdom2);
    
    cout << "Alliance broken between " << kingdom1.getName() << " and " << kingdom2.getName() << ".\n";
}


void Diplomacy::declareWar(Kingdom& kingdom1, Kingdom& kingdom2) {
    
    kingdom1.updateAllianceStatus(kingdom2.getId(), AllianceStatus::ENEMY, "War declared.");
    kingdom2.updateAllianceStatus(kingdom1.getId(), AllianceStatus::ENEMY, "");
    
    applyWarConsequences(kingdom1, kingdom2);
    
    cout << "War declared between " << kingdom1.getName() << " and " << kingdom2.getName() << ".\n";
}


void Diplomacy::applyWarConsequences(Kingdom& kingdom1, Kingdom& kingdom2) {
    
    kingdom1.economy.adjustTaxRate(0.1);
    kingdom1.military.recruitSoldiers();
    kingdom1.corruption.increaseCorruption(5);
    kingdom1.military.manageMorale();

    cout << "Consequences of war applied between " << kingdom1.getName() << " and " << kingdom2.getName() << ".\n";
}


void Diplomacy::applyBetrayalConsequences(Kingdom& kingdom1, Kingdom& kingdom2) {
    
    kingdom1.military.declareWar(kingdom2);  
    
    kingdom1.economy.adjustTaxRate(0.75);    
    kingdom1.population.affectHappiness(-10);
    kingdom1.corruption.increaseCorruption(5);

    cout << "Betrayal consequences applied between " << kingdom1.getName() << " and " << kingdom2.getName() << ".\n";
}


bool Diplomacy::isAllied(Kingdom& kingdom1, Kingdom& kingdom2) const {
    return kingdom1.getAllianceStatus(kingdom2.getId()) == AllianceStatus::ALLIED;
}


bool Diplomacy::isAtWar(Kingdom& kingdom1, Kingdom& kingdom2) const {
    return kingdom1.getAllianceStatus(kingdom2.getId()) == AllianceStatus::ENEMY;
}


bool Diplomacy::hasBetrayed(Kingdom& kingdom1, Kingdom& kingdom2) const {
    return kingdom1.getAllianceStatus(kingdom2.getId()) == AllianceStatus::BETRAYED;
}
