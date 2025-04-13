#include "clases.h"
#include <iostream>
using namespace std;

// --- Métodos Item ---
Item::Item(int id, int nivelTaxonomico, int tipo, string texto) {
    this->id = id;
    this->nivelTaxonomico = nivelTaxonomico;
    this->tipo = tipo;
    this->texto = texto;
}

Item::~Item() {}

int Item::getId() { return id; }
int Item::getNivelTaxonomico() { return nivelTaxonomico; }
int Item::getTipo() { return tipo; }
string Item::getTexto() { return texto; }
void Item::setTexto(string nuevoTexto) { texto = nuevoTexto; }

// --- PreguntaVF ---
PreguntaVF::PreguntaVF(int id, int nivelTaxonomico, string texto, bool respuesta, string justificacion)
: Item(id, nivelTaxonomico, 1, texto) {
    this->respuestaCorrecta = respuesta;
    this->justificacion = justificacion;
}

void PreguntaVF::mostrar() {
    cout << "ID: " << getItemId() << " [VF] " << getItemTexto() << endl;
    cout << "Respuesta: " << (respuestaCorrecta ? "Verdadero" : "Falso") << endl;
    if (!respuestaCorrecta) {
        cout << "Justificación: " << justificacion << endl;
    }
}

// --- PreguntaAlternativa ---
PreguntaAlternativa::PreguntaAlternativa(int id, int nivelTaxonomico, string texto, vector<string> alternativas, int correcta)
: Item(id, nivelTaxonomico, 2, texto) {
    this->alternativas = alternativas;
    this->correcta = correcta;
}

void PreguntaAlternativa::mostrar() {
    cout << "ID: " << getItemId() << " [Alternativa] " << getItemTexto() << endl;
    for (size_t i = 0; i < alternativas.size(); ++i) {
        cout << i + 1 << ". " << alternativas[i];
        if (i == correcta) cout << " (Correcta)";
        cout << endl;
    }
}

// --- SistemaEvaluacion ---
SistemaEvaluacion::SistemaEvaluacion() {
    nextId = 1;
}

SistemaEvaluacion::~SistemaEvaluacion() {
    for (Item* item : items) {
        delete item;
    }
}

void SistemaEvaluacion::crearItem() {
    int tipo;
    cout << "\nTipo de pregunta (1: VF, 2: Alternativa): ";
    cin >> tipo;

    int nivel;
    string texto;
    cout << "Nivel taxonómico (1-5): ";
    cin >> nivel;
    cin.ignore();
    cout << "Ingrese el texto de la pregunta: ";
    getline(cin, texto);

    if (tipo == 1) {
        bool respuesta;
        string justificacion;
        cout << "Respuesta correcta (1: Verdadero, 0: Falso): ";
        cin >> respuesta;
        cin.ignore();
        if (!respuesta) {
            cout << "Ingrese justificación: ";
            getline(cin, justificacion);
        }
        items.push_back(new PreguntaVF(nextId++, nivel, texto, respuesta, justificacion));
    } else if (tipo == 2) {
        int n;
        vector<string> alternativas;
        cout << "Cantidad de alternativas: ";
        cin >> n;
        cin.ignore();
        for (int i = 0; i < n; ++i) {
            string alt;
            cout << "Alternativa " << i + 1 << ": ";
            getline(cin, alt);
            alternativas.push_back(alt);
        }
        int correcta;
        cout << "Índice de la correcta (1-" << n << "): ";
        cin >> correcta;
        items.push_back(new PreguntaAlternativa(nextId++, nivel, texto, alternativas, correcta - 1));
    }
}





void SistemaEvaluacion::mostrarItems() {
    for (Item* item : items) {
        item->mostrar();
        cout << "------------------" << endl;
    }
}






void SistemaEvaluacion::actualizarItem() {
    int id;
    cout << "Ingrese ID del ítem a actualizar: ";
    cin >> id;
    cin.ignore();

    for (Item* item : items) {
        if (item->getId() == id) {
            string nuevoTexto;
            cout << "Ingrese el nuevo texto de la pregunta: ";
            getline(cin, nuevoTexto);
            item->setTexto(nuevoTexto);
            cout << "Texto actualizado correctamente.\n";
            return;
        }
    }
    cout << "Ítem no encontrado.\n";
}

void SistemaEvaluacion::borrarItem() {
    int id;
    cout << "Ingrese ID del ítem a borrar: ";
    cin >> id;

    for (auto it = items.begin(); it != items.end(); ++it) {
        if ((*it)->getId() == id) {
            delete *it;
            items.erase(it);
            cout << "Ítem borrado correctamente.\n";
            return;
        }
    }
    cout << "Ítem no encontrado.\n";
}

void SistemaEvaluacion::consultarItem() {
    int id;
    cout << "Ingrese ID del ítem a consultar: ";
    cin >> id;

    for (Item* item : items) {
        if (item->getId() == id) {
            item->mostrar();
            return;
        }
    }
    cout << "Ítem no encontrado.\n";
}

void SistemaEvaluacion::buscarItemsPorTaxonomia() {
    int nivel;
    cout << "Ingrese el nivel taxonómico (1-5): ";
    cin >> nivel;

    for (Item* item : items) {
        if (item->getNivelTaxonomico() == nivel) {
            item->mostrar();
            cout << "------------------" << endl;
        }
    }
}

void SistemaEvaluacion::generarEvaluacion() {
    int cantidad;
    cout << "¿Cuántas preguntas desea incluir en la evaluación?: ";
    cin >> cantidad;

    if (cantidad > items.size()) {
        cout << "No hay suficientes preguntas disponibles.\n";
        return;
    }

    cout << "\n--- Evaluación Generada ---\n";
    for (int i = 0; i < cantidad; ++i) {
        items[i]->mostrar();
        cout << "------------------" << endl;
    }
}

void SistemaEvaluacion::menu() {
    int opcion;
    do {
        cout << "\n===== MENÚ =====\n";
        cout << "1. Crear ítem\n";
        cout << "2. Mostrar ítems\n";
        cout << "3. Actualizar ítem\n";
        cout << "4. Borrar ítem\n";
        cout << "5. Consultar ítem\n";
        cout << "6. Buscar por nivel taxonómico\n";
        cout << "7. Generar evaluación\n";
        cout << "0. Salir\n\n";
        cout << "Seleccione una opción: ";
        cin >> opcion;

        switch (opcion) {
            case 1: crearItem(); break;
            case 2: mostrarItems(); break;
            case 3: actualizarItem(); break;
            case 4: borrarItem(); break;
            case 5: consultarItem(); break;
            case 6: buscarItemsPorTaxonomia(); break;
            case 7: generarEvaluacion(); break;
            case 0: cout << "Saliendo...\n"; break;
            default: cout << "Opción inválida.\n";
        }
    } while (opcion != 0);
}
