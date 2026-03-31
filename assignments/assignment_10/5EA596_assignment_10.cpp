/**
 * @file 5EA596_assignment_10_main.cpp
 * @author 5EA596
 * @date 2026-03-31
 * @brief Assignment 10 - The Priority Help Desk (Queues)
 *
 * @details
 * This program implements a manual linked Queue to simulate a help desk ticket
 * system. The queue follows the First-In, First-Out (FIFO) rule, meaning the
 * first customer added is the first customer served.
 *
 * The HelpDesk class manages nodes manually using dynamic memory and maintains
 * both a front pointer and a rear pointer for efficient queue operations.
 *
 * Implemented features:
 * - enqueue
 * - dequeue
 * - peek using enum QueueSide
 * - size
 * - isEmpty
 * - clear
 * - display
 * - destructor
 * - copy constructor
 * - move constructor
 * - copy assignment operator
 * - move assignment operator
 *
 * Mandatory Header Question:
 * In a manual Queue, why is it necessary to maintain a 'Rear' pointer in addition
 * to a 'Front' pointer? How does this affect the Big-O complexity of the Enqueue
 * operation?
 *
 * Answer:
 * The rear pointer is necessary because new nodes are always added at the back
 * of the queue. If the queue only had a front pointer, the program would need
 * to traverse the entire linked structure every time enqueue is called in order
 * to find the last node. By keeping a rear pointer, enqueue can directly attach
 * the new node to the end in O(1) time instead of O(n).
 *
 * AI Usage Statement:
 * AI assistance was used to help clarify assignment requirements, organize the
 * structure of the class, and check code documentation for grammer.
 */

#include <iostream>
#include <string>
using namespace std;

/**
 * @enum QueueSide
 * @brief Indicates which side of the queue should be accessed by peek.
 */
enum QueueSide
{
    FRONT,
    REAR
};

/**
 * @struct Customer
 * @brief Represents a help desk ticket.
 */
struct Customer
{
    string name;      ///< Customer name
    string issue;     ///< Description of the issue
    int ticketID;     ///< Ticket number

    /**
     * @brief Default constructor
     */
    Customer()
    {
        name = "";
        issue = "";
        ticketID = 0;
    }

    /**
     * @brief Value constructor
     * @param n Customer name
     * @param i Issue description
     * @param id Ticket ID
     */
    Customer(string n, string i, int id)
    {
        name = n;
        issue = i;
        ticketID = id;
    }
};

/**
 * @class HelpDesk
 * @brief Manual linked queue for managing help desk tickets.
 */
class HelpDesk
{
private:
    /**
     * @struct Node
     * @brief Internal linked node for the queue.
     */
    struct Node
    {
        Customer data;  ///< Customer data stored in the node
        Node* next;     ///< Pointer to the next node

        /**
         * @brief Node constructor
         * @param value Customer data to store
         */
        Node(const Customer& value)
        {
            data = value;
            next = nullptr;
        }
    };

    Node* front;   ///< Pointer to the front of the queue
    Node* rear;    ///< Pointer to the rear of the queue
    int count;     ///< Number of nodes in the queue

    /**
     * @brief Copies all nodes from another HelpDesk queue.
     * @param other Queue to copy from
     */
    void copyFrom(const HelpDesk& other)
    {
        if (other.front == nullptr)
        {
            front = nullptr;
            rear = nullptr;
            count = 0;
            return;
        }

        Node* currentOther = other.front;

        while (currentOther != nullptr)
        {
            enqueue(currentOther->data);
            currentOther = currentOther->next;
        }
    }

public:
    /**
     * @brief Default constructor
     */
    HelpDesk()
    {
        front = nullptr;
        rear = nullptr;
        count = 0;
    }

    /**
     * @brief Copy constructor
     * @param other Queue to copy from
     */
    HelpDesk(const HelpDesk& other)
    {
        front = nullptr;
        rear = nullptr;
        count = 0;
        copyFrom(other);
    }

    /**
     * @brief Move constructor
     * @param other Queue to move from
     */
    HelpDesk(HelpDesk&& other)
    {
        front = other.front;
        rear = other.rear;
        count = other.count;

        other.front = nullptr;
        other.rear = nullptr;
        other.count = 0;
    }

    /**
     * @brief Destructor
     */
    ~HelpDesk()
    {
        clear();
    }

    /**
     * @brief Copy assignment operator
     * @param other Queue to copy from
     * @return Reference to the current object
     */
    HelpDesk& operator=(const HelpDesk& other)
    {
        if (this != &other)
        {
            clear();
            copyFrom(other);
        }

        return *this;
    }

    /**
     * @brief Move assignment operator
     * @param other Queue to move from
     * @return Reference to the current object
     */
    HelpDesk& operator=(HelpDesk&& other)
    {
        if (this != &other)
        {
            clear();

            front = other.front;
            rear = other.rear;
            count = other.count;

            other.front = nullptr;
            other.rear = nullptr;
            other.count = 0;
        }

        return *this;
    }

    /**
     * @brief Adds a customer to the rear of the queue.
     * @param customer Customer to add
     */
    void enqueue(const Customer& customer)
    {
        Node* newNode = new Node(customer);

        if (isEmpty())
        {
            front = newNode;
            rear = newNode;
        }
        else
        {
            rear->next = newNode;
            rear = newNode;
        }

        count++;
    }

