/**
 * @file main.cpp
 * @author 5EA596
 * @date 2026-02-08
 * @brief Driver for Lab 3: The Luggage Tracker. Demonstrates stack vs heap allocation
 *        and correct use of dot (.) vs arrow (->) operators.
 */

#include <iostream>
#include <string>
#include <limits>
#include <iomanip>
#include "5EA596_luggage.h"

int main()
{
    std::cout << "--- Stack Object (bag1) ---\n";

    Luggage bag1; // stack allocation

    std::string ownerInput;
    std::string typeInput;
    double weightInput = 0.0;

    std::cout << "Enter Owner Name: ";
    std::getline(std::cin, ownerInput);

    std::cout << "Enter Weight (lbs): ";
    std::cin >> weightInput;

    // Clear newline before next getline
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    std::cout << "Enter Type: ";
    std::getline(std::cin, typeInput);

    // Dot operator for stack object
    bag1.setOwner(ownerInput);
    bag1.setWeight(weightInput);
    bag1.setType(typeInput);

    std::cout << "Owner: " << bag1.getOwner()
              << " | Oversized Fee: $"
              << std::fixed << std::setprecision(2)
              << bag1.getOversizedFee() << "\n\n";

    std::cout << "--- Heap Object (bag2) ---\n";
    std::cout << "*Creating Bag on Heap...*\n";

    // Heap allocation with parameterized constructor
    Luggage* bag2 = new Luggage("Alice Smith", 65.5, "Checked");

    // Arrow operator for heap object
    std::cout << "Name: " << bag2->getOwner()
              << " | Weight: " << std::fixed << std::setprecision(1) << bag2->getWeight() << " lbs"
              << " | Oversized Fee: $"
              << std::fixed << std::setprecision(2)
              << bag2->getOversizedFee() << "\n";

    std::cout << "*Deleting bag2...*\n";
    delete bag2;
    bag2 = nullptr;

    return 0;
}


