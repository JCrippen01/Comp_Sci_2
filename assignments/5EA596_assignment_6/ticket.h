#ifndef TICKET_H
#define TICKET_H

#include <iostream>
#include <string>

/**
 * @brief Represents a Global Roam ticket object.
 */
class Ticket {
private:
    int ticketId;
    std::string passengerName;

public:
    /**
     * @brief Default constructor.
     */
    Ticket() {
        ticketId = 0;
        passengerName = "";
    }

    /**
     * @brief Constructs a Ticket object.
     * @param id Ticket ID number.
     * @param name Passenger name.
     */
    Ticket(int id, std::string name) {
        ticketId = id;
        passengerName = name;
    }

    /**
     * @brief Prints ticket information.
     * @param os Output stream.
     * @param ticket Ticket object to print.
     * @return std::ostream& Updated output stream.
     */
    friend std::ostream& operator<<(std::ostream& os, const Ticket& ticket) {
        os << "Ticket ID: " << ticket.ticketId
           << ", Passenger: " << ticket.passengerName;
        return os;
    }
};

#endif