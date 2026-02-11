#ifndef TRIP_H
#define TRIP_H

/**
 * @file Trip.h
 * @author 5EA596
 * @date 2026-02-08
 * @brief Specification for the Trip class used by Global Roam Destination Loader.
 */

#include <string>

/**
 * @class Trip
 * @brief Stores one travel package record (city, country, and price).
 */
class Trip
{
private:
    std::string city;
    std::string country;
    double price;

public:
    /**
     * @brief Constructs a Trip with city, country, and price.
     * @param city The destination city.
     * @param country The destination country.
     * @param price The package price.
     */
    Trip(const std::string& city, const std::string& country, double price);

    /**
     * @brief Gets the destination city.
     * @return The city string.
     */
    std::string getCity() const;

    /**
     * @brief Gets the destination country.
     * @return The country string.
     */
    std::string getCountry() const;

    /**
     * @brief Gets the package price.
     * @return The price as a double.
     */
    double getPrice() const;
};

#endif