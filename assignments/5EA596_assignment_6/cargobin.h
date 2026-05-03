#ifndef CARGOBIN_H
#define CARGOBIN_H

#include <string>

/**
 * @brief A generic heap-allocated cargo bin template.
 * @tparam T The data type stored in the bin.
 */
template <class T>
class CargoBin {
private:
    T* binPtr;
    int capacity;
    int count;

public:
    /**
     * @brief Constructs a CargoBin with a fixed capacity.
     * @param size Maximum number of items the bin can hold.
     */
    CargoBin(int size) {
        capacity = size;
        count = 0;
        binPtr = new T[capacity];
    }

    /**
     * @brief Destroys the CargoBin and releases heap memory.
     */
    ~CargoBin() {
        delete[] binPtr;
    }

    /**
     * @brief Adds an item to the bin.
     * @param item The item to add.
     * @throws std::string if the bin is full.
     */
    void push(T item) {
        if (count >= capacity) {
            throw std::string("Error: Bin is full.");
        }

        binPtr[count] = item;
        count++;
    }

    /**
     * @brief Removes and returns the most recent item from the bin.
     * @return T The removed item.
     * @throws std::string if the bin is empty.
     */
    T pop() {
        if (count <= 0) {
            throw std::string("Error: Bin is empty.");
        }

        count--;
        return binPtr[count];
    }

    /**
     * @brief Gets the current number of items in the bin.
     * @return int Number of stored items.
     */
    int getCount() const {
        return count;
    }

    /**
     * @brief Gets the maximum capacity of the bin.
     * @return int Maximum number of items.
     */
    int getCapacity() const {
        return capacity;
    }
};

#endif