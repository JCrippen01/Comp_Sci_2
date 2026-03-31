/**
 * @file 5EA596_module_9_main.cpp
 * @author 5EA596
 * @date March 26, 2026
 * @brief Lab 9 - The Grand Tour (Merging Lists)
 *
 * Builds two linked lists (Europe and Asia routes) and merges them
 * by linking the tail of the first list to the head of the second list.
 *
 * Critical Thinking Reflection:
 * Linking lists is efficient because it only requires updating a single pointer.
 * Moving nodes individually would require traversal and copying (O(n)).
 *
 * [AI CITATION]
 * ChatGPT was used to clarify linked list traversal conditions (identifying the
 * tail node using `temp->next != nullptr`) and to reinforce the concept of
 * merging lists by updating a single pointer instead of duplicating nodes.
 */

#include <iostream>
#include <string>

using namespace std;

/**
 * @struct Node
 * @brief Represents a single node in the linked list.
 *
 * Each node contains:
 * - A city name (data)
 * - A pointer to the next node
 */
struct Node
{
    string city;   /**< City name stored in the node */
    Node* next;    /**< Pointer to the next node in the list */
};

/**
 * @brief Appends a new node to the end of the list.
 *
 * Traverses the list until the last node is found,
 * then attaches the new node.
 *
 * @param head Reference to the head pointer of the list
 * @param cityName Name of the city to add
 */
void append(Node*& head, const string& cityName)
{
    Node* newNode = new Node;       ///< Allocate new node
    newNode->city = cityName;       ///< Assign city name
    newNode->next = nullptr;        ///< Set next to null (end of list)

    if (head == nullptr)
    {
        head = newNode;             ///< Empty list → new node becomes head
    }
    else
    {
        Node* temp = head;          ///< Temporary pointer for traversal

        while (temp->next != nullptr)
        {
            temp = temp->next;      ///< Move to next node
        }

        temp->next = newNode;       ///< Attach new node at the end
    }
}

/**
 * @brief Merges two linked lists.
 *
 * Connects the tail of list1 to the head of list2.
 * This avoids copying nodes and improves efficiency.
 *
 * @param list1 Reference to the head of the first list
 * @param list2 Pointer to the head of the second list
 */
void mergeLists(Node*& list1, Node* list2)
{
    if (list1 == nullptr)
    {
        list1 = list2;              ///< If first list empty, assign list2
    }
    else
    {
        Node* temp = list1;         ///< Start at head of list1

        while (temp->next != nullptr)
        {
            temp = temp->next;      ///< Traverse to last node
        }

        temp->next = list2;         ///< Link tail of list1 to head of list2
    }
}

/**
 * @brief Displays all nodes in the list.
 *
 * Prints the itinerary in the format:
 * City1 -> City2 -> City3
 *
 * @param head Pointer to the head of the list
 */
void displayList(Node* head)
{
    Node* temp = head;              ///< Start traversal at head

    while (temp != nullptr)
    {
        cout << temp->city;

        if (temp->next != nullptr)
        {
            cout << " -> ";         ///< Print arrow between nodes
        }

        temp = temp->next;          ///< Move to next node
    }

    cout << endl;
}

/**
 * @brief Deletes all nodes in the list to prevent memory leaks.
 *
 * Traverses the list and deletes each node safely.
 * Saves the next pointer before deletion to avoid losing access.
 *
 * @param head Reference to the head pointer
 */
void cleanupList(Node*& head)
{
    Node* temp = head;              ///< Start at head

    while (temp != nullptr)
    {
        Node* nextNode = temp->next; ///< Save next node BEFORE delete

        cout << "Deleting: " << temp->city << "..." << endl;

        delete temp;                 ///< Free current node memory

        temp = nextNode;             ///< Move to next node
    }

    head = nullptr;                  ///< Reset head after cleanup
}

/**
 * @brief Main function - program entry point.
 *
 * Creates two lists, merges them, displays the result,
 * and cleans up memory.
 *
 * @return int Program exit status
 */
int main()
{
    Node* europeHead = nullptr;     ///< Head of Europe list
    Node* asiaHead = nullptr;       ///< Head of Asia list

    // Build Europe route
    append(europeHead, "London");
    append(europeHead, "Paris");
    append(europeHead, "Berlin");

    // Build Asia route
    append(asiaHead, "Tokyo");
    append(asiaHead, "Seoul");
    append(asiaHead, "Beijing");

    cout << "--- Global Roam Itinerary Merger ---" << endl << endl;

    cout << "Merging Europe and Asia routes..." << endl;

    mergeLists(europeHead, asiaHead); ///< Merge the two lists

    cout << "Full Itinerary: ";
    displayList(europeHead);

    cout << endl;

    cout << "Cleaning up memory..." << endl;

    cleanupList(europeHead);          ///< Delete all nodes

    cout << "Done." << endl;

    return 0;
}