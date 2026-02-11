#ifndef PASSENGER_H
#define PASSENGER_H

/**
 * @file Passenger.h
 * @author 5EA596
 * @date 2026-02-08
 * @brief Specification (declarations) for the Passenger class used in Global Roam systems.
 */

#include <string>

/**
 * @class Passenger
 * @brief Represents a passenger with a name and seat number.
 */
class Passenger
{
private:
    std::string name;
    std::string seatNumber;

public:
    /**
     * @brief Constructs a Passenger with a name and seat number.
     * @param name The passenger's full name.
     * @param seatNumber The passenger's seat number (e.g., "12A").
     */
    Passenger(const std::string& name, const std::string& seatNumber);

    /**
     * @brief Prints the passenger information in Global Roam format.
     */
    void print() const;
};

#endif
