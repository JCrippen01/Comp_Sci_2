/**********************************************************
 * *********************************************************
 * @file ticket.h
 * @author 5EA596
 * @course Comp Sci 2
 * @lab Lab 5 - The Abstract Ticket
 * @date 2026-02-22
 * @brief Declares the abstract base class Ticket.
 *
 * Ticket represents a general booking product in Global Roam.
 * It is abstract because customers cannot purchase a generic Ticket.
 * Only specific ticket types such as Flight or Cruise can be instantiated.
 * *********************************************************
 **********************************************************/

#ifndef TICKET_H
#define TICKET_H

#include <string>

/**
 * @class Ticket
 * @brief Abstract base class for all ticket types.
 */
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