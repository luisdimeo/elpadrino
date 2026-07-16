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
    
    public:
    Tree();
    ~Tree();

    // Requisito 1: Cargar CSV
    void loadFromCSV(const std::string& filename);
    bool insertNodeDirectly(Node* parentNode, Node* newNode);

    // Requisito 2: Mostrar línea de sucesión
    void showSuccessionLine();

    // Requisito 3: Sucesión automática
    void checkAndHandleSuccession();
    Node* findActualBoss(Node* current);

    // Requisito 4: Modificar datos
    Node* searchMember(int id);
    bool modifyMember(int id, std::string newName, std::string newLastName, char newGender, int newAge, bool newIsDead, bool newInJail);
};

#endif