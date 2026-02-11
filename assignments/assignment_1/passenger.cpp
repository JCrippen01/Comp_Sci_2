/*
 @file Passenger.cpp
 @author 5EA596
 @date 2026-02-04
 @brief Implementation file for the Passenger class. 
*/

#include "Passenger.h"
#include <iostream>
#include <iomanip>

Passenger::Passenger(const std::string& name, const std::string& seat, double ticketPrice)
    : name(name), seat(seat), ticketPrice(ticketPrice)
{
}

Passenger::Passenger(const Passenger& other)
    : name(other.name), seat(other.seat), ticketPrice(other.ticketPrice)
{
    std::cout << "[SYSTEM] Warning: Passenger object copied." << std::endl;
}

std::string Passenger::getName() const
{
    return name;
}

std::string Passenger::getSeat() const
{
    return seat;
}

double Passenger::getTicketPrice() const
{
    return ticketPrice;
}

void Passenger::display() const
{
    std::cout << std::left
              << std::setw(22) << name
              << std::setw(10) << seat
              << "$" << std::fixed << std::setprecision(2) << ticketPrice
              << std::endl;
}
