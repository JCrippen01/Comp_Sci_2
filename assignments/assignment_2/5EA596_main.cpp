/**
 * @file main.cpp
 * @author 5EA596
 * @date 2026-02-06
 * @brief Assignment 2 - Destination Loader: reads destinations.txt, parses CSV lines,
 *        loads Trip objects into a vector, and displays available travel packages.
 */

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>

#include "Trip.h"

/**
 * @brief Returns true if the string looks like a valid non-negative decimal number.
 *        (Digits with optional single decimal point.)
 * @param text The price text extracted from the file.
 * @return True if valid; otherwise false.
 */
bool isValidPriceText(const std::string& text)
{
    if (text.size() == 0)
        return false;

    bool sawDot = false;
    for (size_t i = 0; i < text.size(); i++)
    {
        char c = text[i];

        if (c == '.')
        {
            if (sawDot)
                return false;
            sawDot = true;
        }
        else if (c < '0' || c > '9')
        {
            return false;
        }
    }
    return true;
}

int main()
{
    const std::string fileName = "destinations.txt";
    std::ifstream inFile(fileName.c_str());

    std::cout << "--- Global Roam System: Loading Data ---\n";

    // File Safety: verify file opens
    if (!inFile)
    {
        std::cout << "ERROR: Unable to open '" << fileName << "'.\n";
        std::cout << "TIP: Place destinations.txt in the same folder as your .cpp files\n";
        std::cout << "     or set Working Directory to $(ProjectDir) in Project Properties > Debugging.\n";
        return 1;
    }

    std::vector<Trip> trips;
    std::string line;

    int badLineCount = 0;

    // Required pattern: read line-by-line until EOF
    while (std::getline(inFile, line))
    {
        // Skip empty lines safely
        if (line.size() == 0)
            continue;

        // Find commas
        size_t comma1 = line.find(',');
        if (comma1 == std::string::npos)
        {
            badLineCount++;
            continue;
        }

        size_t comma2 = line.find(',', comma1 + 1);
        if (comma2 == std::string::npos)
        {
            badLineCount++;
            continue;
        }

        // Extract parts using substr
        std::string city = line.substr(0, comma1);
        std::string country = line.substr(comma1 + 1, comma2 - (comma1 + 1));
        std::string priceStr = line.substr(comma2 + 1);

        // Basic format validation for numeric conversion safety
        if (!isValidPriceText(priceStr))
        {
            badLineCount++;
            continue;
        }

        // Required conversion: stod()
        double price = std::stod(priceStr);

        Trip t(city, country, price);
        trips.push_back(t);
    }

    inFile.close();

    std::cout << "Successfully loaded " << trips.size() << " destinations.\n";
    if (badLineCount > 0)
        std::cout << "Note: Skipped " << badLineCount << " malformed line(s).\n";

    std::cout << "\n--- Available Travel Packages ---\n";

    for (size_t i = 0; i < trips.size(); i++)
    {
        std::cout << (i + 1) << ". "
                  << trips[i].getCity() << ", " << trips[i].getCountry()
                  << " ($" << std::fixed << std::setprecision(2) << trips[i].getPrice() << ")\n";
    }

    return 0;
}
