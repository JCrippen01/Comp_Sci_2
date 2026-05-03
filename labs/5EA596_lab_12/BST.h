#ifndef BST_H
#define BST_H

#include <iostream>

/**
 * @file BST.h
 * @author 5EA596
 * @date 2026-04-04
 * @brief Templated Binary Search Tree implementation for Lab 12 and Assignment 12.
 *
 * Reflection Answers:
 *
 * 1. Why is a Post-Order traversal used for destroyRec but a Pre-Order traversal
 *    used for copyRec? What would happen if you swapped them?
 *
 *    destroyRec uses Post-Order because the children must be deleted before the
 *    parent. If the parent were deleted first, access to the children could be lost,
 *    which could cause memory leaks or invalid memory access.
 *
 *    copyRec uses Pre-Order because the parent node must be created before its
 *    children can be attached beneath it. If this were swapped, the logic would
 *    become much more difficult because child nodes would be processed before the
 *    parent node existed in the new tree.
 *
 * 2. When searching for "Zane", why is the BST faster than a standard linear
 *    std::vector of employees?
 *
 *    In a BST, each comparison allows the program to eliminate roughly half of the
 *    remaining search space when the tree is balanced, resulting in about O(log n)
 *    performance. A linear vector search may require checking every employee one by
 *    one, which is O(n).
 *
 * 3. If we have two employees named "Sarah" but with different IDs, how does the
 *    current insertRec logic handle the second Sarah? Why?
 *
 *    With this implementation, values that are not less than the current node go
 *    to the right subtree. That means a duplicate name such as a second "Sarah"
 *    will be inserted to the right. This happens because only operator< is checked
 *    first, and all other values fall into the "else" branch.
 *
 * AI Citation:
 * Tool Used: ChatGPT
 * Prompt Summary: Generate a full BST template solution with recursive helpers,
 * Employee class, file parsing, traversal logic, search trace, destructor trace,
 * and optional remove bonus for a Computer Science II assignment.
 * Changes Made: Final formatting, comments, and assignment-specific wording were
 * adjusted for clarity and submission readiness.
 */

template <typename T>
class BST
{
private:
    /**
     * @brief Internal tree node structure.
     */
    struct Node
    {
        T data;
        Node* left;
        Node* right;

        /**
         * @brief Construct a new Node object.
         * @param value The value to store in the node.
         */
        Node(const T& value) : data(value), left(nullptr), right(nullptr) {}
    };

    Node* root;

    /**
     * @brief Recursively inserts a value into the BST.
     * @param current Pointer to the current subtree root.
     * @param value The value being inserted.
     * @return Node* The subtree root after insertion is completed.
     */
    Node* insertRec(Node* current, const T& value)
    {
        if (current == nullptr)
        {
            return new Node(value);
        }

        if (value < current->data)
        {
            current->left = insertRec(current->left, value);
        }
        else
        {
            current->right = insertRec(current->right, value);
        }

        return current;
    }

    /**
     * @brief Recursively removes a value from the BST.
     * @param current Pointer to the current subtree root.
     * @param value The value being removed.
     * @return Node* The updated subtree root after removal.
     */
    Node* removeRec(Node* current, const T& value)
    {
        if (current == nullptr)
        {
            return nullptr;
        }

        if (value < current->data)
        {
            current->left = removeRec(current->left, value);
        }
        else if (current->data < value)
        {
            current->right = removeRec(current->right, value);
        }
        else
        {
            // Case 1: no children
            if (current->left == nullptr && current->right == nullptr)
            {
                delete current;
                return nullptr;
            }

            // Case 2: one child
            if (current->left == nullptr)
            {
                Node* temp = current->right;
                delete current;
                return temp;
            }

            if (current->right == nullptr)
            {
                Node* temp = current->left;
                delete current;
                return temp;
            }

            // Case 3: two children
            Node* successor = findMin(current->right);
            current->data = successor->data;
            current->right = removeRec(current->right, successor->data);
        }

        return current;
    }

    /**
     * @brief Finds the smallest node in a subtree.
     * @param current Pointer to the subtree root.
     * @return Node* Pointer to the smallest node in that subtree.
     */
    Node* findMin(Node* current) const
    {
        while (current != nullptr && current->left != nullptr)
        {
            current = current->left;
        }
        return current;
    }

    /**
     * @brief Recursively copies a tree using Pre-Order traversal.
     * @param current Pointer to the current source subtree root.
     * @return Node* Pointer to the root of the newly copied subtree.
     */
    Node* copyRec(Node* current)
    {
        if (current == nullptr)
        {
            return nullptr;
        }

        Node* newNode = new Node(current->data);
        newNode->left = copyRec(current->left);
        newNode->right = copyRec(current->right);

        return newNode;
    }

