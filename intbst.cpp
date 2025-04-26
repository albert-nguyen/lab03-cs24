#include "intbst.h"
#include <iostream>
using std::cout;

// constructor sets up empty tree
IntBST::IntBST() {
    root = nullptr;
}

// destructor deletes all nodes
IntBST::~IntBST() {
    clear(root);
}

// recursive helper for destructor
void IntBST::clear(Node* n) {
    if (n != nullptr) {
        clear(n->left);
        clear(n->right);
        delete n;
    }
}

// insert value in tree; return false if duplicate
bool IntBST::insert(int value) {
    if (root == nullptr) {
        root = new Node(value);
        return true;
    }
    return insert(value, root);  // Calls the private helper
}

// recursive helper for insert (assumes n is never nullptr)
bool IntBST::insert(int value, Node* n) {
    if (value == n->info) {  // Replaced 'data' with 'info'
        return false;  // Duplicate value
    } else if (value < n->info) {  // Replaced 'data' with 'info'
        if (n->left == nullptr) {
            n->left = new Node(value);
            n->left->parent = n;  // Set parent pointer
            return true;
        }
        return insert(value, n->left);  // Recur on the left child
    } else {
        if (n->right == nullptr) {
            n->right = new Node(value);
            n->right->parent = n;  // Set parent pointer
            return true;
        }
        return insert(value, n->right);  // Recur on the right child
    }
}

// print tree data pre-order
void IntBST::printPreOrder() const {
    printPreOrder(root);  // Call the helper function
}

// recursive helper for printPreOrder
void IntBST::printPreOrder(Node* n) const {
    if (n != nullptr) {
        cout << n->info << " ";  // Replaced 'data' with 'info'
        printPreOrder(n->left);
        printPreOrder(n->right);
    }
}

// print tree data in-order
void IntBST::printInOrder() const {
    printInOrder(root);  // Call the helper function
}

// recursive helper for printInOrder
void IntBST::printInOrder(Node* n) const {
    if (n != nullptr) {
        printInOrder(n->left);
        cout << n->info << " ";  // Replaced 'data' with 'info'
        printInOrder(n->right);
    }
}

// print tree data post-order
void IntBST::printPostOrder() const {
    printPostOrder(root);  // Call the helper function
}

// recursive helper for printPostOrder
void IntBST::printPostOrder(Node* n) const {
    if (n != nullptr) {
        printPostOrder(n->left);
        printPostOrder(n->right);
        cout << n->info << " ";  // Replaced 'data' with 'info'
    }
}

// return sum of values in tree
int IntBST::sum() const {
    return sum(root);  // Call the helper function
}

// recursive helper for sum
int IntBST::sum(Node* n) const {
    if (n == nullptr) {
        return 0;
    }
    return n->info + sum(n->left) + sum(n->right);  // Replaced 'data' with 'info'
}

// return count of values
int IntBST::count() const {
    return count(root);  // Call the helper function
}

// recursive helper for count
int IntBST::count(Node* n) const {
    if (n == nullptr) {
        return 0;
    }
    return 1 + count(n->left) + count(n->right);  // Replaced 'data' with 'info'
}

// returns the node for a given value or NULL if none exists
IntBST::Node* IntBST::getNodeFor(int value, Node* n) const {
    if (n == nullptr) {
        return nullptr;
    }
    if (value == n->info) {  // Replaced 'data' with 'info'
        return n;
    } else if (value < n->info) {  // Replaced 'data' with 'info'
        return getNodeFor(value, n->left);
    } else {
        return getNodeFor(value, n->right);
    }
}

// returns true if value is in the tree; false if not
bool IntBST::contains(int value) const {
    return getNodeFor(value, root) != nullptr;
}

// returns the Node containing the predecessor of the given value
IntBST::Node* IntBST::getPredecessorNode(int value) const {
    Node* current = getNodeFor(value, root);
    if (current == nullptr) {
        return nullptr;  // Node not found
    }

    // Case 1: If there is a left subtree, the predecessor is the rightmost node of the left subtree
    if (current->left != nullptr) {
        current = current->left;
        while (current->right != nullptr) {
            current = current->right;
        }
        return current;  // The rightmost node in the left subtree
    }

    // Case 2: If there is no left subtree, move up to the parent and keep checking
    Node* parent = current->parent;
    while (parent != nullptr && current == parent->left) {
        current = parent;
        parent = parent->parent;
    }
    return parent;  // If we find a parent where current is not the left child, return that parent
}

// returns the predecessor value of the given value or 0 if there is none
int IntBST::getPredecessor(int value) const {
    Node* predNode = getPredecessorNode(value);
    return predNode ? predNode->info : 0;  // Return 0 if there is no predecessor
}

// returns the Node containing the successor of the given value
IntBST::Node* IntBST::getSuccessorNode(int value) const {
    Node* current = getNodeFor(value, root);
    if (current == nullptr) {
        return nullptr;  // Node not found
    }

    // Case 1: If there is a right subtree, the successor is the leftmost node of the right subtree
    if (current->right != nullptr) {
        current = current->right;
        while (current->left != nullptr) {
            current = current->left;
        }
        return current;  // The leftmost node in the right subtree
    }

    // Case 2: If there is no right subtree, move up to the parent and keep checking
    Node* parent = current->parent;
    while (parent != nullptr && current == parent->right) {
        current = parent;
        parent = parent->parent;
    }
    return parent;  // If we find a parent where current is not the right child, return that parent
}

// returns the successor value of the given value or 0 if there is none
int IntBST::getSuccessor(int value) const {
    Node* succNode = getSuccessorNode(value);
    return succNode ? succNode->info : 0;  // Return 0 if there is no successor
}

// deletes the Node containing the given value from the tree
bool IntBST::remove(int value) {
    return remove(value, root);  // Calls the private helper
}

// private helper for remove
bool IntBST::remove(int value, Node*& n) {
    if (n == nullptr) {
        return false;
    }
    if (value < n->info) {  // Replaced 'data' with 'info'
        return remove(value, n->left);
    } else if (value > n->info) {  // Replaced 'data' with 'info'
        return remove(value, n->right);
    }

    // Node found
    if (n->left == nullptr && n->right == nullptr) {
        delete n;
        n = nullptr;
    } else if (n->left == nullptr) {
        Node* temp = n;
        n = n->right;
        delete temp;
    } else if (n->right == nullptr) {
        Node* temp = n;
        n = n->left;
        delete temp;
    } else {
        Node* succNode = getSuccessorNode(n->info);
        n->info = succNode->info;  // Replace info with successor value
        remove(succNode->info, n->right);
    }

    return true;
}
