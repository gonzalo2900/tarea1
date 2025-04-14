#include <iostream>
#include "clases.h"
using namespace std;

//
// IMPLEMENTACIÓN DE LA CLASE BASE: Item
//
Item::Item(int id, int nivel_taxonomico, int categoria, string enunciado) {
    this->id = id;
    this->nivel_taxonomico = nivel_taxonomico;
    this->categoria = categoria;
    this->enunciado = enunciado;
}

Item::~Item() {}

// Métodos getter
int Item::get_id() { return id; }
int Item::get_nivel_taxonomico() { return nivel_taxonomico; }
int Item::get_categoria() { return categoria; }
string Item::get_enunciado() { return enunciado; }

// Método setter
void Item::set_enunciado(string nuevo_enunciado) {
    enunciado = nuevo_enunciado;
}

//
// IMPLEMENTACIÓN DE: PreguntaVerdaderoFalso
//
PreguntaVerdaderoFalso::PreguntaVerdaderoFalso(int id, int nivel_taxonomico, string enunciado, bool respuesta, string justificacion)
    : Item(id, nivel_taxonomico, 1, enunciado) {
    this->respuesta_correcta = respuesta;
    this->justificacion = justificacion;
}

void PreguntaVerdaderoFalso::mostrar() {
    cout << "ID: " << get_id() << " [Verdadero/Falso] Nivel: " << get_nivel_taxonomico() << endl;
    cout << "Enunciado: " << get_enunciado() << endl;
    cout << "Respuesta correcta: " << (respuesta_correcta ? "Verdadero" : "Falso") << endl;
    if (!respuesta_correcta) {
        cout << "Justificación: " << justificacion << endl;
    }
    cout << "--------------------------" << endl;
}

//
// IMPLEMENTACIÓN DE: PreguntaAlternativa
//
PreguntaAlternativa::PreguntaAlternativa(int id, int nivel_taxonomico, string enunciado, vector<string> alternativas, int correcta)
    : Item(id, nivel_taxonomico, 2, enunciado) {
    this->alternativas = alternativas;
    this->correcta = correcta;
}

void PreguntaAlternativa::mostrar() {
    cout << "ID: " << get_id() << " [Alternativa] Nivel: " << get_nivel_taxonomico() << endl;
    cout << "Enunciado: " << get_enunciado() << endl;
    for (size_t i = 0; i < alternativas.size(); ++i) {
        cout << i + 1 << ". " << alternativas[i];
        if (i == correcta) cout << " (Correcta)";
        cout << endl;
    }
    cout << "--------------------------" << endl;
}

//
// IMPLEMENTACIÓN DE: Sistema_Evaluacion
//
Sistema_Evaluacion::Sistema_Evaluacion() {
    next_id = 1;
}

Sistema_Evaluacion::~Sistema_Evaluacion() {
    for (Item* item : items) {
        delete item;
    }
}

void Sistema_Evaluacion::crear_item() {
    int tipo;
    cout << "Selecciona tipo de pregunta (1: Verdadero/Falso, 2: Alternativa): ";
    cin >> tipo;

    cin.ignore();
    string enunciado;
    int nivel;
    cout << "Ingrese enunciado: ";
    getline(cin, enunciado);
    cout << "Ingrese nivel taxonomico (1 a 5): ";
    cin >> nivel;

    if (tipo == 1) {
        bool respuesta;
        string justificacion;
        cout << "Respuesta correcta (1: Verdadero, 0: Falso): ";
        cin >> respuesta;
        cin.ignore();
        if (!respuesta) {
            cout << "Ingrese justificacion: ";
            getline(cin, justificacion);
        }
        items.push_back(new PreguntaVerdaderoFalso(next_id++, nivel, enunciado, respuesta, justificacion));
    } else if (tipo == 2) {
        int cantidad;
        cout << "Cantidad de alternativas: ";
        cin >> cantidad;
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
        cin >> correcta;
        items.push_back(new PreguntaAlternativa(next_id++, nivel, enunciado, alternativas, correcta - 1));
    } else {
        cout << "Tipo no válido." << endl;
    }
}

void Sistema_Evaluacion::mostrar_items() {
    for (Item* item : items) {
        item->mostrar();
    }
}

void Sistema_Evaluacion::actualizar_item() {
    int id;
    cout << "Ingrese ID del ítem a actualizar: ";
    cin >> id;
    for (Item* item : items) {
        if (item->get_id() == id) {
            cin.ignore();
            string nuevo_enunciado;
            cout << "Ingrese nuevo enunciado: ";
            getline(cin, nuevo_enunciado);
            item->set_enunciado(nuevo_enunciado);
            cout << "Actualizado." << endl;
            return;
        }
    }
    cout << "Ítem no encontrado." << endl;
}

void Sistema_Evaluacion::borrar_item() {
    int id;
    cout << "Ingrese ID del ítem a eliminar: ";
    cin >> id;
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

void Sistema_Evaluacion::consultar_item() {
    int id;
    cout << "Ingrese ID del ítem a consultar: ";
    cin >> id;
    for (Item* item : items) {
        if (item->get_id() == id) {
            item->mostrar();
            return;
        }
    }
    cout << "Ítem no encontrado." << endl;
}

void Sistema_Evaluacion::buscar_items_por_taxonomia() {
    int nivel;
    cout << "Ingrese nivel taxonómico a buscar: ";
    cin >> nivel;
    for (Item* item : items) {
        if (item->get_nivel_taxonomico() == nivel) {
            item->mostrar();
        }
    }
}

void Sistema_Evaluacion::generar_evaluacion() {
    int cantidad;
    cout << "Cantidad de preguntas para evaluación: ";
    cin >> cantidad;
    if (cantidad > items.size()) {
        cout << "No hay suficientes ítems." << endl;
        return;
    }
    for (int i = 0; i < cantidad; ++i) {
        items[i]->mostrar();
    }
}

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
        cin >> opcion;

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

    } while (opcion != 0);
}
