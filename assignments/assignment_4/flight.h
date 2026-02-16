/**
 * *********************************************************
 * @file flight.h
 * @author 5EA596
 * @date 2026-02-15
 * @brief assignment_4
 * *********************************************************
 */



#ifndef FLIGHT_H
#define FLIGHT_H

#include "ticket.h"

/**
 * @class Flight
 * @brief Derived ticket type for flight bookings.
 */
class Flight : public Ticket
{
private:
    std::string flightNumber; ///< Flight number (e.g., UA99)
    std::string seatNumber;   ///< Seat number (e.g., 14B)

public:
    /**
     * @brief Construct a Flight ticket with base + flight data.
     * @param customerName Customer full name.
     * @param basePrice Ticket cost.
     * @param flightNumber Flight identifier.
     * @param seatNumber Seat assignment.
     *
     * Uses constructor chaining: Flight(...) : Ticket(name, price) { ... }
     */
    Flight(const std::string& customerName,
           double basePrice,
           const std::string& flightNumber,
           const std::string& seatNumber);

    /**
     * @brief Print ticket info, then flight-specific data.
     * Calls Ticket::printTicket() first.
     */
    void printTicket() const override;
};

#endif
