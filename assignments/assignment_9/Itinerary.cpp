/**
 * @file Itinerary.cpp
 * @author 5EA596
 * @date March 26, 2026
 * @brief Implements the Itinerary class for Assignment 9.
 */

#include "Itinerary.h"

/**
 * @brief Default constructor for Itinerary.
 */
Itinerary::Itinerary()
{
    head = nullptr;
    tail = nullptr;
}

/**
 * @brief Destructor for Itinerary.
 *
 * Deletes every node in the list from head to tail.
 * This prevents memory leaks by freeing all dynamically allocated memory.
 */
Itinerary::~Itinerary()
{
    Node* temp = head;

    while (temp != nullptr)
    {
        Node* nextNode = temp->next;
        delete temp;
        temp = nextNode;
    }

    head = nullptr;
    tail = nullptr;
}

/**
 * @brief Appends a city to the end of the list.
 *
 * If the list is empty, the new node becomes both head and tail.
 * Otherwise, it is linked after the current tail, and both next
 * and prev pointers are updated.
 *
 * @param cityName Name of the city to add
 */
void Itinerary::append(const string& cityName)
{
    Node* newNode = new Node;
    newNode->city = cityName;
    newNode->next = nullptr;
    newNode->prev = nullptr;

    if (head == nullptr)
    {
        head = newNode;
        tail = newNode;
    }
    else
    {
        tail->next = newNode;
        newNode->prev = tail;
        tail = newNode;
    }
}

/**
 * @brief Prints the list from head to tail.
 *
 * Uses next pointers to move forward through the chain.
 */
void Itinerary::printForward() const
{
    Node* temp = head;

    cout << "Forward: ";

    while (temp != nullptr)
    {
        cout << "[" << temp->city << "] -> ";
        temp = temp->next;
    }

    cout << "[END]" << endl;
}

/**
 * @brief Prints the list from tail to head.
 *
 * Uses prev pointers to move backward through the chain.
 */
void Itinerary::printReverse() const
{
    Node* temp = tail;

    cout << "Reverse: ";

    while (temp != nullptr)
    {
        cout << "[" << temp->city << "] -> ";
        temp = temp->prev;
    }

    cout << "[END]" << endl;
}

/**
 * @brief Returns an iterator to the start of the list.
 * @return Iterator at head
 */
Itinerary::Iterator Itinerary::begin()
{
    return Iterator(head);
}

/**
 * @brief Returns an iterator to one past the end of the list.
 * @return Iterator at nullptr
 */
Itinerary::Iterator Itinerary::end()
{
    return Iterator(nullptr);
}

/**
 * @brief Constructs an iterator pointing at a node.
 * @param ptr Pointer to the node
 */
Itinerary::Iterator::Iterator(Node* ptr)
{
    current = ptr;
}

/**
 * @brief Moves the iterator forward.
 * @return Reference to this iterator
 */
Itinerary::Iterator& Itinerary::Iterator::operator++()
{
    if (current != nullptr)
    {
        current = current->next;
    }

    return *this;
}

/**
 * @brief Moves the iterator backward.
 * @return Reference to this iterator
 */
Itinerary::Iterator& Itinerary::Iterator::operator--()
{
    if (current != nullptr)
    {
        current = current->prev;
    }

    return *this;
}

/**
 * @brief Dereferences the iterator.
 * @return Reference to the city string in the current node
 */
string& Itinerary::Iterator::operator*() const
{
    return current->city;
}

/**
 * @brief Compares iterators for inequality.
 * @param other Iterator being compared
 * @return true if current pointers differ
 * @return false if current pointers match
 */
bool Itinerary::Iterator::operator!=(const Iterator& other) const
{
    return current != other.current;
}