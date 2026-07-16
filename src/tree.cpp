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

// Función auxiliar para limpiar el árbol 
void Tree::clearTree(Node* current) {
    if (current != nullptr) {
        clearTree(current->left);
        clearTree(current->right);
        delete current;
    }
}

// ==========================================
// MÉTODOS DE LA FASE 3: CARGA DEL CSV
// ==========================================

// Buscar un nodo por ID de forma recursiva (¡Indispensable para poder cargar!)
Node* Tree::findNodeInTree(Node* current, int id) {
    if (current == nullptr) return nullptr;
    if (current->id == id) return current;

    Node* found = findNodeInTree(current->left, id);
    if (found != nullptr) return found;

    return findNodeInTree(current->right, id);
}

// Insertar en la lista de pendientes si el jefe no existe todavía en el árbol
void Tree::insertPending(Node* node) {
    ListNode* newNode = new ListNode(node);
    newNode->next = pendingListHead;
    pendingListHead = newNode;
}

// Intentar conectar los nodos que quedaron pendientes
void Tree::resolvePendingNodes() {
    bool movement = true;
    while (movement) {
        movement = false;
        ListNode* prev = nullptr;
        ListNode* curr = pendingListHead;

        while (curr != nullptr) {
            Node* potentialParent = findNodeInTree(root, curr->treeNode->id_boss);
            if (potentialParent != nullptr) {
                // Insertar en el árbol
                curr->treeNode->parent = potentialParent;
                if (potentialParent->left == nullptr) {
                    potentialParent->left = curr->treeNode;
                } else {
                    potentialParent->right = curr->treeNode;
                }

                // Remover de la lista de pendientes
                ListNode* toDelete = curr;
                if (prev == nullptr) {
                    pendingListHead = curr->next;
                } else {
                    prev->next = curr->next;
                }
                curr = curr->next;
                delete toDelete; // Borramos el ListNode de apoyo, NO el Node de la mafia.
                movement = true;
            } else {
                prev = curr;
                curr = curr->next;
            }
        }
    }
}

// Carga el CSV y resuelve las dependencias
void Tree::loadFromCSV(const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cout << "Error: No se pudo abrir el archivo " << filename << endl;
        return;
    }

    string line;
    // Ignorar cabecera
    getline(file, line);

    while (getline(file, line)) {
        if (line.empty()) continue;

        stringstream ss(line);
        string temp;

        int id, age, id_boss;
        string name, last_name;
        char gender;
        bool is_dead, in_jail, was_boss, is_boss;

        getline(ss, temp, ','); id = stoi(temp);
        getline(ss, name, ',');
        getline(ss, last_name, ',');
        getline(ss, temp, ','); gender = temp[0];
        getline(ss, temp, ','); age = stoi(temp);
        getline(ss, temp, ','); id_boss = stoi(temp);
        getline(ss, temp, ','); is_dead = (stoi(temp) == 1);
        getline(ss, temp, ','); in_jail = (stoi(temp) == 1);
        getline(ss, temp, ','); was_boss = (stoi(temp) == 1);
        getline(ss, temp, ','); is_boss = (stoi(temp) == 1);

        Node* newNode = new Node(id, name, last_name, gender, age, id_boss, is_dead, in_jail, was_boss, is_boss);

        if (id_boss == 0) {
            root = newNode; // Es el Capo di tutti capi
        } else {
            Node* parentNode = findNodeInTree(root, id_boss);
            if (parentNode != nullptr) {
                newNode->parent = parentNode;
                if (parentNode->left == nullptr) {
                    parentNode->left = newNode;
                } else {
                    parentNode->right = newNode;
                }
            } else {
                // Si el jefe no se ha cargado todavía, va a la lista de pendientes
                insertPending(newNode);
            }
        }
    }
    file.close();
    // Resolver los que quedaron huérfanos temporalmente
    resolvePendingNodes();
}




// MÉTODOS DE LA FASE 4: VISUALIZACIÓN Y EDICIÓN

// Buscar miembro por ID para edición (interfaz pública)
Node* Tree::searchMember(int id) {
    return findNodeInTree(root, id);
}

// Mostrar línea de sucesión (Solo vivos) en Preorden
void Tree::printSuccessionRecursive(Node* current) {
    if (current == nullptr) return;

    if (!current->is_dead) {
        cout << "- " << current->name << " " << current->last_name 
             << " [ID: " << current->id << "] "
             << (current->is_boss ? " (JEFE ACTUAL)" : "") 
             << (current->in_jail ? " [EN PRISIÓN]" : "") << endl;
    }

    printSuccessionRecursive(current->left);
    printSuccessionRecursive(current->right);
}

void Tree::showSuccessionLine() {
    if (root == nullptr) {
        cout << "La familia no tiene miembros cargados." << endl;
        return;
    }
    cout << "--- LINEA DE SUCESIÓN ACTUAL (MIEMBROS VIVOS) ---" << endl;
    printSuccessionRecursive(root);
    cout << "------------------------------------------------" << endl;
}

// Modificar datos (protegiendo id e id_boss)
bool Tree::modifyMember(int id, string newName, string newLastName, char newGender, int newAge, bool newIsDead, bool newInJail) {
    Node* member = searchMember(id);
    if (member == nullptr) return false;

    member->name = newName;
    member->last_name = newLastName;
    member->gender = newGender;
    member->age = newAge;
    member->is_dead = newIsDead;
    member->in_jail = newInJail;

    return true;
}