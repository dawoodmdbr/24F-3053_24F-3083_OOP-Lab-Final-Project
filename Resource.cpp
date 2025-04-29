#include "Stronghold.h"
using namespace std;
Resource::Resource(ResourceType type, double amount) : type(type), amount(amount) {}
void Resource::gather(double a) {
    this->amount += a;
}
void Resource::consume(double a) {
    this->amount -= a;
}
void Resource::trade(double a) {
    this->amount -= a;
}
ResourceType Resource::getType() const {
    return this->type;
}
double Resource::getAmount() const {
    return this->amount;
}