/**********************************************************
 * *********************************************************
 * @file Cruise.cpp
 * @author 5EA596
 * @course Comp Sci 2
 * @lab Lab 5 - The Abstract Ticket
 * @date 2026-02-22
 * @brief Implements the Cruise class.
 * *********************************************************
 **********************************************************/

#include "Cruise.h"
#include <iostream>

Cruise::Cruise(const std::string& customerName,
               double basePrice,
               const std::string& cabinType,
               const std::string& shipName)
    : Ticket(customerName, basePrice)
{
    this->cabinType = cabinType;
    this->shipName = shipName;
}

void Cruise::printTicket() const
{
    std::cout << "Ship: " << shipName
              << " (" << cabinType << ")" << std::endl;
}