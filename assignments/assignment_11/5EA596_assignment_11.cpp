/**
 * @file 5EA596_assignment_11_main.cpp
 * @author 5EA596
 * @date 2026-03-31
 * @brief Assignment 11 - The Recursive Route Finder
 *
 * @details
 * This program reads flight connections from an external file named
 * flights.txt, dynamically builds a graph of City objects, and then
 * uses recursive depth-first search (DFS) to determine whether a route
 * exists from a starting city to a target city.
 *
 * A City Registry is used so that each city name corresponds to exactly
 * one City object in memory. This prevents duplicate city objects and
 * ensures all connections point into the same shared graph structure.
 *
 * The recursive search uses a visited vector to prevent cycles, which is
 * especially important in a network containing loops such as:
 * London -> Dubai -> London
 *
 * The program also reconstructs and prints the successful path from the
 * starting city to the destination city.
 *
 * Additional Feature:
 * The program validates user input against the dynamically loaded flight network.
 * If a user enters a city name that does not exist in the registry, the program
 * detects this and displays a clear error message instead of attempting the search.
 *
 * This prevents null pointer access and demonstrates defensive programming by
 * ensuring that all recursive operations are performed only on valid graph nodes.
 *
 * Mandatory Analysis:
 * Why is the "City Registry" essential when reading from a file? What
 * would happen to the memory and the recursive search if every mention
 * of "London" in the text file created a brand new, separate City object?
 *
 * Answer:
 * The City Registry is essential because it guarantees that each city
 * exists only once in memory. That allows all routes involving the same
 * city name to connect back to the same object. If every mention of
 * "London" created a new separate object, then the graph would become
 * fragmented. Some paths would point to one London object, while other
 * paths would point to a different London object with different outgoing
 * flights. This would waste memory, break the true structure of the
 * graph, and cause the recursive search to miss valid routes or behave
 * incorrectly because the same real-world city would not be treated as
 * one shared node.
 *
 * AI Usage Statement:
 * AI assistance (ChatGPT) was used to help deepen understanding of recursion,
 * specifically how the call stack behaves during recursive graph traversal
 * and how depth-first search explores and backtracks through a network.
 * The code and logic were written and verified independently to ensure full
 * understanding of the recursive process and adherence to assignment requirements.
 */

#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

/**
 * @struct City
 * @brief Represents one city node in the flight graph.
 */
struct City
{
    string name;
    vector<City*> connections;

    City(const string& cityName)
    {
        name = cityName;
    }
};

/**
 * @brief Finds a city in the registry.
 */
City* findCity(const vector<City*>& cityRegistry, const string& cityName)
{
    for (size_t i = 0; i < cityRegistry.size(); i++)
    {
        if (cityRegistry[i]->name == cityName)
        {
            return cityRegistry[i];
        }
    }
    return nullptr;
}

/**
 * @brief Gets or creates a city (ensures no duplicates).
 */
City* getOrCreateCity(vector<City*>& cityRegistry, const string& cityName)
{
    City* found = findCity(cityRegistry, cityName);

    if (found != nullptr)
    {
        return found;
    }

    City* newCity = new City(cityName);
    cityRegistry.push_back(newCity);
    return newCity;
}

/**
 * @brief Checks if a city has already been visited.
 */
bool hasVisited(const vector<string>& visited, const string& cityName)
{
    for (size_t i = 0; i < visited.size(); i++)
    {
        if (visited[i] == cityName)
        {
            return true;
        }
    }
    return false;
}

/**
 * @brief Loads flight data from file and builds graph.
 */
bool loadFlights(const string& fileName, vector<City*>& cityRegistry)
{
    ifstream file(fileName);

    if (!file)
    {
        return false;
    }

    string line;

    while (getline(file, line))
    {
        size_t comma = line.find(',');

        if (comma == string::npos)
        {
            continue;
        }

        string origin = line.substr(0, comma);
        string dest = line.substr(comma + 1);

        City* originCity = getOrCreateCity(cityRegistry, origin);
        City* destCity = getOrCreateCity(cityRegistry, dest);

        originCity->connections.push_back(destCity);
    }

    file.close();
    return true;
}

/**
 * @brief Recursive DFS to find route.
 */
bool canTravel(City* current, City* target,
               vector<string>& visited,
               vector<string>& path)
{
    if (current == nullptr)
    {
        return false;
    }

    if (hasVisited(visited, current->name))
    {
        return false;
    }

    cout << "... Visiting " << current->name;

    if (current == target)
    {
        cout << " [Target Found!]" << endl;
        path.insert(path.begin(), current->name);
        return true;
    }

    cout << endl;

    visited.push_back(current->name);

    for (size_t i = 0; i < current->connections.size(); i++)
    {
        if (canTravel(current->connections[i], target, visited, path))
        {
            path.insert(path.begin(), current->name);
            return true;
        }
    }

    cout << "... Visiting " << current->name << " [Backtracking...]" << endl;
    return false;
}

/**
 * @brief Prints the discovered path.
 */
void printPath(const vector<string>& path)
{
    for (size_t i = 0; i < path.size(); i++)
    {
        cout << path[i];
        if (i + 1 < path.size())
        {
            cout << " -> ";
        }
    }
    cout << endl;
}

/**
 * @brief Frees all dynamically allocated memory.
 */
void clearCityRegistry(vector<City*>& cityRegistry)
{
    for (size_t i = 0; i < cityRegistry.size(); i++)
    {
        delete cityRegistry[i];
    }
    cityRegistry.clear();
}

int main()
{
    vector<City*> cityRegistry;

    cout << "--- Global Roam Connection Search ---" << endl;
    cout << "Loading flight data... ";

    if (!loadFlights("flights.txt", cityRegistry))
    {
        cout << "Failed." << endl;
        cout << "Error: Could not open flights.txt" << endl;
        return 1;
    }

    cout << "Done." << endl << endl;

    string startName;
    string targetName;

    cout << "Enter starting city: ";
    getline(cin, startName);

    cout << "Enter destination city: ";
    getline(cin, targetName);

    City* startCity = findCity(cityRegistry, startName);
    City* targetCity = findCity(cityRegistry, targetName);

    // Input validation: ensures cities exist before recursion begins
    if (startCity == nullptr)
    {
        cout << "\nError: \"" << startName << "\" is not in the flight network." << endl;
        clearCityRegistry(cityRegistry);
        return 1;
    }

    if (targetCity == nullptr)
    {
        cout << "\nError: \"" << targetName << "\" is not in the flight network." << endl;
        clearCityRegistry(cityRegistry);
        return 1;
    }

    cout << "\nChecking route: " << startName << " -> " << targetName << endl << endl;

    vector<string> visited;
    vector<string> path;

    bool found = canTravel(startCity, targetCity, visited, path);

    cout << endl;

    if (found)
    {
        cout << "RESULT: Route Found!" << endl;
        cout << "Path: ";
        printPath(path);
    }
    else
    {
        cout << "RESULT: No route found from "
             << startName << " to " << targetName << "." << endl;
    }

    clearCityRegistry(cityRegistry);
    return 0;
}