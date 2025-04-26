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
    return insert(value, root);
}

// recursive helper for insert (assumes n is never nullptr)
bool IntBST::insert(int value, Node* n) {
    if (value == n->info) {
        return false;
    } else if (value < n->info) {
        if (n->left == nullptr) {
            n->left = new Node(value);
            n->left->parent = n;
            return true;
        }
        return insert(value, n->left);
    } else {
        if (n->right == nullptr) {
            n->right = new Node(value);
            n->right->parent = n;
            return true;
        }
        return insert(value, n->right);
    }
}

// print tree data pre-order
void IntBST::printPreOrder() const {
    printPreOrder(root);
}

// recursive helper for printPreOrder
void IntBST::printPreOrder(Node* n) const {
    if (n != nullptr) {
        cout << n->info << " ";
        printPreOrder(n->left);
        printPreOrder(n->right);
    }
}

// print tree data in-order
void IntBST::printInOrder() const {
    printInOrder(root);
}

// recursive helper for printInOrder
void IntBST::printInOrder(Node* n) const {
    if (n != nullptr) {
        printInOrder(n->left);
        cout << n->info << " ";
        printInOrder(n->right);
    }
}

// print tree data post-order
void IntBST::printPostOrder() const {
    printPostOrder(root);
}

// recursive helper for printPostOrder
void IntBST::printPostOrder(Node* n) const {
    if (n != nullptr) {
        printPostOrder(n->left);
        printPostOrder(n->right);
        cout << n->info << " ";
    }
}

// return sum of values in tree
int IntBST::sum() const {
    return sum(root);
}

// recursive helper for sum
int IntBST::sum(Node* n) const {
    if (n == nullptr) {
        return 0;
    }
    return n->info + sum(n->left) + sum(n->right);
}

// return count of values
int IntBST::count() const {
    return count(root);
}

// recursive helper for count
int IntBST::count(Node* n) const {
    if (n == nullptr) {
        return 0;
    }
    return 1 + count(n->left) + count(n->right);
}

// returns the node for a given value or NULL if none exists
IntBST::Node* IntBST::getNodeFor(int value, Node* n) const {
    if (n == nullptr) {
        return nullptr;
    }
    if (value == n->info) {
        return n;
    } else if (value < n->info) {
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
        return nullptr;
    }

    if (current->left != nullptr) {
        current = current->left;
        while (current->right != nullptr) {
            current = current->right;
        }
        return current;
    }

    Node* parent = current->parent;
    while (parent != nullptr && current == parent->left) {
        current = parent;
        parent = parent->parent;
    }
    return parent;
}

// returns the predecessor value of the given value or 0 if there is none
int IntBST::getPredecessor(int value) const {
    Node* predNode = getPredecessorNode(value);
    return predNode ? predNode->info : 0;
}

// returns the Node containing the successor of the given value
IntBST::Node* IntBST::getSuccessorNode(int value) const {
    Node* current = getNodeFor(value, root);
    if (current == nullptr) {
        return nullptr;
    }

    if (current->right != nullptr) {
        current = current->right;
        while (current->left != nullptr) {
            current = current->left;
        }
        return current;
    }

    Node* parent = current->parent;
    while (parent != nullptr && current == parent->right) {
        current = parent;
        parent = parent->parent;
    }
    return parent;
}

// returns the successor value of the given value or 0 if there is none
int IntBST::getSuccessor(int value) const {
    Node* succNode = getSuccessorNode(value);
    return succNode ? succNode->info : 0;
}

// deletes the Node containing the given value from the tree
bool IntBST::remove(int value) {
    return remove(value, root);
}

// private helper for remove
bool IntBST::remove(int value, Node*& n) {
    if (n == nullptr) {
        return false;
    }
    if (value < n->info) {
        return remove(value, n->left);
    } else if (value > n->info) {
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
        n->info = succNode->info;
        remove(succNode->info, n->right);
    }

    return true;
}
