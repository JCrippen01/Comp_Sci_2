#ifndef CARGOBIN_H
#define CARGOBIN_H

#include <string>

/**
 * @brief A generic CargoBin that stores items of any type.
 * @tparam T The data type stored in the bin.
 *
 * Storage is a heap-allocated array (T*). The bin tracks capacity and count.
 * Boundary issues are handled by throwing std::string error messages.
 */
template <class T>
class CargoBin
{
private:
    T* binPtr;     // Heap array
    int capacity;  // Max items
    int count;     // Current items

public:
    /**
     * @brief Constructs a CargoBin with a fixed capacity.
     * @param cap The maximum number of items in the bin.
     */
    CargoBin(int cap)
    {
        capacity = cap;
        count = 0;
        binPtr = new T[capacity];
    }

    /**
     * @brief Destructor frees heap memory.
     */
    ~CargoBin()
    {
        delete [] binPtr;
        binPtr = 0;
    }

    /**
     * @brief Adds an item to the bin.
     * @param item Item to add.
     * @throws std::string if the bin is full.
     */
    void push(const T& item)
    {
        if (count == capacity)
        {
            throw std::string("Error: Bin is full.");
        }

        binPtr[count] = item;
        count++;
    }

    /**
     * @brief Removes and returns the last item added (LIFO).
     * @return The removed item.
     * @throws std::string if the bin is empty.
     */
    T pop()
    {
        if (count == 0)
        {
            throw std::string("Error: Bin is empty.");
        }

        count--;
        return binPtr[count];
    }

    /**
     * @brief Gets the number of items currently in the bin.
     */
    int getCount() const
    {
        return count;
    }

    /**
     * @brief Gets the capacity of the bin.
     */
    int getCapacity() const
    {
        return capacity;
    }
};

#endif