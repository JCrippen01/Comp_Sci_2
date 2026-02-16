/**
 * *********************************************************
 * @file cruise.cpp
 * @author 5EA596
 * @date 2026-02-15
 * @brief assignment_4
 * *********************************************************
 */


#include "cruise.h"
#include <iostream>

Cruise::Cruise(const std::string& customerName,
               double basePrice,
               const std::string& shipName,
               const std::string& cabinType)
    : Ticket(customerName, basePrice),
      cabinType(cabinType),
      shipName(shipName)
{
}

void Cruise::printTicket() const
{
    Ticket::printTicket();
    std::cout << "Ship: " << shipName << " | Cabin: " << cabinType << '\n';
}

