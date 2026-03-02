/**********************************************************
 * *********************************************************
 * @file Flight.h
 * @author 5EA596
 * @course Comp Sci 2
 * @lab Lab 5 - The Abstract Ticket
 * @date 2026-02-22
 * @brief Declares the Flight class derived from Ticket.
 * *********************************************************
 **********************************************************/

#ifndef FLIGHT_H
#define FLIGHT_H

#include "ticket.h"
#include <string>

class Flight : public Ticket
{
private:
    std::string flightNumber;
    std::string seatNumber;

public:
    Flight(const std::string& customerName,
           double basePrice,
           const std::string& flightNumber,
           const std::string& seatNumber);

    void printTicket() const override;
};

#endif