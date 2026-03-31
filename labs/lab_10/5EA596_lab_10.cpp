/**
 * @file 5EA596_lab_10_main.cpp
 * @author 5EA596
 * @date 2026-03-31
 * @brief Lab 10 - The Agent Security Stack (LIFO)
 *
 * @details
 * This program implements a pointer-based Stack using a custom Node structure.
 * The stack follows the Last-In, First-Out (LIFO) principle, meaning the most
 * recently added element is removed first.
 *
 * This simulates secure navigation tracking, where pages are removed in reverse
 * order of access to ensure proper session cleanup.
 *
 * Features Implemented:
 * - Push, Pop, Peek
 * - isEmpty, size
 * - clear and destructor
 * - Copy constructor and copy assignment (deep copy)
 * - Move constructor and move assignment
 * - display (top-to-bottom traversal)
 *
 * Mandatory Header Question:
 * In Lab 9, we used a Tail pointer to add to the end of a list. In this Lab,
 * we only use a Top pointer. Why is a Stack more efficient than a Linked List
 * for operations that only happen at one end of the collection?
 *
 * Answer:
 * A stack is more efficient because all operations occur at a single point (the top).
 * Push and pop operations are always O(1) and do not require traversal. In a linked
 * list, accessing the end may require iteration unless additional pointers are used.
 *
 * AI Usage Statement:
 * AI assistance (ChatGPT) was used to help clarify requirements, structure the
 * implementation, and improve documentation. All code was reviewed, understood,
 * and adapted to meet assignment requirements.
 */

#include <iostream>
#include <string>
using namespace std;

/**
 * @class AgentStack
 * @brief A templated stack implemented using a singly linked structure.
 *
 * @tparam T Data type stored in the stack.
 */
template <typename T>
class AgentStack
{
private:

    /**
     * @struct Node
     * @brief Internal structure representing each element in the stack.
     */
    struct Node
    {
        T data;        ///< Stored value
        Node* next;    ///< Pointer to next node

        /**
         * @brief Node constructor
         * @param value Value to store
         * @param nextPtr Pointer to next node
         */
        Node(const T& value, Node* nextPtr = nullptr)
            : data(value), next(nextPtr) {}
    };

    Node* top;   ///< Pointer to the top of the stack
    int count;   ///< Number of elements in the stack

    /**
     * @brief Helper function to perform deep copy
     * @param other Stack to copy from
     */
    void copyFrom(const AgentStack<T>& other)
    {
        if (other.top == nullptr)
        {
            top = nullptr;
            count = 0;
            return;
        }

        Node* otherCurrent = other.top;
        Node* newTop = new Node(otherCurrent->data);
        Node* newCurrent = newTop;

        otherCurrent = otherCurrent->next;

        while (otherCurrent != nullptr)
        {
            newCurrent->next = new Node(otherCurrent->data);
            newCurrent = newCurrent->next;
            otherCurrent = otherCurrent->next;
        }

        top = newTop;
        count = other.count;
    }

public:

    /**
     * @brief Default constructor
     */
    AgentStack() : top(nullptr), count(0) {}

    /**
     * @brief Copy constructor (deep copy)
     * @param other Stack to copy
     */
    AgentStack(const AgentStack<T>& other)
    {
        top = nullptr;
        count = 0;
        copyFrom(other);
    }

    /**
     * @brief Move constructor
     * @param other Stack to move from
     */
    AgentStack(AgentStack<T>&& other)
    {
        top = other.top;
        count = other.count;

        other.top = nullptr;
        other.count = 0;
    }

    /**
     * @brief Destructor
     */
    ~AgentStack()
    {
        clear();
    }

    /**
     * @brief Copy assignment operator
     * @param other Stack to copy
     * @return Reference to current object
     */
    AgentStack<T>& operator=(const AgentStack<T>& other)
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
     * @param other Stack to move from
     * @return Reference to current object
     */
    AgentStack<T>& operator=(AgentStack<T>&& other)
    {
        if (this != &other)
        {
            clear();

            top = other.top;
            count = other.count;

            other.top = nullptr;
            other.count = 0;
        }
        return *this;
    }

    /**
     * @brief Push a new element onto the stack
     * @param value Value to add
     */
    void push(const T& value)
    {
        top = new Node(value, top);
        count++;
    }

    /**
     * @brief Remove and return top element
     * @return Removed value or default if empty
     */
    T pop()
    {
        if (isEmpty())
        {
            cout << "Pop failed: stack is empty." << endl;
            return T();
        }

        Node* temp = top;
        T value = temp->data;

        top = top->next;
        delete temp;

        count--;
        return value;
    }

    /**
     * @brief View top element without removing
     * @return Top value or default if empty
     */
    T peek() const
    {
        if (isEmpty())
        {
            cout << "Peek failed: stack is empty." << endl;
            return T();
        }

        return top->data;
    }

    /**
     * @brief Check if stack is empty
     * @return True if empty
     */
    bool isEmpty() const
    {
        return top == nullptr;
    }

    /**
     * @brief Get number of elements
     * @return Stack size
     */
    int size() const
    {
        return count;
    }

    /**
     * @brief Remove all elements from stack
     */
    void clear()
    {
        while (top != nullptr)
        {
            Node* temp = top;
            top = top->next;
            delete temp;
        }

        count = 0;
    }

    /**
     * @brief Display stack contents from top to bottom
     */
    void display() const
    {
        if (isEmpty())
        {
            cout << "[Empty Stack]" << endl;
            return;
        }

        Node* current = top;

        cout << "Top -> Bottom:" << endl;

        while (current != nullptr)
        {
            cout << current->data << endl;
            current = current->next;
        }
    }
};

/**
 * @brief Main test driver for Lab 10
 */
int main()
{
    AgentStack<string> stack;

    cout << "Initial State:" << endl;
    cout << "Empty: " << (stack.isEmpty() ? "true" : "false") << endl;
    cout << "Size: " << stack.size() << endl;

    cout << "\nPush Test:" << endl;
    stack.push("google.com");
    stack.push("maps.com");

    cout << "Peek: " << stack.peek() << endl;
    cout << "Size: " << stack.size() << endl;

    cout << "\nPop Test:" << endl;
    cout << "Popped: " << stack.pop() << endl;
    cout << "Size: " << stack.size() << endl;

    cout << "\nDisplay Test:" << endl;
    stack.push("airline.com");
    stack.push("passport.com");
    stack.push("boarding.com");
    stack.display();

    cout << "\nEdge Case Test:" << endl;
    AgentStack<string> empty;
    empty.pop();
    empty.peek();

    cout << "\nCopy Test:" << endl;
    AgentStack<string> copy(stack);
    copy.push("secure.com");

    cout << "Original:" << endl;
    stack.display();

    cout << "Copy:" << endl;
    copy.display();

    cout << "\nMove Test:" << endl;
    AgentStack<string> moved(std::move(copy));

    cout << "Moved Stack:" << endl;
    moved.display();

    cout << "Original After Move:" << endl;
    copy.display();

    cout << "\nClear Test:" << endl;
    moved.clear();
    moved.display();

    return 0;
}