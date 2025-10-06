#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

// Constantes
const string ARCHIVO_TAREAS = "tareas.txt";

// Estructura para representar una tarea
struct Tarea {
    int id;
    string descripcion;
    bool completada;
};

// Declaraciones de funciones
void mostrarMenu();
void agregarTarea(vector<Tarea>& tareas);
void mostrarTareas(const vector<Tarea>& tareas);
void eliminarTarea(vector<Tarea>& tareas);
void marcarTareaCompletada(vector<Tarea>& tareas);
void guardarTareas(const vector<Tarea>& tareas);
void cargarTareas(vector<Tarea>& tareas);

// Función principal
int main() {
    vector<Tarea> tareas;
    cargarTareas(tareas); // Cargar tareas desde el archivo

    int opcion;
    do {
        mostrarMenu();
        cin >> opcion;
        cin.ignore(); // Limpiar el buffer

        switch (opcion) {
            case 1:
                agregarTarea(tareas);
                break;
            case 2:
                mostrarTareas(tareas);
                break;
            case 3:
                marcarTareaCompletada(tareas);
                break;
            case 4:
                eliminarTarea(tareas);
                break;
            case 5:
                guardarTareas(tareas);
                cout << "Tareas guardadas. ¡Hasta luego!\n";
                break;
            default:
                cout << "Opción no válida.\n";
        }
    } while (opcion != 5);

    return 0;
}

// Implementación de funciones
void mostrarMenu() {
    cout << "\n--- Gestor de Tareas ---\n";
    cout << "1. Agregar tarea\n";
    cout << "2. Mostrar tareas\n";
    cout << "3. Marcar tarea como completada\n";
    cout << "4. Eliminar tarea\n";
    cout << "5. Salir y guardar\n";
    cout << "Selecciona una opción: ";
}

void agregarTarea(vector<Tarea>& tareas) {
    Tarea nuevaTarea;
    static int ultimoId = 0;
    if (!tareas.empty()) {
        // Buscar el mayor ID existente
        for (const auto& tarea : tareas) {
            if (tarea.id > ultimoId) {
                ultimoId = tarea.id;
            }
        }
    }
    nuevaTarea.id = ++ultimoId;
    cout << "Descripción de la tarea: ";
    getline(cin, nuevaTarea.descripcion);
    nuevaTarea.completada = false;
    tareas.push_back(nuevaTarea);
    cout << "Tarea agregada (ID: " << nuevaTarea.id << ").\n";
}

void mostrarTareas(const vector<Tarea>& tareas) {
    if (tareas.empty()) {
        cout << "No hay tareas registradas.\n";
        return;
    }
    cout << "\n--- Lista de Tareas ---\n";
    int numero = 1;
    for (const auto& tarea : tareas) {
        // Mostrar ID, estado y descripción (limpiando saltos de línea)
        cout << "ID: " << tarea.id << " | ";
        cout << (tarea.completada ? "[X] " : "[ ] ");
        string desc = tarea.descripcion;
        for (char& c : desc) {
            if (c == '\n') c = ' ';
        }
        cout << "\"" << desc << "\"" << endl;
        ++numero;
    }
}

void marcarTareaCompletada(vector<Tarea>& tareas) {
    if (tareas.empty()) {
        cout << "No hay tareas para marcar.\n";
        return;
    }
    mostrarTareas(tareas);
    int idMarcar;
    cout << "Ingresa el ID de la tarea a marcar como completada: ";
    cin >> idMarcar;
    for (auto& tarea : tareas) {
        if (tarea.id == idMarcar) {
            tarea.completada = true;
            cout << "Tarea ID " << tarea.id << " marcada como completada.\n";
            return;
        }
    }
    cout << "ID no encontrado.\n";
}

void eliminarTarea(vector<Tarea>& tareas) {
    if (tareas.empty()) {
        cout << "No hay tareas para eliminar.\n";
        return;
    }
    mostrarTareas(tareas);
    int idEliminar;
    cout << "Ingresa el ID de la tarea a eliminar: ";
    cin >> idEliminar;

    for (auto it = tareas.begin(); it != tareas.end(); ++it) {
        if (it->id == idEliminar) {
            tareas.erase(it);
            cout << "Tarea eliminada.\n";
            return;
        }
    }
    cout << "ID no encontrado.\n";
}

void guardarTareas(const vector<Tarea>& tareas) {
    ofstream archivo(ARCHIVO_TAREAS);
    if (!archivo.is_open()) {
        cout << "Error al guardar las tareas.\n";
        return;
    }
    for (const auto& tarea : tareas) {
        archivo << tarea.id << "," << tarea.descripcion << "," << tarea.completada << endl;
    }
    archivo.close();
}

void cargarTareas(vector<Tarea>& tareas) {
    ifstream archivo(ARCHIVO_TAREAS);
    if (!archivo.is_open()) return;

    string linea;
    while (getline(archivo, linea)) {
        Tarea tarea;
        size_t pos1 = linea.find(',');
        size_t pos2 = linea.find(',', pos1 + 1);

        tarea.id = stoi(linea.substr(0, pos1));
        tarea.descripcion = linea.substr(pos1 + 1, pos2 - pos1 - 1);
        tarea.completada = stoi(linea.substr(pos2 + 1));

        tareas.push_back(tarea);
    }
    archivo.close();
}