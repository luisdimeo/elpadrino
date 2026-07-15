#ifndef NODO_H
#define NODO_H

#include <string>

struct Nodo {
    // Datos provenientes del CSV
    int id;
    std::string nombre;
    std::string apellido;
    char genero; // 'H' o 'M'
    int edad;
    int id_jefe;
    bool esta_muerto;
    bool esta_preso;
    bool fue_jefe;
    bool es_jefe;

    // Punteros para la estructura del árbol binario de la familia
    Nodo* sucesor_A;     // Sucesor izquierdo (primer sucesor)
    Nodo* sucesor_B;     // Sucesor derecho (segundo sucesor)
    Nodo* jefe_directo;  // Enlace al "padre" o jefe superior en la jerarquía

    // Constructor para inicializar el nodo de manera limpia
    Nodo(int _id, std::string _nombre, std::string _apellido, char _genero, int _edad, int _id_jefe,
         bool _esta_muerto, bool _esta_preso, bool _fue_jefe, bool _es_jefe)
        : id(_id), nombre(_nombre), apellido(_apellido), genero(_genero), edad(_edad), id_jefe(_id_jefe),
          esta_muerto(_esta_muerto), esta_preso(_esta_preso), fue_jefe(_fue_jefe), es_jefe(_es_jefe),
          sucesor_A(nullptr), sucesor_B(nullptr), jefe_directo(nullptr) {}
};

#endif // NODO_H