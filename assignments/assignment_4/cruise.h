/**
 * *********************************************************
 * @file cruise.h
 * @author 5EA596
 * @date 2026-02-15
 * @brief assignment_4
 * *********************************************************
 */


#ifndef CRUISE_H
#define CRUISE_H

#include "ticket.h"

/**
 * @class Cruise
 * @brief Derived ticket type for cruise bookings.
 */
class Cruise : public Ticket
{
private:
    std::string cabinType; ///< Cabin type (e.g., Balcony)
    std::string shipName;  ///< Ship name (e.g., Oceanic Star)

public:
    /**
     * @brief Construct a Cruise ticket with base + cruise data.
     * @param customerName Customer full name.
     * @param basePrice Ticket cost.
     * @param shipName Ship name.
     * @param cabinType Cabin type.
     *
     * Uses constructor chaining: Cruise(...) : Ticket(name, price) { ... }
     */
    Cruise(const std::string& customerName,
           double basePrice,
           const std::string& shipName,
           const std::string& cabinType);

    /**
     * @brief Print ticket info, then cruise-specific data.
     * Calls Ticket::printTicket() first.
     */
    void printTicket() const override;
};

#endif
