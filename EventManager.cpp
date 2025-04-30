#include "Stronghold.h"
#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

EventManager::EventManager() : eventCount(0) {
    srand(time(0)); // Seed random number generator
}

void EventManager::generateRandomEvent() {
    if (eventCount >= 10) {
        cout << "Event queue full. Cannot generate more events.\n";
        return;
    }

    EventType type = static_cast<EventType>(rand() % EVENT_TYPE_COUNT);
    string description;
    int impact = rand() % 21 + 10; // Random impact between 10 and 30

    switch (type) {
        case PLAGUE:
            description = "A deadly plague spreads through the kingdom.";
            break;
        case FAMINE:
            description = "A famine has caused widespread hunger.";
            break;
        case REBELLION:
            description = "A rebellion rises against the ruling class.";
            break;
        case DISCOVERY_OF_GOLD:
            description = "A rich vein of gold has been discovered.";
            break;
        case NATURAL_DISASTER:
            description = "A terrible natural disaster has struck.";
            break;
        default:
            description = "An unknown event occurred.";
            break;
    }

    events[eventCount++] = Event(type, description, impact);
    cout << "New event generated: " << description << " [Impact: " << impact << "]\n";
}

void EventManager::applyEvent(Event& event) {
    cout << "Applying event...\n";
    event.triggerEvent();
    //full functionality in phase 2 for kingdom
}
