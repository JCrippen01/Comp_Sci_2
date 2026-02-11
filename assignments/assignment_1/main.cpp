/*
   @file main.cpp
   @author 5EA596
   @date 2026-02-04
   @brief Driver program for the Flight Manifest assignment.

    Assignment Summary:
    This program implements a flight manifest management system using object-oriented
    design principles. Passenger data is encapsulated within a Passenger class, and a
    std::vector is used to store an expandable list of passengers as they are entered
    at runtime.

    The program demonstrates proper input buffer management when mixing cin >> and
    getline() by explicitly clearing the input buffer using cin.ignore() after numeric
    input. This prevents skipped input and ensures reliable user interaction.

    A custom copy constructor is included to observe object copying behavior when
    Passenger objects are stored in a vector. During output, passengers are accessed
    using const references to prevent unnecessary copies, improving efficiency and
    avoiding extra copy constructor calls.

    The program also calculates and displays total ticket revenue by summing all
    passenger ticket prices.
*/

#include <iostream>
#include <vector>
#include <string>
#include <limits>
#include <iomanip>
#include "Passenger.h"

int main()
{
    std::vector<Passenger> manifest;
    double totalRevenue = 0.0;

    std::cout << "Global Roam - Flight Manifest System\n\n";

    while (true)
    {
        std::string name;
        std::string seat;
        double price = 0.0;

        std::cout << "Enter passenger name: ";
        std::getline(std::cin, name);

        std::cout << "Enter seat (e.g., 12A): ";
        std::getline(std::cin, seat);

        std::cout << "Enter ticket price: ";
        std::cin >> price;

        // REQUIREMENT: clear the newline left behind by cin >> before the next getline()
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        Passenger p(name, seat, price);

        // May trigger copies due to vector reallocation / growth
        manifest.push_back(p);

        // Revenue requirement
        totalRevenue += price;

        char choice;
        std::cout << "Add another passenger? (y/n): ";
        std::cin >> choice;

        // Clear newline before next getline
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        if (choice != 'y' && choice != 'Y')
            break;

        std::cout << "\n";
    }

    std::cout << "\n--- FLIGHT MANIFEST ---\n";
    std::cout << "Name                  Seat      Price\n";
    std::cout << "-------------------------------------------\n";

    // BONUS EXPLANATION:
    // Using const references prevents extra copies of Passenger objects.
    // If we wrote: for (Passenger p : manifest) each element would be copied
    // into p, triggering the copy constructor once per iteration.
    for (const Passenger& p : manifest)
    {
        p.display();
    }

    std::cout << "-------------------------------------------\n";
    std::cout << "Total Revenue: $"
              << std::fixed << std::setprecision(2)
              << totalRevenue << std::endl;

    return 0;
}
