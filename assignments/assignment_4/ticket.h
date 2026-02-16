/**
 * *********************************************************
 * @file ticket.h
 * @author 5EA596
 * @date 2026-02-15
 * @brief assignment_4
 * *********************************************************
 */



#ifndef TICKET_H
#define TICKET_H

#include <string>
#include <iostream>

/**
 * @class Ticket
 * @brief Base class representing a generic booking ticket.
 *
 * Stores shared attributes for all tickets:
 * customerName and basePrice.
 */
class Ticket
{
protected:
    std::string customerName; ///< Customer name (protected for derived access)
    double basePrice;         ///< Base price (protected for derived access)

public:
    /**
     * @brief Construct a Ticket with customer name and base price.
     * @param customerName Customer full name.
     * @param basePrice Ticket cost.
     */
    Ticket(const std::string& customerName, double basePrice);

    /**
     * @brief Print the base ticket information.
     *
     * Derived classes should call Ticket::printTicket() first
     * then print specialized details.
     */
    virtual void printTicket() const;

    /**
     * @brief Virtual destructor for proper cleanup via base pointer.
     */
    virtual ~Ticket() = default;
};

#endif
