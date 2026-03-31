/**
 * @file Itinerary.h
 * @author 5EA596
 * @date March 25, 2026
 * @brief Declares the Itinerary class for Assignment 9.
 *
 * This class implements a custom doubly linked list to store city names.
 * Each node links both forward and backward, allowing traversal in both
 * directions.
 *
 * Critical Thinking Note:
 * A doubly linked list is useful when the program needs efficient forward
 * and reverse traversal. Each node stores both a next pointer and a prev
 * pointer, which makes reverse printing possible without rebuilding the list.
 *
 * [AI CITATION]
 * ChatGPT was used to clarify doubly linked list wiring, reverse traversal
 * logic, destructor cleanup, and the structure of a nested iterator class
 * using overloaded operators.
 */

#ifndef ITINERARY_H
#define ITINERARY_H

#include <iostream>
#include <string>

using namespace std;

/**
 * @class Itinerary
 * @brief Manages a doubly linked list of city names.
 *
 * The class keeps track of both the head and tail of the list so that
 * it can print efficiently in both forward and reverse directions.
 */
class Itinerary
{
private:
    /**
     * @struct Node
     * @brief Represents a single city node in the doubly linked list.
     */
    struct Node
    {
        string city;   /**< City stored in this node */
        Node* next;    /**< Pointer to the next node */
        Node* prev;    /**< Pointer to the previous node */
    };

    Node* head;        /**< Pointer to the first node in the list */
    Node* tail;        /**< Pointer to the last node in the list */

public:
    /**
     * @class Iterator
     * @brief Nested iterator for STL-style traversal of the custom list.
     *
     * This iterator stores a pointer to the current node and supports:
     * - operator++ for forward movement
     * - operator-- for backward movement
     * - operator* for access to the city string
     * - operator!= for loop comparisons
     */
    class Iterator
    {
    private:
        Node* current; /**< Current node being referenced by the iterator */

    public:
        /**
         * @brief Constructs an iterator at a given node.
         * @param ptr Pointer to the node the iterator should reference
         */
        Iterator(Node* ptr = nullptr);

        /**
         * @brief Moves the iterator forward to the next node.
         * @return Reference to the updated iterator
         */
        Iterator& operator++();

        /**
         * @brief Moves the iterator backward to the previous node.
         * @return Reference to the updated iterator
         */
        Iterator& operator--();

        /**
         * @brief Dereferences the iterator to access the city string.
         * @return Reference to the current city string
         */
        string& operator*() const;

        /**
         * @brief Compares two iterators for inequality.
         * @param other Iterator being compared
         * @return true if iterators point to different nodes
         * @return false if iterators point to the same node
         */
        bool operator!=(const Iterator& other) const;
    };

    /**
     * @brief Default constructor.
     *
     * Initializes an empty itinerary with head and tail set to nullptr.
     */
    Itinerary();

    /**
     * @brief Destructor.
     *
     * Traverses the list and deletes every node to prevent memory leaks.
     */
    ~Itinerary();

    /**
     * @brief Appends a city to the end of the doubly linked list.
     *
     * Updates next and prev pointers appropriately.
     *
     * @param cityName Name of the city to add
     */
    void append(const string& cityName);

    /**
     * @brief Prints the itinerary from head to tail.
     */
    void printForward() const;

    /**
     * @brief Prints the itinerary from tail to head.
     */
    void printReverse() const;

    /**
     * @brief Returns an iterator to the first node.
     * @return Iterator positioned at the head
     */
    Iterator begin();

    /**
     * @brief Returns an iterator representing one past the end.
     * @return Iterator positioned at nullptr
     */
    Iterator end();
};

#endif