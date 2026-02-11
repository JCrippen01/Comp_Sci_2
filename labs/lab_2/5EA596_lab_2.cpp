/**
 * @file 5EA596_lab2.cpp
 * @author 5EA596
 * @date 2026-02-04
 * @brief Lab 2 - The Flight Logger (File I/O). Appends departure/arrival logs to flight_log.txt.
 */

#include <iostream>
#include <fstream>
#include <string>
#include <limits>

int main()
{
    const std::string fileName = "flight_log.txt";

    int choice = 0;

    do
    {
        std::cout << "\n=== Global Roam Ground Control: Flight Logger ===\n";
        std::cout << "1. Log a Departure\n";
        std::cout << "2. Log an Arrival\n";
        std::cout << "3. Quit\n";
        std::cout << "Enter choice: ";

        std::cin >> choice;

        // Buffer management: clear newline left by cin >> before any getline()
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        if (choice == 1)
        {
            std::string flightNumber;
            std::string destination;

            std::cout << "Enter Flight Number: ";
            std::getline(std::cin, flightNumber);

            std::cout << "Enter Destination: ";
            std::getline(std::cin, destination);

            std::ofstream outFile(fileName, std::ios::app);
            if (!outFile)
            {
                std::cout << "Error: Could not open " << fileName << " for writing.\n";
            }
            else
            {
                outFile << "DEPARTURE: " << flightNumber << " to " << destination << "\n";
                outFile.close(); // explicit close for rubric
                std::cout << "Logged departure.\n";
            }
        }
        else if (choice == 2)
        {
            std::string flightNumber;
            std::string origin;

            std::cout << "Enter Flight Number: ";
            std::getline(std::cin, flightNumber);

            std::cout << "Enter Origin: ";
            std::getline(std::cin, origin);

            std::ofstream outFile(fileName, std::ios::app);
            if (!outFile)
            {
                std::cout << "Error: Could not open " << fileName << " for writing.\n";
            }
            else
            {
                outFile << "ARRIVAL: " << flightNumber << " from " << origin << "\n";
                outFile.close(); // explicit close for rubric
                std::cout << "Logged arrival.\n";
            }
        }
        else if (choice == 3)
        {
            std::cout << "Quitting...\n";
        }
        else
        {
            std::cout << "Invalid choice. Please enter 1, 2, or 3.\n";
        }

    } while (choice != 3);

    return 0;
}
