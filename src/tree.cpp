#include "tree.hpp" 
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

Tree::Tree() {
    root = nullptr;
    pendingListHead = nullptr;
}

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
    return false; 
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

void Tree::loadFromCSV(const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cout << "Error: No se pudo abrir el archivo " << filename << endl;
        return;
    }

    string line;
    getline(file, line); 

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

void Tree::showSuccessionLine() {
    if (root == nullptr) {
        cout << "La familia no tiene miembros registrados." << endl;
        return;
    }
    cout << "\n--- MIEMBROS VIVOS DE LA FAMILIA ---" << endl;
    printSuccessionRecursive(root);
    cout << "------------------------------------" << endl;
}

void Tree::printSuccessionRecursive(Node* current) {
    if (current == nullptr) return;

    if (!current->is_dead) {
        cout << "ID: " << current->id << " | " << current->name << " " << current->last_name 
             << " | Edad: " << current->age << " | ";
        if (current->is_boss) {
            cout << "[BOSS ACTUAL]";
        } else if (current->in_jail) {
            cout << "[EN PRISION (Sucesion bloqueada)]";
        } else {
            cout << "[Sucesor Libre]";
        }
        cout << endl;
    }

    printSuccessionRecursive(current->left);
    printSuccessionRecursive(current->right);
}

Node* Tree::searchMember(int id) {
    return findNodeInTree(root, id);
}

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

Node* Tree::findFirstFreeSuccessor(Node* current, bool allowJail) {
    if (current == nullptr) return nullptr;

    if (!current->is_dead) {
        if (allowJail || !current->in_jail) {
            return current;
        }
    }

    Node* foundLeft = findFirstFreeSuccessor(current->left, allowJail);
    if (foundLeft != nullptr) return foundLeft;

    return findFirstFreeSuccessor(current->right, allowJail);
}

Node* Tree::findNewBossRules(Node* deadBoss) {
    if (deadBoss == nullptr) return nullptr;

    Node* candidate = nullptr;

    // Regla 1: Primer sucesor libre de su propio árbol
    candidate = findFirstFreeSuccessor(deadBoss->left);
    if (candidate != nullptr) return candidate;
    candidate = findFirstFreeSuccessor(deadBoss->right);
    if (candidate != nullptr) return candidate;

    Node* formerBoss = deadBoss->parent;
    if (formerBoss != nullptr) {
        Node* sibling = (formerBoss->left == deadBoss) ? formerBoss->right : formerBoss->left;

        if (sibling != nullptr) {
            // Regla 2: Primer sucesor del árbol de su hermano
            candidate = findFirstFreeSuccessor(sibling);
            if (candidate != nullptr) return candidate;

            // Regla 3: Hermano libre, vivo y sin descendencia
            if (!sibling->is_dead && !sibling->in_jail && sibling->left == nullptr && sibling->right == nullptr) {
                return sibling;
            }
        }

        // Regla 4: Árbol del tío (compañero del anterior jefe)
        Node* grandBoss = formerBoss->parent;
        if (grandBoss != nullptr) {
            Node* uncle = (grandBoss->left == formerBoss) ? grandBoss->right : grandBoss->left;
            if (uncle != nullptr) {
                candidate = findFirstFreeSuccessor(uncle);
                if (uncle != nullptr) return candidate;

                if (!uncle->is_dead && !uncle->in_jail && uncle->left == nullptr && uncle->right == nullptr) {
                    return uncle;
                }
            }
        }
    }

    // =========================================================================
    // REGLA 5 POTENCIADA: ¡Uso de la Cola propia de Luis! (Búsqueda BFS de jefes)
    // =========================================================================
    Node* temp = deadBoss->parent;
    Cola miCola;
    
    // Encolamos los niveles superiores para buscar al jefe idóneo más cercano
    while (temp != nullptr) {
        miCola.encolar(temp);
        temp = temp->parent;
    }

    while (!miCola.esta_vacia()) {
        Node* currentBossNode = miCola.desencolar();
        
        // Evaluamos si el jefe extraído tiene dos sucesores directos
        if (currentBossNode->left != nullptr && currentBossNode->right != nullptr) {
            candidate = findFirstFreeSuccessor(currentBossNode->left);
            if (candidate != nullptr) return candidate;
            candidate = findFirstFreeSuccessor(currentBossNode->right);
            if (candidate != nullptr) return candidate;
        }
    }

    // Regla 6: Crisis absoluta (Permitir sucesores en prisión)
    candidate = findFirstFreeSuccessor(deadBoss->left, true);
    if (candidate != nullptr) return candidate;
    candidate = findFirstFreeSuccessor(deadBoss->right, true);
    if (candidate != nullptr) return candidate;

    temp = deadBoss->parent;
    while (temp != nullptr) {
        if (!temp->is_dead) return temp;
        candidate = findFirstFreeSuccessor(temp->left, true);
        if (candidate != nullptr) return candidate;
        candidate = findFirstFreeSuccessor(temp->right, true);
        if (candidate != nullptr) return candidate;
        temp = temp->parent;
    }

    return nullptr;
}

Node* Tree::findActualBoss(Node* current) {
    if (current == nullptr) return nullptr;
    if (current->is_boss) return current;

    Node* foundLeft = findActualBoss(current->left);
    if (foundLeft != nullptr) return foundLeft;

    return findActualBoss(current->right);
}

void Tree::checkAndHandleSuccession() {
    Node* currentBoss = findActualBoss(root);

    if (currentBoss == nullptr) {
        if (root != nullptr) {
            root->is_boss = true;
            currentBoss = root;
        } else {
            return;
        }
    }
    if (currentBoss->is_dead || currentBoss->in_jail || currentBoss->age > 70) {
        cout << "\n=============================================" << endl;
        cout << "   ATENCION: EL CAPO HA DEJADO EL PUESTO" << endl;
        cout << "=============================================" << endl;
        cout << "Nombre: " << currentBoss->name << " " << currentBoss->last_name << endl;
        cout << "Causa: ";
        if (currentBoss->is_dead) cout << "Fallecimiento." << endl;
        else if (currentBoss->in_jail) cout << "Encarcelamiento." << endl;
        else cout << "Retiro por vejez (" << currentBoss->age << " anos)." << endl;

        Node* newBoss = findNewBossRules(currentBoss);

        if (newBoss != nullptr) {
            currentBoss->is_boss = false;
            currentBoss->was_boss = true;
            newBoss->is_boss = true;
            cout << "---------------------------------------------" << endl;
            cout << ">>> EL NUEVO DON ES: " << newBoss->name << " " << newBoss->last_name 
                 << " (ID: " << newBoss->id << ") <<<" << endl;
            cout << "=============================================\n" << endl;
        } else {
            cout << "La familia ha quedado sin un heredero apto." << endl;
        }
    }
}