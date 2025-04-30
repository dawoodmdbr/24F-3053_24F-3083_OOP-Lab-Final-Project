#include "Stronghold.h"

Event::Event() : type(FAMINE), description("Unknown Event"), impact(0) {
    // Default event constructor
}

Event::Event(EventType t, const string& desc, int imp)
    : type(t), description(desc), impact(imp) {
    // Ensure impact is not negative
    if (impact < 0) impact = 0;
}

void Event::update(Kingdom& kingdom) {
    // Events become more impactful when kingdom is unhappy
    if (kingdom.getPopulation().getOverallHappiness() < 50.0) {
        impact += 10;
    }
    
    // Events become more impactful when corruption is high
    if (kingdom.getCorruption().isCorrupted()) {
        impact += 5;
    }
    
    // Trigger the event if impact is significant
    if (impact > 50) {
        triggerEvent();
    }
}

void Event::triggerEvent() {
    cout << "=== EVENT TRIGGERED ===" << endl;
    cout << "Type: ";
    
    switch(type) {
        case PLAGUE:
            cout << "PLAGUE";
            break;
        case FAMINE:
            cout << "FAMINE";
            break;
        case REBELLION:
            cout << "REBELLION";
            break;
        case DISCOVERY_OF_GOLD:
            cout << "DISCOVERY OF GOLD";
            break;
        case NATURAL_DISASTER:
            cout << "NATURAL DISASTER";
            break;
        default:
            cout << "UNKNOWN";
            break;
    }
    
    cout << endl;
    cout << "Description: " << description << endl;
    cout << "Impact: " << impact << endl;
    cout << "=======================" << endl;
}

EventType Event::getType() const {
    return type;
}

string Event::getDescription() const {
    return description;
}

int Event::getImpact() const {
    return impact;
}