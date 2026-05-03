#ifndef BST_H
#define BST_H

#include <iostream>
#include <string>

/**
 * @file BST.h
 * @author 5EA596
 * @date 2026-04-04
 * @brief Templated Binary Search Tree for Assignment 12
 *
 * Reflection:
 *
 * 1. When searching for "Zane", why is the BST faster than a std::vector?
 * A BST reduces the search space by half at each comparison when balanced,
 * resulting in O(log n) time. A vector requires checking each element one
 * by one, resulting in O(n).
 *
 * 2. How are duplicate names handled?
 * If a duplicate name is inserted, it will go to the right subtree because
 * insertRec places values that are not less than the current node into the
 * right branch. This maintains BST structure but may impact balance.
 */

template <typename T>
class bst {
private:
    struct Node {
        T data;
        Node* left;
        Node* right;

        /**
         * @brief Construct a new Node
         * @param value Data to store in node
         */
        Node(T value) : data(value), left(nullptr), right(nullptr) {}
    };

    Node* root;

public:
    /**
     * @brief Default constructor
     */
    bst() : root(nullptr) {}

    /**
     * @brief Destructor
     */
    ~bst() { destroyRec(root); }

    /**
     * @brief Copy constructor
     * @param other Tree to copy
     */
    bst(const bst& other) : root(nullptr) { copyRec(root, other.root); }

    /**
     * @brief Move constructor
     * @param other Tree to move
     */
    bst(bst&& other) noexcept : root(other.root) { other.root = nullptr; }

    /**
     * @brief Copy assignment operator
     * @param other Tree to copy from
     * @return bst&
     */
    bst& operator=(const bst& other) {
        if (this != &other) {
            clear();
            copyRec(root, other.root);
        }
        return *this;
    }

    /**
     * @brief Move assignment operator
     * @param other Tree to move from
     * @return bst&
     */
    bst& operator=(bst&& other) noexcept {
        if (this != &other) {
            clear();
            root = other.root;
            other.root = nullptr;
        }
        return *this;
    }

    /**
     * @brief Insert value into BST
     * @param value Value to insert
     */
    void insert(T value) { root = insertRec(root, value); }

    /**
     * @brief Remove value from BST
     * @param value Value to remove
     */
    void remove(T value) { root = removeRec(root, value); }

    /**
     * @brief Clear entire tree
     */
    void clear() { destroyRec(root); root = nullptr; }

    /**
     * @brief Print tree in-order
     */
    void printInOrder() { inorderRec(root); std::cout << std::endl; }

    /**
     * @brief Print tree pre-order
     */
    void printPreOrder() { preorderRec(root); std::cout << std::endl; }

    /**
     * @brief Print tree post-order
     */
    void printPostOrder() { postorderRec(root); std::cout << std::endl; }

    /**
     * @brief Search by employee name with trace
     * @param targetName Name to search
     * @return true if found, false otherwise
     */
    bool searchByName(std::string targetName) {
        return searchByNameRec(root, targetName);
    }

private:

    /**
     * @brief Recursive insert helper
     * @param node Current node
     * @param value Value to insert
     * @return Node* Updated subtree root
     */
    Node* insertRec(Node* node, T value) {
        if (node == nullptr) return new Node(value);

        if (value < node->data)
            node->left = insertRec(node->left, value);
        else
            node->right = insertRec(node->right, value);

        return node;
    }

    /**
     * @brief Recursive remove helper
     * @param node Current node
     * @param value Value to remove
     * @return Node* Updated subtree root
     */
    Node* removeRec(Node* node, T value) {
        if (node == nullptr) return nullptr;

        if (value < node->data)
            node->left = removeRec(node->left, value);
        else if (node->data < value)
            node->right = removeRec(node->right, value);
        else {
            if (node->left == nullptr && node->right == nullptr) {
                delete node;
                return nullptr;
            }

            if (node->left == nullptr) {
                Node* temp = node->right;
                delete node;
                return temp;
            }

            if (node->right == nullptr) {
                Node* temp = node->left;
                delete node;
                return temp;
            }

            Node* successor = minValueNode(node->right);
            node->data = successor->data;
            node->right = removeRec(node->right, successor->data);
        }

        return node;
    }

    /**
     * @brief Recursive copy helper (Pre-Order)
     * @param node Destination node reference
     * @param otherNode Source node
     */
    void copyRec(Node*& node, Node* otherNode) {
        if (otherNode == nullptr) {
            node = nullptr;
            return;
        }

        node = new Node(otherNode->data);
        copyRec(node->left, otherNode->left);
        copyRec(node->right, otherNode->right);
    }

    /**
     * @brief Recursive destroy helper (Post-Order)
     * @param node Current node
     */
    void destroyRec(Node* node) {
        if (node == nullptr) return;

        destroyRec(node->left);
        destroyRec(node->right);

        std::cout << "Deleting Agent: " << node->data << std::endl;
        delete node;
    }

    /**
     * @brief In-order traversal
     * @param node Current node
     */
    void inorderRec(Node* node) {
        if (node == nullptr) return;

        inorderRec(node->left);
        std::cout << node->data << std::endl;
        inorderRec(node->right);
    }

    /**
     * @brief Pre-order traversal
     * @param node Current node
     */
    void preorderRec(Node* node) {
        if (node == nullptr) return;

        std::cout << node->data << std::endl;
        preorderRec(node->left);
        preorderRec(node->right);
    }

    /**
     * @brief Post-order traversal
     * @param node Current node
     */
    void postorderRec(Node* node) {
        if (node == nullptr) return;

        postorderRec(node->left);
        postorderRec(node->right);
        std::cout << node->data << std::endl;
    }

    /**
     * @brief Recursive search helper
     * @param node Current node
     * @param targetName Name to search
     * @return true if found, false otherwise
     */
    bool searchByNameRec(Node* node, std::string targetName) {
        if (node == nullptr) return false;

        std::cout << "Visited: " << node->data.getName() << std::endl;

        if (targetName == node->data.getName())
            return true;
        else if (targetName < node->data.getName())
            return searchByNameRec(node->left, targetName);
        else
            return searchByNameRec(node->right, targetName);
    }

    /**
     * @brief Find smallest value in subtree
     * @param node Subtree root
     * @return Node* Minimum node
     */
    Node* minValueNode(Node* node) {
        while (node && node->left != nullptr)
            node = node->left;
        return node;
    }
};

#endif