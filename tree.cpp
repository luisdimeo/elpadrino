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

void Tree::insertPending(Node* node) {
    ListNode* newNode = new ListNode(node);
    newNode->next = pendingListHead;
    pendingListHead = newNode;
}

Node* Tree::findNodeInTree(Node* current, int id) {
    if (current == nullptr) return nullptr;
    if (current->id == id) return current;

    Node* foundLeft = findNodeInTree(current->left, id);
    if (foundLeft != nullptr) return foundLeft;

    return findNodeInTree(current->right, id);
}

bool Tree::insertNodeDirectly(Node* parentNode, Node* newNode) {
    if (parentNode->left == nullptr) {
        parentNode->left = newNode;
        newNode->parent = parentNode;
        return true;
    } else if (parentNode->right == nullptr) {
        parentNode->right = newNode;
        newNode->parent = parentNode;
        return true;
    }
    return false; // Ya tiene 2 sucesores directos
}

void Tree::resolvePendingNodes() {
    bool progress = true;
    while (progress) {
        progress = false;
        ListNode* prev = nullptr;
        ListNode* current = pendingListHead;

        while (current != nullptr) {
            Node* parentNode = findNodeInTree(root, current->treeNode->id_boss);
            if (parentNode != nullptr) {
                if (insertNodeDirectly(parentNode, current->treeNode)) {
                    ListNode* toDelete = current;
                    if (prev == nullptr) {
                        pendingListHead = current->next;
                    } else {
                        prev->next = current->next;
                    }
                    current = current->next;
                    delete toDelete;
                    progress = true;
                    continue;
                }
            }
            prev = current;
            current = current->next;
        }
    }
}

// Carga de archivo CSV sin usar vectores
void Tree::loadFromCSV(const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cout << "Error: No se pudo abrir el archivo " << filename << endl;
        return;
    }

    string line;
    getline(file, line); // Ignorar cabecera

    while (getline(file, line)) {
        if (line.empty()) continue;

        stringstream ss(line);
        string item;
        
        int id, age, id_boss;
        string name, last_name;
        char gender;
        bool is_dead, in_jail, was_boss, is_boss;

        getline(ss, item, ','); id = stoi(item);
        getline(ss, name, ',');
        getline(ss, last_name, ',');
        getline(ss, item, ','); gender = item[0];
        getline(ss, item, ','); age = stoi(item);
        getline(ss, item, ','); id_boss = (item.empty() || item == "0") ? 0 : stoi(item);
        getline(ss, item, ','); is_dead = (stoi(item) == 1);
        getline(ss, item, ','); in_jail = (stoi(item) == 1);
        getline(ss, item, ','); was_boss = (stoi(item) == 1);
        getline(ss, item, ','); is_boss = (stoi(item) == 1);

        Node* newNode = new Node(id, name, last_name, gender, age, id_boss, is_dead, in_jail, was_boss, is_boss);

        if (id_boss == 0) {
            root = newNode;
        } else {
            Node* parentNode = findNodeInTree(root, id_boss);
            if (parentNode != nullptr) {
                if (!insertNodeDirectly(parentNode, newNode)) {
                    delete newNode;
                }
            } else {
                insertPending(newNode);
            }
        }
    }
    file.close();
    resolvePendingNodes();
}
