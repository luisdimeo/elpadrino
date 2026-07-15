#ifndef NODE_HPP
#define NODE_HPP

#include <string>

struct Node {
    // Datos personales
    int id;
    std::string name;
    std::string last_name;
    char gender; // 'H' o 'M'
    int age;
    int id_boss;

    // Estado en la organización
    bool is_dead;
    bool in_jail;
    bool was_boss;
    bool is_boss;

    // Punteros del Árbol Binario
    Node* left;   // Primer sucesor
    Node* right;  // Segundo sucesor
    Node* parent; // Jefe directo (Padre en el árbol)
};

