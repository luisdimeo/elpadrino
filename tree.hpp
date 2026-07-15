#ifndef TREE_HPP
#define TREE_HPP

#include "Node.hpp" // <-- Cambiado a .hpp
#include <string>

class Tree {
private:
    Node* root; // El jefe supremo (Raíz)

    // Lista enlazada simple interna para guardar temporalmente nodos huérfanos del CSV
    struct ListNode {
        Node* treeNode;
        ListNode* next;
        ListNode(Node* node) : treeNode(node), next(nullptr) {}
    };

    ListNode* pendingListHead; // Cabeza de la lista de pendientes

    // Métodos auxiliares privados
    void insertPending(Node* node);
    Node* findNodeInTree(Node* current, int id);
    void resolvePendingNodes();
    void clearTree(Node* current);
    void printSuccessionRecursive(Node* current);
    Node* findFirstFreeSuccessor(Node* current, bool allowJail = false);
    Node* findNewBossRules(Node* deadBoss);
    