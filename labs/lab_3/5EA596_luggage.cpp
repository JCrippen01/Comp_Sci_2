/**
 * @file Luggage.cpp
 * @author 5EA596
 * @date 2026-02-08
 * @brief Implementation for the Luggage class used in Global Roam Lab 3.
 */

#include "5EA596_luggage.h"

Luggage::Luggage()
{
    owner = "Unknown";
    weight = 0.0;
    type = "Checked";
}

Luggage::Luggage(const std::string& owner, double weight, const std::string& type)
{
    this->owner = owner;
    setWeight(weight);   // ensures validation
    this->type = type;
}

void Luggage::setOwner(const std::string& owner)
{
    this->owner = owner;
}

void Luggage::setWeight(double weight)
{
    if (weight < 0.0)
        this->weight = 0.0;
    else
        this->weight = weight;
}

void Luggage::setType(const std::string& type)
{
    this->type = type;
}

double Luggage::getOversizedFee() const
{
    if (weight > 50.0)
        return 50.0;
    return 0.0;
}

std::string Luggage::getOwner() const
{
    return owner;
}

double Luggage::getWeight() const
{
    return weight;
}

std::string Luggage::getType() const
{
    return type;
}
