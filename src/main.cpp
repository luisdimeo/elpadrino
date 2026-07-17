#include <iostream>
#include <string>
#include "tree.hpp" // Se comunicará con el árbol 

using namespace std;

// Función auxiliar para limpiar la pantalla de la consola (opcional y estética)
void limpiarPantalla() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

// Función auxiliar para pausar la ejecución y dejar que el usuario lea los mensajes
void pausar() {
    cout << "\nPresione Enter para continuar...";
    cin.ignore();
    cin.get();
}

int main() {
    Tree miFamilia;
    int opcion = 0;
    string archivoCSV = "bin/datos.csv"; // 

    do {
        limpiarPantalla();
        cout << "=================================================" << endl;
        cout << "        SISTEMA DE SUCESIÓN DE LA MAFIA          " << endl;
        cout << "=================================================" << endl;
        cout << " 1. Cargar miembros desde archivo CSV           " << endl;
        cout << " 2. Mostrar línea de sucesión actual (Vivos)    " << endl;
        cout << " 3. Modificar datos de un miembro               " << endl;
        cout << " 4. Simular evento (Muerte, prisión o vejez)     " << endl;
        cout << " 5. Salir del programa                          " << endl;
        cout << "=================================================" << endl;
        cout << " Seleccione una opción (1-5): ";
        
        // Validación básica de entrada numérica
        if (!(cin >> opcion)) {
            cout << "\n[!] Error: Por favor, ingrese un número válido." << endl;
            cin.clear();
            cin.ignore(10000, '\n');
            pausar();
            continue;
        }

        switch (opcion) {
            case 1: {
                limpiarPantalla();
                cout << "--- CARGAR MIEMBROS DE LA FAMILIA ---" << endl;
                cout << "Intentando cargar desde: " << archivoCSV << "..." << endl;
                
                // Llama al método de carga del árbol
                miFamilia.loadFromCSV(archivoCSV); 
                
                cout << "\n[+] Proceso de carga finalizado." << endl;
                pausar();
                break;
            }
            case 2: {
                limpiarPantalla();
                // Llama al método que muestra los miembros vivos
                miFamilia.showSuccessionLine(); 
                pausar();
                break;
            }
            case 3: {
                limpiarPantalla();
                cout << "--- MODIFICAR DATOS DE UN MIEMBRO ---" << endl;
                int id;
                cout << "Ingrese el ID del miembro a modificar: ";
                cin >> id;

                // Primero verificamos si el miembro existe
                auto miembro = miFamilia.searchMember(id);
                if (miembro == nullptr) {
                    cout << "\n[!] Error: No se encontró ningún miembro con el ID " << id << endl;
                } else {
                    string nuevoNombre, nuevoApellido;
                    char nuevoGenero;
                    int nuevaEdad;
                    bool estaMuerto, estaPreso;

                    cout << "\nMiembro encontrado. Ingrese los nuevos datos:" << endl;
                    cout << "Nuevo Nombre: ";
                    cin >> nuevoNombre;
                    cout << "Nuevo Apellido: ";
                    cin >> nuevoApellido;
                    cout << "Género (H/M): ";
                    cin >> nuevoGenero;
                    cout << "Edad: ";
                    cin >> nuevaEdad;
                    cout << "¿Está muerto? (1: Sí, 0: No): ";
                    cin >> estaMuerto;
                    cout << "¿Está en prisión? (1: Sí, 0: No): ";
                    cin >> estaPreso;

                    // Llama al método de modificación resguardando ID e ID del padre/jefe
                    bool exito = miFamilia.modifyMember(id, nuevoNombre, nuevoApellido, nuevoGenero, nuevaEdad, estaMuerto, estaPreso);
                    
                    if (exito) {
                        cout << "\n[+] Datos actualizados correctamente en el sistema." << endl;
                    } else {
                        cout << "\n[!] Hubo un problema al intentar actualizar los datos." << endl;
                    }
                }
                pausar();
                break;
            }
            case 4: {
                limpiarPantalla();
                cout << "--- SIMULAR EVENTO Y VERIFICAR SUCESIÓN ---" << endl;
                cout << "Este proceso analizará el estado del Don actual." << endl;
                cout << "Si falleció, fue encarcelado o superó los 70 años, se activará la sucesión." << endl;
                
                // Ejecuta el algoritmo de sucesión automática
                miFamilia.checkAndHandleSuccession(); 
                
                pausar();
                break;
            }
            case 5: {
                cout << "\nSaliendo del programa... Arrivederci." << endl;
                break;
            }
            default: {
                cout << "\n[!] Opción inválida. Intente de nuevo." << endl;
                pausar();
                break;
            }
        }

    } while (opcion != 5);

    return 0;
}