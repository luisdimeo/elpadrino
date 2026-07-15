#ifndef COLA_H
#define COLA_H

#include "Nodo.h"

// Nodo interno de la cola para poder enlazar los elementos
struct NodoCola {
    Nodo* nodo_arbol;
    NodoCola* siguiente;
    NodoCola(Nodo* nodo) : nodo_arbol(nodo), siguiente(nullptr) {}
};

class Cola {
private:
    NodoCola* primero;
    NodoCola* ultimo;

public:
    Cola() : primero(nullptr), ultimo(nullptr) {}

    // Destructor para evitar fugas de memoria (limpia la cola al terminar)
    ~Cola() {
        while (!esta_vacia()) {
            desencolar();
        }
    }

    bool esta_vacia() const {
        return primero == nullptr;
    }

    // Insertar un miembro al final de la cola (para procesamiento)
    void encolar(Nodo* nodo) {
        NodoCola* temporal = new NodoCola(nodo);
        if (esta_vacia()) {
            primero = ultimo = temporal;
            return;
        }
        ultimo->siguiente = temporal;
        ultimo = temporal;
    }

    // Sacar al miembro que va de primero
    Nodo* desencolar() {
        if (esta_vacia()) return nullptr;
        NodoCola* temporal = primero;
        Nodo* nodo = temporal->nodo_arbol;
        primero = primero->siguiente;
        if (primero == nullptr) {
            ultimo = nullptr;
        }
        delete temporal;
        return nodo;
    }
};

#endif // COLA_H