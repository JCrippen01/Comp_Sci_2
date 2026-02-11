#ifndef LUGGAGE_H
#define LUGGAGE_H

/**
 * @file Luggage.h
 * @author 5EA596
 * @date 2026-02-08
 * @brief Specification for the Luggage class used in Global Roam Lab 3.
 */

#include <string>

/**
 * @class Luggage
 * @brief Represents a piece of luggage with an owner, weight, and type.
 */
class Luggage
{
private:
    std::string owner;
    double weight;
    std::string type;

public:
    /**
     * @brief Default constructor. Initializes owner="Unknown", weight=0.0, type="Checked".
     */
    Luggage();

    /**
     * @brief Parameterized constructor.
     * @param owner The luggage owner's name.
     * @param weight The luggage weight in pounds.
     * @param type The luggage type (e.g., "Carry-On", "Checked").
     */
    Luggage(const std::string& owner, double weight, const std::string& type);

    /**
     * @brief Sets the owner name.
     * @param owner The new owner name.
     */
    void setOwner(const std::string& owner);

    /**
     * @brief Sets the weight. Negative values are not allowed.
     * @param weight The new weight in pounds.
     */
    void setWeight(double weight);

    /**
     * @brief Sets the luggage type.
     * @param type The new luggage type.
     */
    void setType(const std::string& type);

    /**
     * @brief Returns the oversized fee based on weight.
     * @return 50.0 if weight > 50.0, otherwise 0.0.
     */
    double getOversizedFee() const;

    /**
     * @brief Gets the owner name.
     * @return Owner string.
     */
    std::string getOwner() const;

    /**
     * @brief Gets the luggage weight.
     * @return Weight in pounds.
     */
    double getWeight() const;

    /**
     * @brief Gets the luggage type.
     * @return Type string.
     */
    std::string getType() const;
};

#endif
