/**
 * @file Trip.cpp
 * @author 5EA596
 * @date 2026-02-08
 * @brief Implementation for the Trip class.
 */

#include "Trip.h"

Trip::Trip(const std::string& city, const std::string& country, double price)
{
    this->city = city;
    this->country = country;
    this->price = price;
}

std::string Trip::getCity() const
{
    return city;
}

std::string Trip::getCountry() const
{
    return country;
}

double Trip::getPrice() const
{
    return price;
}
