/**********************************************************
 * *********************************************************
 * @file Flight.cpp
 * @author 5EA596
 * @course Comp Sci 2
 * @lab Lab 5 - The Abstract Ticket
 * @date 2026-02-22
 * @brief Implements the Flight class.
 * *********************************************************
 **********************************************************/

#include "Flight.h"
#include <iostream>

Flight::Flight(const std::string& customerName,
               double basePrice,
               const std::string& flightNumber,
               const std::string& seatNumber)
    : Ticket(customerName, basePrice)
{
    this->flightNumber = flightNumber;
    this->seatNumber = seatNumber;
}

void Flight::printTicket() const
{
    std::cout << "Flight: " << flightNumber
              << " | Seat: " << seatNumber << std::endl;
}