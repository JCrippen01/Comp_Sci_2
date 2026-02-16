/**
 * *********************************************************
 * @file main.cpp
 * @author 5EA596
 * @date 2026-02-15
 * @brief assignment_4
 * *********************************************************
 */



#include "flight.h"
#include "cruise.h"
#include <iostream>

int main()
{
    // Required test data sets
    Flight flight1("Oliver Queen", 400.00, "UA99", "14B");
    Cruise cruise1("Diana Prince", 1250.00, "Oceanic Star", "Balcony");
    Flight flight2("Leroy Jenkins", 750.50, "BA202", "02A");
    Cruise cruise2("Arthur Curry", 2100.00, "Atlantis Queen", "Royal Suite");

    std::cout << "--- Flight Booking ---\n";
    flight1.printTicket();

    std::cout << "\n--- Cruise Booking ---\n";
    cruise1.printTicket();

    std::cout << "\n--- Flight Booking ---\n";
    flight2.printTicket();

    std::cout << "\n--- Cruise Booking ---\n";
    cruise2.printTicket();

    return 0;
}
