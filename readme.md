# Sistema de Gestión y Sucesión de la Familia (el padrino)

Este proyecto es un prototipo desarrollado en **C++** para gestionar la línea de sucesión de una familia de la mafia italiana. Utiliza una estructura de **Árbol Binario Jerárquico** para almacenar y administrar a los miembros de la organización. 

El sistema es capaz de reaccionar dinámicamente a eventos como el fallecimiento, encarcelamiento o jubilación del Jefe Supremo (Don) y asignar automáticamente al sucesor legítimo siguiendo estrictas reglas de herencia.

## Características Principales y Requisitos Cumplidos

1. **Carga Estructurada (Sin Vectores):** Lee los datos de los miembros desde un archivo `datos.csv` y los inserta en el árbol binario. Se respetó la regla estricta de **no utilizar `std::vector`**, implementando en su lugar una lista enlazada simple para la gestión temporal de nodos desordenados.
2. **Línea de Sucesión:** Recorre el árbol jerárquico y muestra la línea de sucesión actual, filtrando y mostrando únicamente a los miembros que continúan con vida.
3. **Algoritmo de Sucesión Automática:** Implementa un complejo sistema de herencia. Si el jefe actual muere, va a prisión o cumple más de 70 años, el sistema busca al heredero ideal basándose en:
   * Sucesores directos libres y vivos.
   * Árbol del compañero ("hermano") sucesor.
   * Árbol del compañero del jefe anterior ("tío").
   * Búsqueda ascendente de ramas disponibles.
   * Protocolo de contingencia que permite asumir a miembros en prisión si no quedan candidatos libres.
4. **Modificación Segura:** Permite buscar a un miembro por su `id` y modificar sus datos (nombre, edad, estado vital, etc.) protegiendo la integridad del árbol al bloquear la edición del `id` y `id_boss`.
5. **Ejecución Continua:** Un menú interactivo en consola que mantiene el programa en ejecución hasta que el usuario decida salir explícitamente.

## 📂 Estructura del Proyecto

El repositorio sigue una estricta organización de carpetas:
```text
elpadrino
├── bin/
│   ├── datos.csv           # Archivo de base de datos inicial
│   └── (elpadrino_system)      # Archivo ejecutable generado tras compilar
├── src/
│   ├── cola.h            # Estructura del Nodo del árbol binario
│   ├── Nodo.h            # Declaración de la clase Tree
│   ├── main.cpp            # Implementación de las reglas de negocio y algoritmos
│   └── tree.cpp
│   └── tree.hpp            # Bucle del programa y menú interactivo
└── README.md               # Documentación del proyecto

Instrucciones de Compilación

Abre tu terminal en la carpeta raíz del proyecto (mi_proyecto_mafia/) y ejecuta el siguiente comando:
g++ -std=c++11 src/main.cpp src/tree.cpp -o bin/elpadrino_system.exe

Instrucciones de Ejecución
Una vez compilado, el ejecutable se guardará en la carpeta bin/. Para iniciar el sistema, ejecuta:
.\bin\elpadrino_system.exe

Uso del Sistema
Al iniciar, el sistema cargará automáticamente los miembros y evaluará si el Don actual es apto para gobernar. Desde el menú principal podrás:

1.Mostrar línea de sucesión: Visualizar a todos los miembros vivos de la familia.

2.Simular evento: Registrar el fallecimiento, encarcelamiento o aumento de edad de un miembro. Si el evento afecta al jefe, verás el protocolo de sucesión en acción.

3.Modificar datos: Corregir manualmente la ficha de un miembro (excepto ID y Jefe).

4.Salir: Terminar la ejecución del programa.

Autoría y Metodología
Autores: [Luis Di Meo/ Luis Mendez]

Control de Versiones: El proyecto se ha desarrollado utilizando Git bajo la especificación Conventional Commits (feat, docs, fix, chore) para un historial de control de versiones profesional y ordenado.