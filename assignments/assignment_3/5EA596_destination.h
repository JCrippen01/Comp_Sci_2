#ifndef DESTINATION_H
#define DESTINATION_H

/**
 * @file Destination.h
 * @author 5EA596
 * @date 2026-02-08
 * @brief Specification for the Destination class used in Assignment 3.
 */

#include <string>

/**
 * @class Destination
 * @brief Represents one itinerary stop with city, days, and daily cost.
 */
class Destination
{
private:
    std::string city;
    int days;
    double dailyCost;

public:
    /**
     * @brief Default constructor sets city="Unknown", days=0, dailyCost=0.0.
     */
    Destination();

    /**
     * @brief Sets the city name.
     * @param city The city for this stop.
     */
    void setCity(const std::string& city);

    /**
     * @brief Sets the number of days. Negative values become 0.
     * @param days Number of days at this destination.
     */
    void setDays(int days);

    /**
     * @brief Sets the daily cost. Negative values become 0.0.
     * @param dailyCost Cost per day.
     */
    void setDailyCost(double dailyCost);

    /**
     * @brief Gets the city name.
     * @return City string.
     */
    std::string getCity() const;

    /**
     * @brief Gets the number of days.
     * @return Days as int.
     */
    int getDays() const;

    /**
     * @brief Gets the daily cost.
     * @return Daily cost.
     */
    double getDailyCost() const;

    /**
     * @brief Returns the total cost for this stop (days * dailyCost).
     * @return Total cost for this destination stop.
     */
    double getStopCost() const;
};

#endif
