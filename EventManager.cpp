#include "Stronghold.h"
#include <cstdlib>
#include <ctime>

EventManager::EventManager() {
    // Seed random number generator
    srand(static_cast<unsigned int>(time(nullptr)));
}

void EventManager::update(Kingdom& kingdom) {
    // Update all existing events
    for (Event& event : events) {
        event.update(kingdom);
    }
    
    // Random chance to generate a new event
    if (rand() % 100 < 10) { // 10% chance each update
        generateRandomEvent();
    }
}

void EventManager::generateRandomEvent() {
    // Generate a random event type
    EventType type = static_cast<EventType>(rand() % EVENT_TYPE_COUNT);
    string description;
    int impact = rand() % 21 + 10; // Random impact between 10 and 30
    
    // Set description based on type
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
    
    // Create and add the new event
    events.push_back(Event(type, description, impact));
    
    cout << "New event generated: " << description << " [Impact: " << impact << "]" << endl;
}

Event EventManager::getLatestEvent() const {
    if (events.empty()) {
        return Event(); // Return default event if none exist
    }
    return events.back(); // Return the most recent event
}

void EventManager::applyEvent(Event& event) {
    cout << "Applying event: " << event.getDescription() << endl;
    event.triggerEvent();
}

void EventManager::handleEvent(Kingdom& kingdom, Event& event) {
    cout << "Handling event: " << event.getDescription() << endl;
    
    // Apply effects based on event type
    switch (event.getType()) {
        case PLAGUE:
            kingdom.getPopulation().affectHealth(-event.getImpact());
            break;
            
        case FAMINE:
            // Reduce food resources
            kingdom.getResourceManager().consume(FOOD, event.getImpact() * 10);
            // Reduce population happiness
            kingdom.getPopulation().adjustHappiness(PEASANT, -event.getImpact() * 0.1);
            break;
            
        case REBELLION:
            // Reduce leader popularity
            kingdom.getLeadership().affectPopularity(-event.getImpact());
            // Potentially trigger a coup if impact is severe
            if (event.getImpact() > 20) {
                kingdom.getLeadership().initiateCoup(kingdom);
            }
            break;
            
        case DISCOVERY_OF_GOLD:
            // Increase gold resources
            kingdom.getResourceManager().gather(GOLD, event.getImpact() * 20);
            break;
            
        case NATURAL_DISASTER:
            // Damage to multiple resources
            kingdom.getResourceManager().consume(FOOD, event.getImpact() * 5);
            kingdom.getResourceManager().consume(WOOD, event.getImpact() * 3);
            kingdom.getResourceManager().consume(STONE, event.getImpact() * 2);
            break;
            
        default:
            cout << "Unknown event type, no effects applied." << endl;
            break;
    }
}

int EventManager::getEventCount() const {
    return static_cast<int>(events.size());
}
