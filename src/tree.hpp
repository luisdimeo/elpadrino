#ifndef TREE_HPP
#define TREE_HPP

#include "Nodo.hpp"
#include "Cola.h" // <-- Vinculamos cola aquí
#include <string>

class Tree {
private:
    Node* root; 

    struct ListNode {
        Node* treeNode;
        ListNode* next;
        ListNode(Node* node) : treeNode(node), next(nullptr) {}
    };

    ListNode* pendingListHead; 

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

    void loadFromCSV(const std::string& filename);
    bool insertNodeDirectly(Node* parentNode, Node* newNode);
    void showSuccessionLine();
    void checkAndHandleSuccession();
    Node* findActualBoss(Node* current);
    Node* searchMember(int id);
    bool modifyMember(int id, std::string newName, std::string newLastName, char newGender, int newAge, bool newIsDead, bool newInJail);
};

#endif