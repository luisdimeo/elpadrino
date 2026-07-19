#ifndef COLA_H
#define COLA_H

#include "Nodo.hpp"

struct NodoCola {
    Node* nodo_arbol;
    NodoCola* siguiente;
    NodoCola(Node* nodo) : nodo_arbol(nodo), siguiente(nullptr) {}
};

class Cola {
private:
    NodoCola* primero;
    NodoCola* ultimo;

public:
    Cola() : primero(nullptr), ultimo(nullptr) {}

    ~Cola() {
        while (!esta_vacia()) {
            desencolar();
        }
    }

    bool esta_vacia() const {
        return primero == nullptr;
    }

    void encolar(Node* nodo) {
        if (nodo == nullptr) return;
        NodoCola* temporal = new NodoCola(nodo);
        if (esta_vacia()) {
            primero = ultimo = temporal;
            return;
        }
        ultimo->siguiente = temporal;
        ultimo = temporal;
    }

    Node* desencolar() {
        if (esta_vacia()) return nullptr;
        NodoCola* temporal = primero;
        Node* nodo = temporal->nodo_arbol;
        primero = primero->siguiente;
        if (primero == nullptr) {
            ultimo = nullptr;
        }
        delete temporal;
        return nodo;
    }
};

#endif // COLA_H