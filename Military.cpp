#include "Stronghold.h"
Military::Military() : soldierCount(0), morale(50.0), foodRequired(0.0), payRequired(0.0) {}
void Military::recruitSoldiers(int count) {
    if (count > 0) {
        soldierCount += count;
        foodRequired += count * 1.5; 
        payRequired += count * 2.0; 
        morale -= count * 0.1;      
        increaseCorruption(count * 0.2); 
        if (morale < 0.0) morale = 0.0;
    }
}
void Military::paySoldiers() {
    if (payRequired > 0) {
        payRequired = 0.0; 
        morale += 10.0;    
        decreaseCorruption(5.0); 
        if (morale > 100.0) morale = 100.0; 
    }
    else {
        morale -= 5.0; 
        increaseCorruption(5.0); 
        if (morale < 0.0) morale = 0.0;
    }
}
void Military::trainSoldiers(int count) {
    if (count > 0 && count <= soldierCount) {
        morale += count * 0.5; 
        decreaseCorruption(count * 0.3); 
        if (morale > 100.0) morale = 100.0; 
    }
}
void Military::manageMorale() {
    if (foodRequired > 0) {
        morale -= 5.0; 
        increaseCorruption(2.0); 
        if (morale < 0.0) morale = 0.0;
    }
    if (isCorrupted()) {
        morale -= corruptionLevel * 0.1; 
        if (morale < 0.0) morale = 0.0;
    }
}
