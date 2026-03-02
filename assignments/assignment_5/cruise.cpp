/**********************************************************
 * *********************************************************
 * @file Cruise.cpp
 * @author 5EA596
 * @course Comp Sci 2
 * @assignment Assignment 5 - The Unified Booking Engine
 * @date 2026-02-22
 * @brief Implements the Cruise class.
 * *********************************************************
 **********************************************************/

#include "cruise.h"
#include <iostream>
#include <iomanip>

Cruise::Cruise(const std::string& customerName,
               double basePrice,
               const std::string& shipName,
               const std::string& cabinType)
    : Ticket(customerName, basePrice)
{
    this->shipName = shipName;
    this->cabinType = cabinType;
}

void Cruise::printTicket() const
{
    std::cout << "Ship: " << shipName
              << " (" << cabinType << ")"
              << "\nCustomer: " << customerName
              << " | Price: $" << std::fixed << std::setprecision(2)
              << basePrice << std::endl;
}