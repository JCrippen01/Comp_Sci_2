/*
 * Author: 5EA596
 * Course: CISP-1020 Computer Science II
 * Institution: Volunteer State Community College
 * Term: Spring 2026
 *
 * Midterm Practice: Abstract Base Class
 *
 * Description:
 * The Ticket class is an ABSTRACT base class because it
 * contains a pure virtual function. The Flight class
 * derives from Ticket and overrides the printTicket()
 * function.
 */

#include <iostream>
#include <string>

using namespace std;

/**
 * Abstract Base Class
 */
class Ticket
{
protected:
    string customerName;
    double basePrice;

public:
    // Constructor
    Ticket(const string& name, double price)
    {
        customerName = name;
        basePrice = price;
    }

    // Virtual Destructor
    virtual ~Ticket() {}

    // Pure Virtual Function
    virtual void printTicket() const = 0;
};

/**
 * Derived Class
 */
class Flight : public Ticket
{
private:
    string flightNumber;

public:
    // Constructor using base constructor
    Flight(const string& name,
           double price,
           const string& number)
        : Ticket(name, price)
    {
        flightNumber = number;
    }

    // Override pure virtual function
    void printTicket() const
    {
        cout << "Flight Ticket\n";
        cout << "Name: " << customerName << endl;
        cout << "Price: $" << basePrice << endl;
        cout << "Flight #: " << flightNumber << endl;
    }
};

int main()
{
    // Polymorphism using base pointer
    Ticket* ticketPtr;

    Flight myFlight("Justin Crippen", 399.99, "GR101");

    ticketPtr = &myFlight;

    ticketPtr->printTicket();

    return 0;
}