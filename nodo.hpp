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
    Node(int _id, std::string _name, std::string _last_name, char _gender, int _age, int _id_boss,
         bool _is_dead, bool _in_jail, bool _was_boss, bool _is_boss) {
        id = _id;
        name = _name;
        last_name = _last_name;
        gender = _gender;
        age = _age;
        id_boss = _id_boss;
        is_dead = _is_dead;
        in_jail = _in_jail;
        was_boss = _was_boss;
        is_boss = _is_boss;
        left = nullptr;
        right = nullptr;
        parent = nullptr;
    }
};
#endif
