/**********************************************************
 * *********************************************************
 * @file Flight.cpp
 * @author 5EA596
 * @course Comp Sci 2
 * @assignment Assignment 5 - The Unified Booking Engine
 * @date 2026-02-22
 * @brief Implements the Flight class.
 * *********************************************************
 **********************************************************/

#include "flight.h"
#include <iostream>
#include <iomanip>

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
              << " | Seat: " << seatNumber
              << "\nCustomer: " << customerName
              << " | Price: $" << std::fixed << std::setprecision(2)
              << basePrice << std::endl;
}