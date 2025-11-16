#ifndef BST_H
#define BST_H
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
    public:
        /** Constructor & Destructor */
        Bst();
        ~Bst();

        /** Function pointer */
        using visitFunc = void (*)(const T&);           /// typedef for the function because compiler doesn't know what T is until later as it is a template type parameter

        /** Recursive class operations */
        void insert(const T& value);
        bool search (const T& value) const;
        void deleteTree();

        void inOrderTraversal(visitFunc visit) const;       /// In-Order Wrapper
        void preOrderTraversal(visitFunc visit) const;      /// Pre-Order Wrapper
        void postOrderTraversal(visitFunc visit) const;     /// Post-Order Wrapper

    private:
        /** Root node */
        Node<T>* root;

        /** Private recursive class operations */
        void insertRecursive(const T& value, Node<T>*& startNode);

        void inOrder(Node<T>* startNode, visitFunc visit) const;       /// Left - Node - Right (Sorted Order)
        void preOrder(Node<T>* startNode, visitFunc visit) const;      /// Node - Left - Right (serialization, copying/saving tree structure)
        void postOrder(Node<T>* startNode, visitFunc visit) const;     /// Left - Right - Node (Child Before Parent, safe Delete)
};


/// =================================================================================


/** Constructor */
template<typename T>
Bst<T>::Bst() {
    root = nullptr;     /// Set the initial root value to be nullptr as it hasn't been created
}

/** Destructor */
template<typename T>
Bst<T>::~Bst() {
    deleteTree();
}


/// =================================================================================


/** Insert */
template<typename T>
void Bst<T>::insert(const T& value) {
    cout << "Inserting Value: " << value << endl;
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

        /** Value is smaller than current Node */
    } else if (value < startNode->data) {
        insertRecursive(value, startNode->left);

        /** Value is bigger than current Node */
    } else if (value > startNode->data) {
        insertRecursive(value, startNode->right);

        /** Duplicate Value */
    } else {
        cout << "Duplicated value ignored: " << value << endl;
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

/** Delete Tree */
template<typename T>
void Bst<T>::deleteTree() {
    /// requires postorder delete
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
