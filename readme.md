# Sistema de Gestión y Sucesión de la Familia (El Padrino)

Este proyecto es un prototipo desarrollado en C++ para gestionar la línea de sucesión de una familia de la mafia italiana. Utiliza una estructura de Árbol Binario Jerárquico para almacenar y administrar a los miembros de la organización.

El sistema es capaz de reaccionar dinámicamente a eventos como el fallecimiento, encarcelamiento o jubilación del Jefe Supremo (Don) y asignar automáticamente al sucesor legítimo siguiendo estrictas reglas de herencia.

## Características Principales y Requisitos Cumplidos

* **Carga Estructurada (Sin Vectores):** Lee los datos de los miembros desde un archivo `datos.csv` y los inserta en el árbol binario. Se respetó la regla estricta de no utilizar `std::vector`, implementando en su lugar una estructura de lista/cola enlazada simple para la gestión temporal de nodos.
* **Línea de Sucesión:** Recorre el árbol jerárquico mediante un algoritmo de búsqueda en anchura (BFS) y muestra la línea de sucesión actual, filtrando y mostrando únicamente a los miembros que continúan con vida y libres.
* **Algoritmo de Sucesión Automática:** Implementa un complejo sistema de herencia. Si el jefe actual muere, va a prisión o cumple más de 70 años, el sistema busca al heredero ideal basándose en:
  * Sucesores directos libres y vivos.
  * Árbol del compañero ("hermano") sucesor.
  * Árbol del compañero del jefe anterior ("tío").
  * Búsqueda ascendente de ramas disponibles.
  * Protocolo de contingencia que permite asumir a miembros en prisión si no quedan candidatos libres.
* **Modificación Segura:** Permite buscar a un miembro por su ID y modificar sus datos (nombre, edad, estado vital, etc.) protegiendo la integridad del árbol al bloquear la edición del ID y ID_Boss.
* **Ejecución Continua:** Un menú interactivo en consola que mantiene el programa en ejecución hasta que el usuario decida salir explícitamente.

---

## 📂 Estructura del Proyecto

El repositorio sigue una estricta organización de carpetas para garantizar una entrega limpia y modular:

```text
proyecto_mafia/
├── bin/
│   ├── datos.csv           # Archivo de base de datos inicial
│   └── padrino.exe         # Archivo ejecutable generado tras compilar
├── src/
│   ├── main.cpp            # Flujo principal, bucle del programa y menú interactivo
│   ├── tree.cpp            # Implementación de las reglas de negocio y algoritmos del árbol
│   ├── tree.hpp            # Cabecera con la definición de la clase de gestión del árbol
│   ├── Nodo.hpp            # Definición del nodo del árbol binario jerárquico
│   └── cola.h              # Estructura auxiliar enlazada para el recorrido BFS
└── README.md               # Documentación del proyecto

---

## 🛠️ Guía de Compilación Detallada

Para compilar el proyecto correctamente, es necesario enlazar todos los archivos de implementación (`.cpp`) de la carpeta `src/`. El compilador detectará automáticamente las cabeceras (`.hpp` y `.h`).

### Opción 1: Compilación por Terminal (Recomendado)
Abre tu terminal favorita (PowerShell, CMD o Bash), navega hasta la carpeta raíz del proyecto y ejecuta el siguiente comando:

```bash
g++ -std=c++11 src/main.cpp src/tree.cpp -o bin/padrino.exe

---

## 🚀 Instrucciones de Ejecución

.\bin\padrino.exe

---

## 🎮 Uso del Sistema

Al iniciar, el sistema cargará automáticamente los miembros desde el CSV y evaluará si el Don actual es apto para gobernar. Desde el menú principal podrás:

1. Cargar miembros desde archivo CSV: Inicializa el árbol binario leyendo el archivo estructurado ubicado en la carpeta bin/.

2. Mostrar línea de sucesión actual (Vivos): Visualiza la jerarquía de los miembros de la familia que se encuentran activos y con vida.

3. Modificar datos de un miembro: Permite corregir manualmente la ficha de cualquier integrante (restringiendo la edición de IDs para proteger la estructura).

4. Simular evento (Muerte, prisión o vejez): Registra cambios de estado en los miembros. Si el evento afecta al Don, se activa el protocolo automático de sucesión en tiempo real.

5. Salir del programa: Finaliza de forma segura la ejecución de la aplicación.


---

## 👥 Autoría y Metodología

Autores: Luis Di Meo / Luis Méndez

Control de Versiones: El proyecto se ha desarrollado utilizando Git bajo la especificación Conventional Commits (feat:, docs:, fix:, style:, chore:) para garantizar un historial de control de versiones profesional, transparente y equitativo entre ambos desarrolladores.

