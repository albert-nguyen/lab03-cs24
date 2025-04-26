#include <iostream>
#include "intbst.h"

using namespace std;

int main() {
    IntBST tree;

    cout << "Inserting values: 10, 5, 15, 3, 7, 12, 18\n";
    tree.insert(10);
    tree.insert(5);
    tree.insert(15);
    tree.insert(3);
    tree.insert(7);
    tree.insert(12);
    tree.insert(18);

    cout << "\nPre-order: ";
    tree.printPreOrder();

    cout << "In-order: ";
    tree.printInOrder();

    cout << "Post-order: ";
    tree.printPostOrder();

    cout << "\nSum of tree: " << tree.sum() << endl;
    cout << "Count of values: " << tree.count() << endl;

    cout << "\nContains 7? " << (tree.contains(7) ? "Yes" : "No") << endl;
    cout << "Contains 100? " << (tree.contains(100) ? "Yes" : "No") << endl;

    cout << "\nPredecessor of 10: " << tree.getPredecessor(10) << endl;
    cout << "Successor of 10: " << tree.getSuccessor(10) << endl;

    cout << "\nRemoving 10 (root node with two children)...\n";
    tree.remove(10);
    cout << "In-order after removing 10: ";
    tree.printInOrder();

    cout << "\nRemoving 3 (leaf)...\n";
    tree.remove(3);
    cout << "In-order after removing 3: ";
    tree.printInOrder();

    cout << "\nRemoving 5 (node with one child)...\n";
    tree.remove(5);
    cout << "In-order after removing 5: ";
    tree.printInOrder();

    cout << "\nFinal Pre-order: ";
    tree.printPreOrder();

    cout << "Final Post-order: ";
    tree.printPostOrder();

    return 0;
}
