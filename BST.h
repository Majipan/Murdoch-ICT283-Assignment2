#ifndef Bst_H
#define Bst_H
#include <cassert>
#include <iostream>

using std::cout;
using std::endl;

/**
 * @brief Individual Nodes
 */
template <typename T>
struct Node {
    T data;
    Node<T>* left;
    Node<T>* right;
};


/// =================================================================================


/**
 * @brief Binary Search Tree
 */
template <typename T>
class Bst {

    /// =============================================================================
    public:
        /** @brief Constructor */
        Bst();
        /** @brief Copy Constructor */
        Bst(const Bst<T>& other);
        /** @brief Destructor */
        ~Bst();

        /**
         * @brief Function pointer
         * Typedef for the function because compiler doesn't know what T is until later as it is a template type parameter
         */
        using visitFunc = void (*)(const T&);

        /**
         * @brief Recursive Insertion
         * @param value The value to insert
         */
        void insert(const T& value);

        /**
         * @brief Recursive Search
         * @param value The value to search for
         */
        bool search (const T& value) const;

        /**
         * @brief Getter for Size of Binary Tree
         * @return Integer for the size of the Binary Tree
         */
        const int size() const;

        /** @brief Delete tree initialiser */
        void deleteTree();

        /**
         * @brief Assignment Operator for =
         * This is for copy constructor and so that the compiler doesn't create a shallow copy
         */
        Bst<T>& operator=(const Bst<T>& other);

        /**
         * @brief Access element by index (In-order ONLY)
         * @param index The index of the node in in-order traversal
         */
        const T& operator[](int index) const;

        /**
         * @brief In-order Traversal wrapper
         * @param visit Function pointer
         */
        void inOrderTraversal(visitFunc visit) const;
        /**
         * @brief Pre-order Traversal wrapper
         * @param visit Function pointer
         */
        void preOrderTraversal(visitFunc visit) const;
        /**
         * @brief Post-order Traversal wrapper
         * @param visit Function pointer
         */
        void postOrderTraversal(visitFunc visit) const;

    /// =============================================================================

    private:
        /** @brief Root node pointer */
        Node<T>* root;
        /** @brief Node count tracker after each successful insert */
        int nodeCount;

        /**
         * @brief Copy Constructor recursive helper
         * @param node The node to add
         */
        Node<T>* clone(Node<T>* node);

        /**
         * @brief Insert recursive class operation
         * @param value Value to insert
         */
        void insertRecursive(const T& value, Node<T>*& startNode);
        /**
         * @brief Delete recursive class operation
         * @param node Node to delete if not null
         */
        void deleteRecursive(Node<T>* node);

        /**
         * @brief Helper to retrieve the node at a given in-order index
         * @param node          Current node in traversal
         * @param currentIndex  Traversal counter, incremented as we visit nodes
         * @param targetIndex   Index we are searching for
         * @return Pointer to the node at targetIndex, or nullptr if not found
         */
        Node<T>* getAtIndex(Node<T>* node, int& currentIndex, int targetIndex) const;

        /**
         * @brief In-order traversal
         * @param startNode     The node to compare recursively
         * @param visit         Function pointer
         * Left - Node - Right (Sorted Order)
         */
        void inOrder(Node<T>* startNode, visitFunc visit) const;
        /**
         * @brief Pre-order traversal
         * @param startNode     The node to compare recursively
         * @param visit         Function pointer
         * Node - Left - Right (serialization, copying/saving tree structure)
         */
        void preOrder(Node<T>* startNode, visitFunc visit) const;
        /**
         * @brief Post-order traversal
         * @param startNode     The node to compare recursively
         * @param visit         Function pointer
         * Left - Right - Node (Child Before Parent, safe Delete)
         */
        void postOrder(Node<T>* startNode, visitFunc visit) const;
};


/// =================================================================================


/** Constructor */
template<typename T>
Bst<T>::Bst() : root(nullptr), nodeCount(0)         /// Set the initial root and nodeCount value to be nullptr as it hasn't been created
{
}

/** Copy Constructor */
template<typename T>
Bst<T>::Bst(const Bst<T>& other) {
    root = clone(other.root);
    nodeCount = other.nodeCount;
}

/** Copy Constructor Helper */
template<typename T>
Node<T>* Bst<T>::clone(Node<T>* node) {
    if (!node) return nullptr;

    Node<T>* newNode = new Node<T>;
    newNode->data = node->data;
    newNode->left = clone(node->left);
    newNode->right = clone(node->right);
    return newNode;
}

/** Copy assignment operator */
template<typename T>
Bst<T>& Bst<T>::operator=(const Bst<T>& other) {
    if (this != &other) {
        /// delete existing tree
        deleteTree();
        /// deep copy from other
        root = clone(other.root);
        nodeCount = other.nodeCount;
    }
    return *this;
}

/** Destructor */
template<typename T>
Bst<T>::~Bst() {
    deleteTree();
}


