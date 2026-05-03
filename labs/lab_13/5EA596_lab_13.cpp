/*
 * Lab 13: The Million-Item Challenge
 * Author: 5EA596
 * Description: Proving O(log n) vs O(n) using high-resolution timing.
 *
 * Reflection:
 * Binary Search is much faster than Linear Search when the data is already
 * sorted because it cuts the search area in half with each comparison.
 * However, we still use Linear Search when the data is unsorted, small, or
 * only needs to be searched one time. The hidden cost of Binary Search is
 * sorting the data first. Sorting can take more time than just doing one
 * simple Linear Search, especially if the list is only searched once.
 */

#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>
#include <ctime>

using std::cout;
using std::endl;
using std::vector;
using std::sort;
using std::chrono::high_resolution_clock;
using std::chrono::duration_cast;
using std::chrono::microseconds;

/**
 * @brief Searches a vector from beginning to end.
 * @param vec The dataset to search.
 * @param target The value to find.
 * @return The index of the target or -1 if not found.
 */
int linearSearch(const vector<int>& vec, int target) {
    for (int i = 0; i < vec.size(); i++) {
        if (vec[i] == target) {
            return i;
        }
    }

    return -1;
}

/**
 * @brief Searches a sorted vector using binary search.
 * @param vec The sorted dataset to search.
 * @param target The value to find.
 * @return The index of the target or -1 if not found.
 */
int binarySearch(const vector<int>& vec, int target) {
    int low = 0;
    int high = vec.size() - 1;

    while (low <= high) {
        int mid = low + (high - low) / 2;

        if (vec[mid] == target) {
            return mid;
        }
        else if (vec[mid] < target) {
            low = mid + 1;
        }
        else {
            high = mid - 1;
        }
    }

    return -1;
}

int main() {
    const int SIZE = 1000000;
    vector<int> database(SIZE);

    cout << "--- Global Roam Security Token Benchmark ---" << endl;
    cout << "Generating " << SIZE << " Tokens... ";

    srand(time(0));

    for (int i = 0; i < SIZE; i++) {
        database[i] = rand() % 2000000;
    }

    cout << "Done." << endl;

    int target = database[SIZE - 1];
    cout << "Target ID to find: " << target << " (Last item in list)" << endl;

    cout << "\n[RACE 1] Linear Search (O(n))" << endl;
    auto start = high_resolution_clock::now();

    int index = linearSearch(database, target);

    auto stop = high_resolution_clock::now();
    auto linearDuration = duration_cast<microseconds>(stop - start);

    cout << "Found at index: " << index << endl;
    cout << "Time taken: " << linearDuration.count() << " microseconds" << endl;

    cout << "\n... Sorting Database for Binary Search... ";
    sort(database.begin(), database.end());
    cout << "Done." << endl;

    target = database[SIZE - 1];

    cout << "\n[RACE 2] Binary Search (O(log n))" << endl;
    start = high_resolution_clock::now();

    index = binarySearch(database, target);

    stop = high_resolution_clock::now();
    auto binaryDuration = duration_cast<microseconds>(stop - start);

    cout << "Found at index: " << index << endl;
    cout << "Time taken: " << binaryDuration.count() << " microseconds" << endl;

    long long linTime = linearDuration.count();
    long long binTime = binaryDuration.count();

    if (binTime == 0) {
        binTime = 1;
    }

    cout << "\nVERDICT: Binary Search was "
         << (linTime / binTime)
         << "x faster." << endl;

    return 0;
}