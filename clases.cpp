#include "clases.h"
#include <iostream>     // Para entrada/salida estándar
#include <limits>       // Para limpiar el buffer de entrada en caso de errores
using namespace std;

//
// FUNCIÓN AUXILIAR: leer_entero
// Esta función se encarga de validar que el usuario ingrese efectivamente un número entero.
// En caso contrario, limpia el buffer y vuelve a pedir el dato.
//
int leer_entero() {
    int valor;
    while (true) {
        cin >> valor;
        if (cin.fail()) {  // Si se ingresó un carácter no válido (letra, símbolo, etc.)
            cin.clear();   // Limpia el estado de error de cin
            cin.ignore(numeric_limits<streamsize>::max(), '\n');  // Descarta lo que quedó en el buffer
            cout << "Entrada no válida. Por favor, ingrese un número: ";
        } else {
            return valor;  // Si el valor es válido, lo retorna
        }
    }
}

//
// IMPLEMENTACIÓN DE LA CLASE BASE DEL CODIGO: Item
//

Item::Item(int id, int nivel_taxonomico, int categoria, string enunciado, int tiempo_estimado)
    : id(id), nivel_taxonomico(nivel_taxonomico), categoria(categoria), enunciado(enunciado), tiempo_estimado(tiempo_estimado) {}

Item::~Item() {}

int Item::get_id() {
    return id;
}

int Item::get_nivel_taxonomico() {
    return nivel_taxonomico;
}

int Item::get_categoria() {
    return categoria;
}

string Item::get_enunciado() {
    return enunciado;
}

int Item::get_tiempo_estimado() {
    return tiempo_estimado;
}

void Item::set_enunciado(string nuevo_enunciado) {
    enunciado = nuevo_enunciado;
}

void Item::set_tiempo_estimado(int nuevo_tiempo) {
    tiempo_estimado = nuevo_tiempo;
}

//
// IMPLEMENTACIÓN DE LA CLASE: PreguntaVerdaderoFalso
//

// Constructor:se crea una pregunta de tipo Verdadero/Falso
PreguntaVerdaderoFalso::PreguntaVerdaderoFalso(int id, int nivel_taxonomico, string enunciado, bool respuesta, string justificacion, int tiempo_estimado)
    : Item(id, nivel_taxonomico, 1, enunciado, tiempo_estimado), respuesta_correcta(respuesta), justificacion(justificacion) {}

//aqui muestra la información de la pregunta Verdadero/Falso
void PreguntaVerdaderoFalso::mostrar() {
    cout << "ID: " << get_id() << " [Verdadero/Falso] Nivel: " << get_nivel_taxonomico() << endl;
    cout << "Enunciado: " << get_enunciado() << endl;
    cout << "Tiempo estimado: " << get_tiempo_estimado() << " minutos" << endl;
    cout << "Respuesta correcta: " << (respuesta_correcta ? "Verdadero" : "Falso") << endl;
    if (!respuesta_correcta) cout << "Justificación: " << justificacion << endl;
    cout << "--------------------------" << endl;
}

//
// IMPLEMENTACIÓN DE LA CLASE: PreguntaAlternativa
//

// Constructor: Aqui se crea una pregunta de tipo alternativa múltiple
PreguntaAlternativa::PreguntaAlternativa(int id, int nivel_taxonomico, string enunciado, vector<string> alternativas, int correcta, int tiempo_estimado)
    : Item(id, nivel_taxonomico, 2, enunciado, tiempo_estimado), alternativas(alternativas), correcta(correcta) {}

//aqui muestra la información de la pregunta con alternativas
void PreguntaAlternativa::mostrar() {
    cout << "ID: " << get_id() << " [Alternativa] Nivel: " << get_nivel_taxonomico() << endl;
    cout << "Enunciado: " << get_enunciado() << endl;
    cout << "Tiempo estimado: " << get_tiempo_estimado() << " minutos" << endl;
    for (size_t i = 0; i < alternativas.size(); ++i) {
        cout << i + 1 << ". " << alternativas[i];
        if (i == correcta) cout << " (Correcta)";
        cout << endl;
    }
    cout << "--------------------------" << endl;
}

//
// IMPLEMENTACIÓN DE LA CLASE CONTROLADORA: Sistema_Evaluacion
//

// Constructor: inicializa el sistema con ID inicial 1
Sistema_Evaluacion::Sistema_Evaluacion() : next_id(1) {}

// Destructor: libera memoria de todos los ítems creados dinámicamente
Sistema_Evaluacion::~Sistema_Evaluacion() {
    for (Item* item : items) delete item;
}

