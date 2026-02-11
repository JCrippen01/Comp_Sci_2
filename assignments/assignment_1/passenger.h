#ifndef PASSENGER_H
#define PASSENGER_H

/*
@file Passenger.cpp
@author 5EA596
@date 2026-02-08
@brief Implementation file for the Passenger class.
*/

#include <string>

class Passenger
{
private:
    std::string name;
    std::string seat;
    double ticketPrice;

public:
    // Parameterized constructor
    Passenger(const std::string& name, const std::string& seat, double ticketPrice);

    // Copy constructor (Senior Engineer Challenge)
    Passenger(const Passenger& other);

    // Getters
    std::string getName() const;
    std::string getSeat() const;
    double getTicketPrice() const;

    // Display
    void display() const;
};

#endif
