/**********************************************************
 * *********************************************************
 * @file Ticket.cpp
 * @author 5EA596
 * @course Comp Sci 2
 * @lab Lab 5 - The Abstract Ticket
 * @date 2026-02-22
 * @brief Implements Ticket constructor and destructor.
 * *********************************************************
 **********************************************************/

#include "ticket.h"

Ticket::Ticket(const std::string& customerName, double basePrice)
{
    this->customerName = customerName;
    this->basePrice = basePrice;
}

Ticket::~Ticket() = default;