// Crea un nuevo ítem (VF o alternativa) solicitando los datos necesarios al usuario
void Sistema_Evaluacion::crear_item() {
    int tipo;
    cout << "Selecciona tipo de pregunta (1: Verdadero/Falso, 2: Alternativa): ";
    tipo = leer_entero();
    cin.ignore();

    string enunciado;
    int nivel, tiempo;
    cout << "Ingrese enunciado: ";
    getline(cin, enunciado);
    cout << "Ingrese nivel taxonómico (1 a 6): ";
    nivel = leer_entero();
    cout << "Ingrese tiempo estimado de respuesta (en minutos): ";
    tiempo = leer_entero();

    // Pregunta tipo Verdadero/Falso
    if (tipo == 1) {
        bool respuesta;
        string justificacion;
        cout << "Respuesta correcta (1: Verdadero, 0: Falso): ";
        respuesta = leer_entero();
        cin.ignore();
        if (!respuesta) {
            cout << "Ingrese justificación: ";
            getline(cin, justificacion);
        }
        items.push_back(new PreguntaVerdaderoFalso(next_id++, nivel, enunciado, respuesta, justificacion, tiempo));
    }
    // Pregunta tipo Alternativa
    else if (tipo == 2) {
        int cantidad;
        cout << "Cantidad de alternativas: ";
        cantidad = leer_entero();
        cin.ignore();
        vector<string> alternativas;
        for (int i = 0; i < cantidad; ++i) {
            string alt;
            cout << "Alternativa " << (i + 1) << ": ";
            getline(cin, alt);
            alternativas.push_back(alt);
        }
        int correcta;
        cout << "Número de la alternativa correcta (1 a " << cantidad << "): ";
        correcta = leer_entero();
        items.push_back(new PreguntaAlternativa(next_id++, nivel, enunciado, alternativas, correcta - 1, tiempo));
    } else {
        cout << "Tipo no válido." << endl;
    }
}

// se muestran todos los ítems registrados en el sistema
void Sistema_Evaluacion::mostrar_items() {
    for (Item* item : items) item->mostrar();
}

// Permite actualizar el enunciado y el tiempo estimado de un ítem existente
void Sistema_Evaluacion::actualizar_item() {
    int id;
    cout << "Ingrese ID del ítem a actualizar: ";
    id = leer_entero();
    for (Item* item : items) {
        if (item->get_id() == id) {
            cin.ignore();
            string nuevo_enunciado;
            int nuevo_tiempo;
            cout << "Ingrese nuevo enunciado: ";
            getline(cin, nuevo_enunciado);
            cout << "Ingrese nuevo tiempo estimado (en minutos): ";
            nuevo_tiempo = leer_entero();
            item->set_enunciado(nuevo_enunciado);
            item->set_tiempo_estimado(nuevo_tiempo);
            cout << "Actualizado." << endl;
            return;
        }
    }
    cout << "Ítem no encontrado." << endl;
}

//aqui permite eliminar un ítem por su ID
void Sistema_Evaluacion::borrar_item() {
    int id;
    cout << "Ingrese ID del ítem a eliminar: ";
    id = leer_entero();
    for (auto it = items.begin(); it != items.end(); ++it) {
        if ((*it)->get_id() == id) {
            delete *it;
            items.erase(it);
            cout << "Eliminado correctamente." << endl;
            return;
        }
    }
    cout << "Ítem no encontrado." << endl;
}

//aqui muestra un ítem específico por su ID
void Sistema_Evaluacion::consultar_item() {
    int id;
    cout << "Ingrese ID del ítem a consultar: ";
    id = leer_entero();
    for (Item* item : items) {
        if (item->get_id() == id) {
            item->mostrar();
            return;
        }
    }
    cout << "Ítem no encontrado." << endl;
}

// Busca y muestra todos los ítems que correspondan a un nivel taxonómico dado
void Sistema_Evaluacion::buscar_items_por_taxonomia() {
    int nivel;
    cout << "Ingrese nivel taxonómico a buscar: ";
    nivel = leer_entero();
    for (Item* item : items) {
        if (item->get_nivel_taxonomico() == nivel) {
            item->mostrar();
        }
    }
}

// Genera una evaluación mostrando una cantidad de preguntas y suma el tiempo total estimado
void Sistema_Evaluacion::generar_evaluacion() {
    int cantidad;
    cout << "Cantidad de preguntas para evaluación: ";
    cantidad = leer_entero();
    if (cantidad > items.size()) {
        cout << "No hay suficientes ítems." << endl;
        return;
    }

    int tiempo_total = 0;  // Acumulador de tiempo
    for (int i = 0; i < cantidad; ++i) {
        items[i]->mostrar();
        tiempo_total += items[i]->get_tiempo_estimado();
    }

    // Muestra el tiempo total estimado
    cout << "Tiempo total estimado para la evaluación: " << tiempo_total << " minutos" << endl;
}

// Menú principal del sistema, usa estructura switch para acceder a las funcionalidades
void Sistema_Evaluacion::menu() {
    int opcion;
    do {
        cout << "\n===== SISTEMA DE EVALUACION =====\n";
        cout << "1. Crear ítem\n";
        cout << "2. Mostrar todos los ítems\n";
        cout << "3. Actualizar ítem\n";
        cout << "4. Borrar ítem\n";
        cout << "5. Consultar ítem por ID\n";
        cout << "6. Buscar ítems por nivel taxonómico\n";
        cout << "7. Generar evaluación\n";
        cout << "0. Salir\n";
        cout << "Seleccione una opción: ";
        opcion = leer_entero();

        // SWITCH: estructura clara para manejar múltiples opciones
        switch (opcion) {
            case 1: crear_item(); break;
            case 2: mostrar_items(); break;
            case 3: actualizar_item(); break;
            case 4: borrar_item(); break;
            case 5: consultar_item(); break;
            case 6: buscar_items_por_taxonomia(); break;
            case 7: generar_evaluacion(); break;
            case 0: cout << "Saliendo del sistema..." << endl; break;
            default: cout << "Opción no válida." << endl;
        }

    } while (opcion != 0);  // El menú se repite hasta que se elige salir (opción 0)
}
