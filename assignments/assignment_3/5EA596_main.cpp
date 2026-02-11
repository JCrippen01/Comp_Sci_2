/**
 * @file main.cpp
 * @author 5EA596
 * @date 2026-02-08
 * @brief Assignment 3 - Dynamic Itinerary Builder. Allocates an array of Destination
 *        objects using new[] and releases memory using delete[].
 */

#include <iostream>
#include <string>
#include <limits>
#include <iomanip>

#include "5EA596_destination.h"

int main()
{
    std::cout << "--- Global Roam: Dynamic Itinerary Builder ---\n";

    int stopCount = 0;
    std::cout << "How many stops are in your itinerary? ";
    std::cin >> stopCount;

    // Basic input safety for negative stopCount (not required, but safe)
    if (stopCount < 0)
        stopCount = 0;

    // Clear newline before getline()
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    // Dynamic allocation (required)
    Destination* itinerary = new Destination[stopCount];

    for (int i = 0; i < stopCount; i++)
    {
        std::string cityInput;
        int daysInput = 0;
        double dailyCostInput = 0.0;

        std::cout << "\n--- Stop " << (i + 1) << " ---\n";
        std::cout << "Enter City: ";
        std::getline(std::cin, cityInput);

        std::cout << "Enter Days: ";
        std::cin >> daysInput;

        std::cout << "Enter Daily Cost: ";
        std::cin >> dailyCostInput;

        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        // Array notation uses DOT because [i] dereferences the pointer
        itinerary[i].setCity(cityInput);
        itinerary[i].setDays(daysInput);
        itinerary[i].setDailyCost(dailyCostInput);
    }

    std::cout << "\n--- Final Itinerary Report ---\n";
    double totalTripCost = 0.0;

    for (int i = 0; i < stopCount; i++)
    {
        double stopCost = itinerary[i].getStopCost();
        totalTripCost += stopCost;

        std::cout << (i + 1) << ". " << itinerary[i].getCity()
                  << " (" << itinerary[i].getDays() << " days @ $"
                  << std::fixed << std::setprecision(2) << itinerary[i].getDailyCost()
                  << "/day) -> Stop Cost: $"
                  << std::fixed << std::setprecision(2) << stopCost
                  << "\n";
    }

    std::cout << "TOTAL TRIP COST: $"
              << std::fixed << std::setprecision(2)
              << totalTripCost << "\n";

    // Cleanup (required)
    delete[] itinerary;
    itinerary = nullptr;

    // Rubric requirement: confirm deletion via console message
    std::cout << "[SYSTEM] Itinerary memory freed (delete[] confirmed).\n";

    return 0;
}
