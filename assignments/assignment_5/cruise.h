/**********************************************************
 * *********************************************************
 * @file Cruise.h
 * @author 5EA596
 * @course Comp Sci 2
 * @assignment Assignment 5 - The Unified Booking Engine
 * @date 2026-02-22
 * @brief Declares the Cruise class derived from Ticket.
 * *********************************************************
 **********************************************************/

#ifndef CRUISE_H
#define CRUISE_H

#include "ticket.h"
#include <string>

class Cruise : public Ticket
{
private:
    std::string shipName;
    std::string cabinType;

public:
    Cruise(const std::string& customerName,
           double basePrice,
           const std::string& shipName,
           const std::string& cabinType);

    void printTicket() const override;
};

#endif