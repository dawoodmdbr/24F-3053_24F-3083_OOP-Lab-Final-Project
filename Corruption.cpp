#include "Stronghold.h"
Corruption::Corruption() : corruptionLevel(10.0) {}
void Corruption::increaseCorruption(double amount) {
    corruptionLevel += amount;
    if (corruptionLevel > 100.0) {
        corruptionLevel = 100.0;
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
    return corruptionLevel > 50.0; 
}
