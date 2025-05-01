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
    int impact = rand() % 21 + 10; // 10 to 30 impact

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
        case TAX_EVASION_SCANDAL:
            description = "Nobles caught hiding wealth in offshore vaults.";
            break;
        case MERCHANTS_STRIKE:
            description = "Merchants halt trade demanding lower tariffs.";
            break;
        case DRAGON_SIGHTING:
            description = "A dragon was seen in the mountains. Panic spreads.";
            break;
        case COMEDY_FESTIVAL:
            description = "A traveling troupe hosts a comedy festival. Laughter everywhere.";
            break;
        case ASTRONOMICAL_EVENT:
            description = "A rare comet lights the sky. Peasants think it’s magic.";
            break;
        default:
            description = "An unknown event occurred.";
            break;
    }

    events[eventCount++] = Event(type, description, impact);
    cout << "New event generated: " << description << " [Impact: " << impact << "]\n";
}

void EventManager::handleEvent(Kingdom& kingdom, Event& event) {
    cout << "Handling event: " << event.getDescription() << "\n";
    switch (event.getType()) {
        case PLAGUE:
            kingdom.getPopulation().affectHealth(-event.getImpact());
            break;
        case FAMINE:
            kingdom.getEconomy().adjustTaxRate(-0.1 * event.getImpact() / 100.0);
            break;
        case REBELLION:
            kingdom.getLeadership().initiateCoup(kingdom);
            break;
        case DISCOVERY_OF_GOLD:
            kingdom.getBank().issueLoan(event.getImpact());
            break;
        case NATURAL_DISASTER:
            kingdom.getPopulation().affectHealth(-event.getImpact());
            break;
        case TAX_EVASION_SCANDAL:
            kingdom.getBank().deductGold(event.getImpact());
            break;
        case MERCHANTS_STRIKE:
            kingdom.getResourceManager().haltResource(ResourceType::Gold, 2);  // example method
            break;
        case DRAGON_SIGHTING:
            kingdom.getMilitary().increaseReadiness(10);
            break;
        case COMEDY_FESTIVAL:
            kingdom.getPopulation().adjustHappiness(AllClasses, +5);
            break;
        case ASTRONOMICAL_EVENT:
            kingdom.getLeadership().gainWisdom(3);
            break;
        default:
            cout << "Unknown event type.\n";
            break;
    }
}

Event EventManager::getLatestEvent() const {
    if (eventCount > 0) {
        return events[eventCount - 1]; // Return the latest event
    } else {
        cout << "No events available.\n";
        return Event(); // Return a default event if none exist
    }
}
void EventManager::applyEvent(Event& event) {
    cout << "Applying event...\n";
    event.triggerEvent();

}

void EventManager::update(Kingdom& kingdom) {
    // Update logic for events, if needed
    for (int i = 0; i < eventCount; ++i) {
        events[i].update(kingdom);
    }
}