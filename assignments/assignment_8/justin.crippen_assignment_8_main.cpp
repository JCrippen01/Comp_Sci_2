/**
 * @file justin_crippen_assignment_8_main.cpp
 * @author Justin Crippen
 * @date 2026-03-22
 * @brief Assignment 8 solution for The High-Performance Travel Manager.
 *
 * This program defines a TravelGroup class that demonstrates static data,
 * static member functions, operator overloading, move semantics, and the
 * Rule of Five. The class tracks a global traveler audit using a static
 * totalSystemTravelers variable.
 *
 * Reflection / Critical Thinking Analysis:
 * In the Copy Constructor, we add travelers to the static global total
 * because copying creates a new object with duplicated data. The system
 * now contains both the original and the copy, so the audit must increase.
 *
 * In the Move Constructor, we do not add travelers to the static total
 * because ownership of the data is transferred, not duplicated. The total
 * number of travelers represented in the system remains the same.
 *
 * @ai_note
 * AI assistance was used to better understand move semantics, particularly
 * how the move assignment operator transfers ownership of data and how the
 * destructor interacts with moved-from objects. AI was used to clarify the
 * logic behind resetting the moved-from object's traveler count to prevent
 * incorrect subtraction from the static audit when the destructor is called.
 */

#include <iostream>
#include <string>

using namespace std;

class TravelGroup
{
private:
    string destination;
    int travelers;
    static int totalSystemTravelers;

public:
    TravelGroup()
    {
        destination = "Unassigned";
        travelers = 0;
    }

    TravelGroup(string dest, int count)
    {
        destination = dest;
        travelers = count;
        totalSystemTravelers += travelers;
    }

    TravelGroup(const TravelGroup& other)
    {
        destination = other.destination;
        travelers = other.travelers;
        totalSystemTravelers += travelers;
    }

    TravelGroup(TravelGroup&& other)
    {
        destination = other.destination;
        travelers = other.travelers;

        other.destination = "Moved_From";
        other.travelers = 0;
    }

    ~TravelGroup()
    {
        totalSystemTravelers -= travelers;
    }

    TravelGroup& operator=(const TravelGroup& other)
    {
        if (this != &other)
        {
            totalSystemTravelers -= travelers;

            destination = other.destination;
            travelers = other.travelers;

            totalSystemTravelers += travelers;
        }
        return *this;
    }

    /**
     * @brief Move assignment operator.
     * @param other The TravelGroup object to move from.
     * @return A reference to the current object.
     *
     * This operator removes the current object's travelers from the audit,
     * then steals the incoming data from the source object. The moved-from
     * object is reset to zero travelers so its destructor will not subtract
     * the transferred travelers later.
     *
     * This is a net-zero transfer for the moved data itself because the
     * travelers are transferred, not duplicated.
     *
     * @ai_note
     * AI assistance was used to better understand the internal behavior of
     * move assignment and how it differs from copy assignment. Specifically,
     * AI helped clarify why the moved-from object's traveler count must be
     * reset to zero so that the destructor does not incorrectly subtract
     * travelers that have already been transferred. This ensured a correct
     * implementation of the static audit system.
     */
    TravelGroup& operator=(TravelGroup&& other)
    {
        if (this != &other)
        {
            totalSystemTravelers -= travelers;

            destination = other.destination;
            travelers = other.travelers;

            other.destination = "Moved_From";
            other.travelers = 0;
        }

        return *this;
    }

    static int getAgencyTotal()
    {
        return totalSystemTravelers;
    }

    TravelGroup operator+(const TravelGroup& other) const
    {
        string mergedDestination = destination + " & " + other.destination;
        int mergedTravelers = travelers + other.travelers;

        TravelGroup mergedGroup(mergedDestination, mergedTravelers);
        return mergedGroup;
    }

    friend ostream& operator<<(ostream& out, const TravelGroup& group);
};

int TravelGroup::totalSystemTravelers = 0;

ostream& operator<<(ostream& out, const TravelGroup& group)
{
    out << "Booking '" << group.destination << "' ("
        << group.travelers << " people).";
    return out;
}

TravelGroup createTemporaryGroup(string dest, int count)
{
    TravelGroup temp(dest, count);
    return temp;
}

int main()
{
    cout << "System Initialization..." << endl;
    cout << "Global Audit: " << TravelGroup::getAgencyTotal() << endl << endl;

    TravelGroup group1("Europe Tour", 20);
    cout << group1 << endl;
    cout << "Global Audit: " << TravelGroup::getAgencyTotal() << endl << endl;

    cout << "--- Copy Constructor Demo ---" << endl;
    TravelGroup copiedGroup(group1);
    cout << "Copied Group: " << copiedGroup << endl;
    cout << "Global Audit: " << TravelGroup::getAgencyTotal() << endl << endl;

    cout << "--- Move Constructor Demo ---" << endl;
    TravelGroup movedConstructed(static_cast<TravelGroup&&>(copiedGroup));
    cout << "Moved-Constructed Group: " << movedConstructed << endl;
    cout << "Global Audit: " << TravelGroup::getAgencyTotal() << endl << endl;

    cout << "--- Operator+ Demo ---" << endl;
    TravelGroup group2("Asia Cruise", 15);
    cout << group2 << endl;
    cout << "Global Audit: " << TravelGroup::getAgencyTotal() << endl;

    TravelGroup mergedGroup = group1 + group2;
    cout << "Merged Group: " << mergedGroup << endl;
    cout << "Global Audit: " << TravelGroup::getAgencyTotal() << endl << endl;

    cout << "--- Copy Assignment Demo ---" << endl;
    TravelGroup group3("Local Escape", 5);
    cout << "Before Copy Assignment: " << group3 << endl;
    cout << "Global Audit: " << TravelGroup::getAgencyTotal() << endl;

    group3 = group1;
    cout << "After group3 = group1: " << group3 << endl;
    cout << "Global Audit: " << TravelGroup::getAgencyTotal() << endl << endl;

    cout << "--- Move Assignment Demo ---" << endl;
    TravelGroup archiveGroup;
    cout << "Before Move Assignment: " << archiveGroup << endl;
    cout << "Global Audit: " << TravelGroup::getAgencyTotal() << endl;

    archiveGroup = createTemporaryGroup("Archive Group", 20);
    cout << "After Move Assignment: " << archiveGroup << endl;
    cout << "Global Audit: " << TravelGroup::getAgencyTotal() << endl << endl;

    cout << "Moving 'Europe Tour' to 'Archive Group' via Move Assignment..." << endl;
    TravelGroup emptyArchive;
    emptyArchive = static_cast<TravelGroup&&>(group1);
    cout << emptyArchive << endl;
    cout << "Global Audit: " << TravelGroup::getAgencyTotal()
         << " (Verified: No duplicate counts created during move!)" << endl;

    return 0;
}