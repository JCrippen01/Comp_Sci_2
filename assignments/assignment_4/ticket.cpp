/**
 * *********************************************************
 * @file ticket.cpp
 * @author 5EA596
 * @date 2026-02-15
 * @brief assignment_4
 * *********************************************************
 */



#include "ticket.h"
#include <iomanip>

Ticket::Ticket(const std::string& customerName, double basePrice)
    : customerName(customerName), basePrice(basePrice)
{
}

void Ticket::printTicket() const
{
    std::cout << "Ticket for " << customerName
              << " -- Cost: $" << std::fixed << std::setprecision(2)
              << basePrice << '\n';
}