    /**
     * @brief Removes the customer at the front of the queue.
     * @return Removed customer data, or default Customer if empty
     */
    Customer dequeue()
    {
        if (isEmpty())
        {
            cout << "Dequeue failed: queue is empty." << endl;
            return Customer();
        }

        Node* temp = front;
        Customer removedCustomer = front->data;

        front = front->next;

        if (front == nullptr)
        {
            rear = nullptr;
        }

        delete temp;
        count--;

        return removedCustomer;
    }

    /**
     * @brief Returns the customer at the requested side of the queue.
     * @param side FRONT or REAR
     * @return Customer data from that side, or default Customer if empty
     */
    Customer peek(QueueSide side) const
    {
        if (isEmpty())
        {
            cout << "Peek failed: queue is empty." << endl;
            return Customer();
        }

        if (side == FRONT)
        {
            return front->data;
        }

        return rear->data;
    }

    /**
     * @brief Checks whether the queue is empty.
     * @return True if empty, false otherwise
     */
    bool isEmpty() const
    {
        return front == nullptr;
    }

    /**
     * @brief Returns the number of nodes in the queue.
     * @return Current queue size
     */
    int size() const
    {
        return count;
    }

    /**
     * @brief Deletes all nodes and resets the queue.
     */
    void clear()
    {
        while (front != nullptr)
        {
            Node* temp = front;
            front = front->next;
            delete temp;
        }

        rear = nullptr;
        count = 0;
    }

    /**
     * @brief Displays all tickets from front to rear.
     */
    void display() const
    {
        if (isEmpty())
        {
            cout << "[Empty Queue]" << endl;
            return;
        }

        Node* current = front;

        cout << "Front -> Rear:" << endl;

        while (current != nullptr)
        {
            cout << "Ticket ID: " << current->data.ticketID
                 << " | Name: " << current->data.name
                 << " | Issue: " << current->data.issue << endl;
            current = current->next;
        }
    }
};

/**
 * @brief Displays one customer ticket neatly.
 * @param customer Customer to print
 */
void printCustomer(const Customer& customer)
{
    cout << "Ticket ID: " << customer.ticketID
         << " | Name: " << customer.name
         << " | Issue: " << customer.issue << endl;
}

/**
 * @brief Main test driver for the HelpDesk queue assignment.
 * @return int Program exit status
 */
int main()
{
    HelpDesk desk;

    cout << "==============================" << endl;
    cout << "Assignment 10: Help Desk Queue" << endl;
    cout << "==============================" << endl;

    cout << "\nCategory A: Functional FIFO & Enum-Based Peeking" << endl;

    desk.enqueue(Customer("Alice", "Cannot reset password", 1001));
    desk.enqueue(Customer("Bob", "VPN not connecting", 1002));

    cout << "\nFront ticket after enqueuing Alice and Bob:" << endl;
    printCustomer(desk.peek(FRONT));

    cout << "Rear ticket after enqueuing Alice and Bob:" << endl;
    printCustomer(desk.peek(REAR));

    cout << "\nDequeue test:" << endl;
    Customer served = desk.dequeue();
    cout << "Removed ticket:" << endl;
    printCustomer(served);

    cout << "New front after dequeue:" << endl;
    printCustomer(desk.peek(FRONT));

    cout << "\nCurrent queue contents:" << endl;
    desk.display();

    cout << "\nQueue size: " << desk.size() << endl;
    cout << "Queue empty? " << (desk.isEmpty() ? "true" : "false") << endl;

    cout << "\nEmpty robustness test:" << endl;
    HelpDesk emptyDesk;
    emptyDesk.peek(FRONT);
    emptyDesk.dequeue();

    cout << "\nCategory B: Resource Management (Rule of Five)" << endl;

    desk.enqueue(Customer("Charlie", "Email locked", 1003));
    desk.enqueue(Customer("Diana", "Software install request", 1004));

    cout << "\nOriginal desk before copy:" << endl;
    desk.display();

    HelpDesk copiedDesk(desk);
    cout << "\nCopied desk before modification:" << endl;
    copiedDesk.display();

    copiedDesk.dequeue();

    cout << "\nCopied desk after one dequeue:" << endl;
    copiedDesk.display();

    cout << "\nOriginal desk should remain unchanged:" << endl;
    desk.display();

    HelpDesk assignedDesk;
    assignedDesk.enqueue(Customer("TempUser1", "Temporary issue", 9001));
    assignedDesk.enqueue(Customer("TempUser2", "Another temporary issue", 9002));

    cout << "\nAssigned desk before copy assignment:" << endl;
    assignedDesk.display();

    assignedDesk = desk;

    cout << "\nAssigned desk after copy assignment from original desk:" << endl;
    assignedDesk.display();

    HelpDesk movedDesk(std::move(copiedDesk));

    cout << "\nMoved desk after move constructor:" << endl;
    movedDesk.display();

    cout << "Original copiedDesk after move:" << endl;
    copiedDesk.display();

    HelpDesk anotherDesk;
    anotherDesk.enqueue(Customer("Eva", "Printer issue", 2001));
    anotherDesk.enqueue(Customer("Frank", "Account lockout", 2002));

    cout << "\nAnother desk before move assignment:" << endl;
    anotherDesk.display();

    anotherDesk = std::move(assignedDesk);

    cout << "\nAnother desk after move assignment:" << endl;
    anotherDesk.display();

    cout << "assignedDesk after move assignment:" << endl;
    assignedDesk.display();

    cout << "\nClear test on anotherDesk:" << endl;
    anotherDesk.clear();
    anotherDesk.display();
    cout << "Queue size: " << anotherDesk.size() << endl;
    cout << "Queue empty? " << (anotherDesk.isEmpty() ? "true" : "false") << endl;

    return 0;
}