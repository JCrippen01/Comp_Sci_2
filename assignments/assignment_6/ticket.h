#ifndef TICKET_H
#define TICKET_H

#include <string>

/**
 * @brief A simple Ticket class used to test CargoBin with a user-defined type.
 */
class Ticket
{
private:
    std::string customerName;
    double basePrice;

public:
    /**
     * @brief Constructs a Ticket.
     * @param name Customer name
     * @param price Ticket price
     */
    Ticket(const std::string& name = "", double price = 0.0)
    {
        customerName = name;
        basePrice = price;
    }

    std::string getCustomerName() const
    {
        return customerName;
    }

    double getBasePrice() const
    {
        return basePrice;
    }
};

#endif