/**********************************************************
 * *********************************************************
 * @file Cruise.h
 * @author 5EA596
 * @course Comp Sci 2
 * @lab Lab 5 - The Abstract Ticket
 * @date 2026-02-22
 * @brief Declares the Cruise class derived from Ticket.
 * *********************************************************
 **********************************************************/

#ifndef CRUISE_H
#define CRUISE_H

#include "Ticket.h"
#include <string>

class Cruise : public Ticket
{
private:
    std::string cabinType;
    std::string shipName;

public:
    Cruise(const std::string& customerName,
           double basePrice,
           const std::string& cabinType,
           const std::string& shipName);

    void printTicket() const override;
};

#endif