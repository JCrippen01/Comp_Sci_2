/**
 * @file 5EA596_assignment13.cpp
 * @author 5EA596
 * @date 2026-04-12
 * @brief Assignment 13: The Manifest Optimizer
 *
 * Reflection:
 * Since Global Roam adds new passengers every 30 seconds, constantly re-sorting
 * the entire passenger manifest with Selection Sort would be expensive because
 * Selection Sort is O(n^2). If searches are rare, I would use Linear Search on
 * the unsorted list because the cost of sorting would not be worth it. However,
 * if gate agents search the manifest constantly, I would sort the list once and
 * then use Binary Search for fast O(log n) lookups. In a real system, I would
 * avoid repeatedly using Selection Sort and instead use a better structure or
 * sorting method, but for this assignment, sorting once before searching makes
 * Binary Search useful.
 */

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <chrono>

using namespace std;
using namespace std::chrono;

class Passenger {
private:
    string firstName;
    string lastName;
    int ticketId;

public:
    /**
     * @brief Default constructor.
     */
    Passenger() : firstName(""), lastName(""), ticketId(0) {}

    /**
     * @brief Constructor for Passenger.
     * @param first Passenger first name.
     * @param last Passenger last name.
     * @param ticket Passenger ticket ID.
     */
    Passenger(string first, string last, int ticket)
        : firstName(first), lastName(last), ticketId(ticket) {}

    /**
     * @brief Gets the passenger first name.
     * @return string First name.
     */
    string getFirstName() const {
        return firstName;
    }

    /**
     * @brief Gets the passenger last name.
     * @return string Last name.
     */
    string getLastName() const {
        return lastName;
    }

    /**
     * @brief Gets the passenger ticket ID.
     * @return int Ticket ID.
     */
    int getTicketId() const {
        return ticketId;
    }

    /**
     * @brief Compares passengers alphabetically by last name.
     * @param other Passenger to compare against.
     * @return true if this passenger comes before the other passenger.
     */
    bool operator<(const Passenger& other) const {
        return lastName < other.lastName;
    }

    /**
     * @brief Prints passenger data.
     * @param os Output stream.
     * @param p Passenger to print.
     * @return ostream& Updated output stream.
     */
    friend ostream& operator<<(ostream& os, const Passenger& p) {
        os << p.lastName << ", " << p.firstName << " | Ticket ID: " << p.ticketId;
        return os;
    }
};

/**
 * @brief Sorts passengers alphabetically by last name using Selection Sort.
 * @param manifest Vector of Passenger objects.
 * @return void
 */
void selectionSort(vector<Passenger>& manifest) {
    int size = manifest.size();

    for (int start = 0; start < size - 1; start++) {
        int minIndex = start;

        for (int scan = start + 1; scan < size; scan++) {
            if (manifest[scan] < manifest[minIndex]) {
                minIndex = scan;
            }
        }

        if (minIndex != start) {
            Passenger temp = manifest[start];
            manifest[start] = manifest[minIndex];
            manifest[minIndex] = temp;
        }
    }
}

/**
 * @brief Searches for a passenger by last name using Binary Search.
 * @param manifest Sorted vector of Passenger objects.
 * @param targetLastName Last name to search for.
 * @return int Index of passenger if found, otherwise -1.
 */
int binarySearch(const vector<Passenger>& manifest, string targetLastName) {
    int low = 0;
    int high = manifest.size() - 1;

    while (low <= high) {
        int mid = low + (high - low) / 2;

        if (manifest[mid].getLastName() == targetLastName) {
            return mid;
        }
        else if (manifest[mid].getLastName() < targetLastName) {
            low = mid + 1;
        }
        else {
            high = mid - 1;
        }
    }

    return -1;
}

/**
 * @brief Prints the full passenger manifest.
 * @param manifest Vector of Passenger objects.
 * @return void
 */
void printManifest(const vector<Passenger>& manifest) {
    for (const Passenger& passenger : manifest) {
        cout << passenger << endl;
    }
}

int main() {
    vector<Passenger> manifest;

    ifstream file("passenger.dat");

    if (!file) {
        cout << "Error: Could not open passenger.dat" << endl;
        return 1;
    }

    string firstName;
    string lastName;
    int ticketId;

    while (file >> firstName >> lastName >> ticketId) {
        manifest.push_back(Passenger(firstName, lastName, ticketId));
    }

    file.close();

    cout << "--- Global Roam Manifest Optimizer ---" << endl;
    cout << "Loaded " << manifest.size() << " passengers." << endl;

    auto start = high_resolution_clock::now();

    selectionSort(manifest);

    auto end = high_resolution_clock::now();
    auto sortTime = duration_cast<microseconds>(end - start);

    cout << "\n--- Sorted Passenger Manifest ---" << endl;
    printManifest(manifest);

    cout << "\nSelection Sort Time: " << sortTime.count() << " microseconds" << endl;

    string searchName;

    cout << "\nEnter passenger last name to search: ";
    cin >> searchName;

    int result = binarySearch(manifest, searchName);

    if (result != -1) {
        cout << "\nPassenger Found!" << endl;
        cout << manifest[result] << endl;
    }
    else {
        cout << "\nPassenger not found in the system." << endl;
    }

    return 0;
}