    /**
     * @brief Recursively deletes every node using Post-Order traversal.
     * @param current Pointer to the current subtree root.
     * @return void Nothing is returned because the purpose is to safely destroy nodes.
     */
    void destroyRec(Node* current)
    {
        if (current == nullptr)
        {
            return;
        }

        destroyRec(current->left);
        destroyRec(current->right);

        std::cout << "Deleting Agent: " << current->data << std::endl;
        delete current;
    }

    /**
     * @brief Recursively prints the BST in In-Order traversal.
     * @param current Pointer to the current subtree root.
     * @return void Nothing is returned because values are printed directly.
     */
    void inorderRec(Node* current) const
    {
        if (current == nullptr)
        {
            return;
        }

        inorderRec(current->left);
        std::cout << current->data << std::endl;
        inorderRec(current->right);
    }

    /**
     * @brief Recursively prints the BST in Pre-Order traversal.
     * @param current Pointer to the current subtree root.
     * @return void Nothing is returned because values are printed directly.
     */
    void preorderRec(Node* current) const
    {
        if (current == nullptr)
        {
            return;
        }

        std::cout << current->data << std::endl;
        preorderRec(current->left);
        preorderRec(current->right);
    }

    /**
     * @brief Recursively prints the BST in Post-Order traversal.
     * @param current Pointer to the current subtree root.
     * @return void Nothing is returned because values are printed directly.
     */
    void postorderRec(Node* current) const
    {
        if (current == nullptr)
        {
            return;
        }

        postorderRec(current->left);
        postorderRec(current->right);
        std::cout << current->data << std::endl;
    }

    /**
     * @brief Recursively searches for a target while printing the visit path.
     * @param current Pointer to the current subtree root.
     * @param target The value being searched for.
     * @return bool True if the target is found, otherwise false.
     */
    bool searchRec(Node* current, const T& target) const
    {
        if (current == nullptr)
        {
            return false;
        }

        std::cout << "Visited: " << current->data << std::endl;

        if (!(target < current->data) && !(current->data < target))
        {
            return true;
        }

        if (target < current->data)
        {
            return searchRec(current->left, target);
        }

        return searchRec(current->right, target);
    }

public:
    /**
     * @brief Default constructor.
     */
    BST() : root(nullptr) {}

    /**
     * @brief Copy constructor.
     * @param other The BST being copied.
     */
    BST(const BST& other)
    {
        root = copyRec(other.root);
    }

    /**
     * @brief Move constructor.
     * @param other The BST being moved.
     */
    BST(BST&& other)
    {
        root = other.root;
        other.root = nullptr;
    }

    /**
     * @brief Destructor.
     */
    ~BST()
    {
        destroyRec(root);
        root = nullptr;
    }

    /**
     * @brief Copy assignment operator.
     * @param other The BST being assigned from.
     * @return BST& Reference to the updated BST object.
     */
    BST& operator=(const BST& other)
    {
        if (this != &other)
        {
            destroyRec(root);
            root = copyRec(other.root);
        }
        return *this;
    }

    /**
     * @brief Move assignment operator.
     * @param other The BST being moved from.
     * @return BST& Reference to the updated BST object.
     */
    BST& operator=(BST&& other)
    {
        if (this != &other)
        {
            destroyRec(root);
            root = other.root;
            other.root = nullptr;
        }
        return *this;
    }

    /**
     * @brief Inserts a value into the BST.
     * @param value The value to insert.
     */
    void insert(const T& value)
    {
        root = insertRec(root, value);
    }

    /**
     * @brief Removes a value from the BST.
     * @param value The value to remove.
     */
    void remove(const T& value)
    {
        root = removeRec(root, value);
    }

    /**
     * @brief Prints the BST in ascending order.
     */
    void inorder() const
    {
        inorderRec(root);
    }

    /**
     * @brief Prints the BST in root-first order.
     */
    void preorder() const
    {
        preorderRec(root);
    }

    /**
     * @brief Prints the BST in children-first order.
     */
    void postorder() const
    {
        postorderRec(root);
    }

    /**
     * @brief Searches for a value while printing the path taken.
     * @param target The value to search for.
     * @return bool True if found, otherwise false.
     */
    bool search(const T& target) const
    {
        return searchRec(root, target);
    }

    /**
     * @brief Checks whether the tree is empty.
     * @return bool True if empty, otherwise false.
     */
    bool isEmpty() const
    {
        return root == nullptr;
    }
};

#endif