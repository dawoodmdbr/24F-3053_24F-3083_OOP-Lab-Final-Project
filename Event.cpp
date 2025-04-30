#include <iostream>
#include "Stronghold.h"
using namespace std;
Event::Event(): description(""), impact(0) {}
Event::Event(string description, int impact): description(description), impact(impact) {}
void Event::triggerEvent() {
    cout << "Event triggered: " << description << " with impact: " << impact << endl;
}
