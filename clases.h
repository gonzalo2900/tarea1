#ifndef CLASES_H
#define CLASES_H

#include <string>
#include <vector>
using namespace std;

class Item {
protected:
    int id;
    int nivelTaxonomico;
    int tipo;
    string texto;

public:
    Item(int id, int nivelTaxonomico, int tipo, string texto);
    virtual ~Item();

    int getId();
    int getNivelTaxonomico();
    int getTipo();
    string getTexto();
    void setTexto(string nuevoTexto);

    virtual void mostrar() = 0;
};

class PreguntaVF : public Item {
private:
    bool respuestaCorrecta;
    string justificacion;

public:
    PreguntaVF(int id, int nivelTaxonomico, string texto, bool respuesta, string justificacion);
    void mostrar();
};

class PreguntaAlternativa : public Item {
private:
    vector<string> alternativas;
    int correcta;

public:
    PreguntaAlternativa(int id, int nivelTaxonomico, string texto, vector<string> alternativas, int correcta);
    void mostrar();
};

class SistemaEvaluacion {
private:
    vector<Item*> items;
    int nextId;

public:
    SistemaEvaluacion();
    ~SistemaEvaluacion();

    void crearItem();
    void mostrarItems();
    void actualizarItem();
    void borrarItem();
    void consultarItem();
    void buscarItemsPorTaxonomia();
    void generarEvaluacion();
    void menu();
};

#endif
