/**********************************************************
 * *********************************************************
 * @file ticket.h
 * @author 5EA596
 * @course Comp Sci 2
 * @assignment Assignment 5 - The Unified Booking Engine
 * @date 2026-02-22
 * @brief Declares the abstract base class Ticket.
 *
 * Ticket represents a generic travel product and cannot
 * be instantiated because it contains a pure virtual function.
 * *********************************************************
 **********************************************************/

#ifndef TICKET_H
#define TICKET_H

#include <string>

class Ticket
{
protected:
    std::string customerName;
    double basePrice;

public:
    Ticket(const std::string& customerName, double basePrice);
    virtual ~Ticket();

    virtual void printTicket() const = 0;
};

#endif