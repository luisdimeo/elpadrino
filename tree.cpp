#include "tree.hpp" 
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

// Constructor
Tree::Tree() {
    root = nullptr;
    pendingListHead = nullptr;
}

// Destructor para evitar fugas de memoria
Tree::~Tree() {
    clearTree(root);
    ListNode* current = pendingListHead;
    while (current != nullptr) {
        ListNode* nextNode = current->next;
        delete current->treeNode;
        delete current;
        current = nextNode;
    }
}

void Tree::clearTree(Node* current) {
    if (current != nullptr) {
        clearTree(current->left);
        clearTree(current->right);
        delete current;
    }
}