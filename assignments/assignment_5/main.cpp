/**********************************************************
 * *********************************************************
 * @file main.cpp
 * @author 5EA596
 * @course Comp Sci 2
 * @assignment Assignment 5 - The Unified Booking Engine
 * @date 2026-02-22
 * @brief Menu-driven program demonstrating polymorphism.
 * *********************************************************
 **********************************************************/

#include <iostream>
#include <vector>
#include "ticket.h"
#include "flight.h"
#include "cruise.h"

/*
Reflection:
If we used vector<Ticket> instead of vector<Ticket*>,
object slicing would occur. When a derived object
(Flight or Cruise) is copied into a base object,
only the Ticket portion remains. The derived-specific
data is sliced off. As a result, the polymorphic loop
would call Ticket’s version (if it existed) and lose
the specialized behavior. Using pointers preserves the
true object type and allows runtime polymorphism
through virtual function dispatch.
*/

int main()
{
    std::vector<Ticket*> itinerary;

    itinerary.push_back(new Flight("John Doe", 400.00, "UA99", "14B"));
    itinerary.push_back(new Cruise("Diana Prince", 1250.00, "Oceanic Star", "Balcony"));

    std::cout << "Polymorphic Output\n";

    for (size_t i = 0; i < itinerary.size(); i++)
    {
        std::cout << "\nTicket " << i + 1 << ":\n";
        itinerary[i]->printTicket();
    }

    for (Ticket* t : itinerary)
    {
        delete t;
    }

    itinerary.clear();
    return 0;
}