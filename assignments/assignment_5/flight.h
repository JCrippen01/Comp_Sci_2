/**********************************************************
 * *********************************************************
 * @file Flight.h
 * @author 5EA596
 * @course Comp Sci 2
 * @assignment Assignment 5 - The Unified Booking Engine
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
    /**
     * @brief Constructs a Flight ticket.
     * @param customerName Customer name
     * @param basePrice Ticket price
     * @param flightNumber Flight number
     * @param seatNumber Seat number
     *
     * [AI CITATION] I received assistance understanding how to properly
     * structure and chain this derived constructor using an initializer list.
     */
    Flight(const std::string& customerName,
           double basePrice,
           const std::string& flightNumber,
           const std::string& seatNumber);

    void printTicket() const override;
};

#endif