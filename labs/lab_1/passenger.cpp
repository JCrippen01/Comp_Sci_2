/**
 * @file Passenger.cpp
 * @author 5EA596
 * @date 2026-02-08
 * @brief Implementation (definitions) for the Passenger class.
 */

#include "Passenger.h"
#include <iostream>

Passenger::Passenger(const std::string& name, const std::string& seatNumber)
{
    this->name = name;
    this->seatNumber = seatNumber;
}

void Passenger::print() const
{
    // Global Roam output specification: display name and seat number clearly.
    std::cout << "Passenger: " << name << " | Seat: " << seatNumber << std::endl;
}
