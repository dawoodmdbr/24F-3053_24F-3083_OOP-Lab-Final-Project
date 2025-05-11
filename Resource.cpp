#include "Stronghold.h"
#include <iostream>
using namespace std;
Resource::Resource() : type(RESOURCE_TYPE_COUNT), amount(0), maxAmount(100) {}
Resource::Resource(ResourceType type, double amount, double max) : type(type), amount(amount), maxAmount(max) {}
void Resource::gather(double a)
{
    if (amount + a > maxAmount)
    {
        cout << "Resource limit reached. Cannot gather more.\n";
        amount = maxAmount;
    }
    else
    {
        this->amount += a;
    }
}

void Resource::consume(double a)
{
    if (amount - a < 0)
    {
        cout << "Not enough resources to consume.\n";
        amount = 0;
    }
    else
    {
        this->amount -= a;
    }
}
void Resource::trade(double a)
{
    if (amount - a < 0)
    {
        cout << "Not enough resources to trade.\n";
    }
    else
    {
        this->amount -= a;
    }
}
ResourceType Resource::getType() const
{
    return this->type;
}
double Resource::getAmount() const
{
    return this->amount;
}
void Resource::setAmount(double amt)
{
    this->amount = amt;
}
void Resource::update(Kingdom &kingdom)
{
    if (kingdom.getEconomy().getTaxRate() > 0.5)
    {
        amount -= 0.1 * amount;
    }
    if (kingdom.getPopulation().getOverallHappiness() < 50)
    {
        amount -= 0.05 * amount;
    }
}
double Resource::getMaxAmount() const
{
    return this->maxAmount;
}