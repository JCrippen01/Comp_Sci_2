/**
 * @file Destination.cpp
 * @author 5EA596
 * @date 2026-02-08
 * @brief Implementation for the Destination class used in Assignment 3.
 */

#include "5EA596_destination.h"

Destination::Destination()
{
    city = "Unknown";
    days = 0;
    dailyCost = 0.0;
}

void Destination::setCity(const std::string& city)
{
    this->city = city;
}

void Destination::setDays(int days)
{
    if (days < 0)
        this->days = 0;
    else
        this->days = days;
}

void Destination::setDailyCost(double dailyCost)
{
    if (dailyCost < 0.0)
        this->dailyCost = 0.0;
    else
        this->dailyCost = dailyCost;
}

std::string Destination::getCity() const
{
    return city;
}

int Destination::getDays() const
{
    return days;
}

double Destination::getDailyCost() const
{
    return dailyCost;
}

double Destination::getStopCost() const
{
    return days * dailyCost;
}
