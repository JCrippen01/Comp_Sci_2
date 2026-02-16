/**
 * *********************************************************
 * @file flight.cpp
 * @author 5EA596
 * @date 2026-02-15
 * @brief assignment_4
 * *********************************************************
 */



#include "flight.h"
#include <iostream>

Flight::Flight(const std::string& customerName,
               double basePrice,
               const std::string& flightNumber,
               const std::string& seatNumber)
    : Ticket(customerName, basePrice),
      flightNumber(flightNumber),
      seatNumber(seatNumber)
{
}

void Flight::printTicket() const
{
    Ticket::printTicket();
    std::cout << "Flight: " << flightNumber << " | Seat: " << seatNumber << '\n';
}
