// intbst.cpp
// Implements class IntBST
// Oliver zhou, 22/10/2024

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
void IntBST::clear(Node *n) {
    if(n!=nullptr){
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
    } else {
        return insert(value, root);
    }
}

// recursive helper for insert (assumes n is never 0)
bool IntBST::insert(int value, Node *n) {
    if (value == n->info) {
        return false;
    //travers left
    } else if (value < n->info) {
        if (n->left == nullptr) {
            n->left = new Node(value);
            n->left->parent = n;
            return true;
        } else {
            return insert(value, n->left); 
        }
    } else {
    //traverse right
        if (n->right == nullptr) {
            n->right = new Node(value);
            n->right->parent = n;
            return true;
        } else {
            return insert(value, n->right);
        }
    }
}

// print tree data pre-order
void IntBST::printPreOrder() const {
    printPreOrder(root);
}

// recursive helper for printPreOrder()
void IntBST::printPreOrder(Node *n) const {
    if (n != nullptr) {
        cout << n->info<<",";
        printPreOrder(n->left);
        printPreOrder(n->right);
    }
}

// print tree data in-order, with helper
void IntBST::printInOrder() const {
    printInOrder(root);
    cout << endl;
}
void IntBST::printInOrder(Node *n) const {
    if (n == nullptr){
        return;
    }

    printInOrder(n->left);

    cout << n->info;

    if (n->right != nullptr) {
        cout << " ";
    }

    printInOrder(n->right);
}

// prints tree data post-order, with helper
void IntBST::printPostOrder() const {
    printPostOrder(root);
}

void IntBST::printPostOrder(Node *n) const {
    if (n != nullptr) {
        printPostOrder(n->left);
        printPostOrder(n->right);
        cout << n->info << ",";
    }
}

// return sum of values in tree
int IntBST::sum() const {
    return sum(root);
}

// recursive helper for sum
int IntBST::sum(Node *n) const {
    if (n == nullptr) {
        return 0;
    } else {
        return n->info + sum(n->left) + sum(n->right);
    }
}

// return count of values
int IntBST::count() const {
    return count(root);
}

// recursive helper for count
int IntBST::count(Node *n) const {
    if (n == nullptr) {
        return 0;
    } else {
        return 1 + count(n->left) + count(n->right);
    }
}

// IMPLEMENT THIS FIRST: returns the node for a given value or NULL if none exists
// Parameters:
// int value: the value to be found
// Node* n: the node to start with (for a recursive call)
// Whenever you call this method from somewhere else, pass it
// the root node as "n"
IntBST::Node* IntBST::getNodeFor(int value, Node* n) const{
    if (n == nullptr) {
        return nullptr;
    } else if (value == n->info) {
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
IntBST::Node* IntBST::getPredecessorNode(int value) const{
    Node* n = getNodeFor(value, root);
    if (n == nullptr || n->left == nullptr) {
        return nullptr;
    }
    //go to left tree for rightmost node
    Node* temp = n->left;
    while (temp->right != nullptr) {
        temp = temp->right;
    }
    return temp;
}

// returns the predecessor value of the given value or 0 if there is none
int IntBST::getPredecessor(int value) const{
    Node* predNode = getPredecessorNode(value);
    if (predNode != nullptr) {
        return predNode->info;
    } else {
        return 0;
    }
}

// returns the Node containing the successor of the given value
IntBST::Node* IntBST::getSuccessorNode(int value) const{
    Node* n = getNodeFor(value, root);
    if (n == nullptr) {
        return nullptr;
    }

    //right subtree leftmost node
    if (n->right != nullptr) {
        Node* temp = n->right;
        while (temp->left != nullptr) {
            temp = temp->left;
        }
        return temp;
    }

    //no right subtree
    Node* parent = n->parent;
    while (parent != nullptr && n == parent->right) {
        n = parent;
        parent = parent->parent;
    }

    return parent;
}
// returns the successor value of the given value or 0 if there is none
int IntBST::getSuccessor(int value) const{
    Node* succNode = getSuccessorNode(value);
    if (succNode != nullptr) {
        return succNode->info;
    } else {
        return 0;
    }
}

// deletes the Node containing the given value from the tree
// returns true if the node exist and was deleted or false if the node does not exist
bool IntBST::remove(int value){
    Node* n = getNodeFor(value, root);
    if (n == nullptr) {
        return false;
    }

    //2 child case
    if (n->left != nullptr && n->right != nullptr) {
        Node* successor = getSuccessorNode(value);
        n->info = successor->info;
        n = successor;
    }

    //0/1 child case
    Node* child = (n->left != nullptr) ? n->left : n->right;

    //replace node
    if (n->parent == nullptr) {
        root = child;
    } else if (n == n->parent->left) {
        n->parent->left = child;
    } else {
        n->parent->right = child;
    }
    if (child != nullptr) {
        child->parent = n->parent;
    }
    delete n;
    return true;
}