/** Getter for Tree size */
template<typename T>
const int Bst<T>::size() const {
    return nodeCount;
}

/// =================================================================================

/** Access element by in-order index */
template<typename T>
const T& Bst<T>::operator[](int index) const {
    assert(index >= 0 && index < nodeCount && "Bst index out of range");

    int currentIndex = 0;
    Node<T>* result = getAtIndex(root, currentIndex, index);

    /// result should never be nullptr if assert above passes
    assert(result != nullptr && "Bst getAtIndex returned nullptr");

    return result->data;
}

/** Helper to find node recursively based on in-order index */
template<typename T>
Node<T>* Bst<T>::getAtIndex(Node<T>* node, int& currentIndex, int targetIndex) const {
    if (!node) {
        return nullptr;
    }

    /// Traverse left subtree
    Node<T>* leftResult = getAtIndex(node->left, currentIndex, targetIndex);
    if (leftResult) {
        return leftResult;
    }

    /// Visit current node
    if (currentIndex == targetIndex) {
        return node;
    }
    ++currentIndex;

    /// Traverse right subtree
    return getAtIndex(node->right, currentIndex, targetIndex);
}

/// =================================================================================

/** Insert */
template<typename T>
void Bst<T>::insert(const T& value) {
    insertRecursive(value, root);
}

/** Insert Recursively */
template<typename T>
void Bst<T>::insertRecursive(const T& value, Node<T>*& startNode) {

    /**
     * If startNode is nullptr, create the a new node
     * If startNode has a value, check if the new value is larger or smaller
     */
    if (startNode==nullptr) {
        Node<T>* newNode = new Node<T>;
        newNode->data = value;          /// Set the value of the new node
        newNode->left = nullptr;        /// Set left to nullptr
        newNode->right = nullptr;       /// Set right to nullptr

        startNode = newNode;            /// Set the new node
        nodeCount++;                    /// Keep track of the number of nodes

        /** Value is smaller than current Node */
    } else if (value < startNode->data) {
        insertRecursive(value, startNode->left);

        /** Current Node is bigger than Value */
    } else if (startNode->data < value) {
        insertRecursive(value, startNode->right);

        /** Duplicate Value */
    } else {
        /// Duplicated value is detected, will ignore
    }
}


/// =================================================================================


/** Search Node */
template<typename T>
bool Bst<T>::search (const T& value) const {
    Node<T>* current = root;

    /** Loop until the end of the tree or when the value is found */
    while (current != nullptr) {
        /// found
        if(value == current->data) return true;

        /// iterate until current == value
        current = ( value < current->data ) ? current->left : current->right;
    }

    return false;       /// Not found
}


/// =================================================================================


/** Delete Tree */
template<typename T>
void Bst<T>::deleteTree() {
    deleteRecursive(root);
    root = nullptr;
    nodeCount = 0;
}

/** Post-order Deletion */
template<typename T>
void Bst<T>::deleteRecursive(Node<T>* node) {
    if (!node) return;
    deleteRecursive(node->left);
    deleteRecursive(node->right);
    delete node;
}


/// =================================================================================


/** Public Wrapper
 * @brief In-Order Traversal Wrapper
 */
template<typename T>
void Bst<T>::inOrderTraversal(visitFunc visit) const {
    if (root == nullptr) return;

    inOrder(root, visit);
}

/** In-Order Traversal
 * @brief Left -> Current Node -> Right
 */
template<typename T>
void Bst<T>::inOrder(Node<T>* startNode, visitFunc visit) const {
    if (startNode == nullptr) return;

    inOrder(startNode->left, visit);
    visit(startNode->data);
    inOrder(startNode->right, visit);
}


/** Public Wrapper
 * @brief Pre-Order Traversal Wrapper
 */
template<typename T>
void Bst<T>::preOrderTraversal(visitFunc visit) const {
    if (root == nullptr) return;

    preOrder(root, visit);
}

/** Pre-Order Traversal
 * @brief Current Node -> Left -> Right
 */
template<typename T>
void Bst<T>::preOrder(Node<T>* startNode, visitFunc visit) const {
    if (startNode == nullptr) return;

    visit(startNode->data);
    preOrder(startNode->left, visit);
    preOrder(startNode->right, visit);
}


/** Public Wrapper
 * @brief Post-Order Traversal Wrapper
 */
template<typename T>
void Bst<T>::postOrderTraversal(visitFunc visit) const {
    if (root == nullptr) return;

    postOrder(root, visit);
}

/** Post-Order Traversal
 * @brief Left -> Right -> Current Node
 */
template<typename T>
void Bst<T>::postOrder(Node<T>* startNode, visitFunc visit) const {
    if (startNode == nullptr) return;

    postOrder(startNode->left, visit);
    postOrder(startNode->right, visit);
    visit(startNode->data);
}


/// =================================================================================

#endif
