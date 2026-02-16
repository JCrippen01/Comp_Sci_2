/**
 * *********************************************************
 * @file person.h
 * @author 5EA596
 * @date 2026-02-15
 * @brief lab_4
 * *********************************************************
 */



#ifndef PERSON_H
#define PERSON_H

#include <string>
#include <iostream>

/**
 * @class Person
 * @brief Base class representing a generic person in Global Roam.
 *
 * Stores shared attributes that apply to all people:
 * name and address. Uses protected access so derived classes
 * can access these members directly when appropriate.
 */
class Person
{
protected:
    std::string name;     ///< Person's full name
    std::string address;  ///< Person's mailing address

public:
    /**
     * @brief Constructs a Person with a name and address.
     * @param name Person's name.
     * @param address Person's address.
     */
    Person(const std::string& name, const std::string& address);

    /**
     * @brief Gets the person's name.
     * @return Name as a string.
     */
    std::string getName() const;

    /**
     * @brief Gets the person's address.
     * @return Address as a string.
     */
    std::string getAddress() const;

    /**
     * @brief Prints basic person information (name and address).
     */
    virtual void printInfo() const;

    /**
     * @brief Virtual destructor for proper polymorphic cleanup.
     */
    virtual ~Person() = default;
};

#endif
