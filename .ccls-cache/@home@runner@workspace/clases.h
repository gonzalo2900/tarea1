#ifndef CLASES_H
#define CLASES_H

#include <string>
#include <vector>
using namespace std;

//
// CLASE ABSTRACTA BASE: Item
// Representa una pregunta genérica, usada como base para preguntas Verdadero/Falso y de Alternativas.
//
class Item {
private:
    int id;                     // Identificador único del ítem
    int nivel_taxonomico;      // Nivel según la taxonomía de Bloom (1 a 5)
    int categoria;             // Tipo de ítem: 1 = VF, 2 = Alternativa
    string enunciado;          // Pregunta a presentar

public:
    // Constructor
    Item(int id, int nivel_taxonomico, int categoria, string enunciado);

    // Destructor virtual (para manejo correcto con herencia)
    virtual ~Item();

    // Métodos de acceso
    int get_id();
    int get_nivel_taxonomico();
    int get_categoria();
    string get_enunciado();

    // Modificador del enunciado
    void set_enunciado(string nuevo_enunciado);

    // Método virtual puro que será implementado por clases hijas
    virtual void mostrar() = 0;
};

//
// CLASE DERIVADA: PreguntaVerdaderoFalso
// Representa preguntas tipo Verdadero o Falso.
//
class PreguntaVerdaderoFalso : public Item {
private:
    bool respuesta_correcta;   // true si la respuesta es "Verdadero"
    string justificacion;      // Justificación si es "Falso"

public:
    PreguntaVerdaderoFalso(int id, int nivel_taxonomico, string enunciado, bool respuesta, string justificacion);
    void mostrar();  // Implementación de mostrar específica para VF
};

//
// CLASE DERIVADA: PreguntaAlternativa
// Representa preguntas con múltiples alternativas.
//
class PreguntaAlternativa : public Item {
private:
    vector<string> alternativas;  // Lista de alternativas
    int correcta;                 // Índice de la alternativa correcta

public:
    PreguntaAlternativa(int id, int nivel_taxonomico, string enunciado, vector<string> alternativas, int correcta);
    void mostrar();  // Implementación de mostrar específica para Alternativas
};

//
// CLASE CONTROLADORA: Sistema_Evaluacion
// Administra la creación, edición, eliminación y consulta de ítems.
//
class Sistema_Evaluacion {
private:
    vector<Item*> items;  // Lista de preguntas (polimórficas)
    int next_id;          // Controla el ID incremental

public:
    Sistema_Evaluacion();   // Constructor
    ~Sistema_Evaluacion();  // Destructor

    // Funciones CRUD y funcionalidades adicionales
    void crear_item();
    void mostrar_items();
    void actualizar_item();
    void borrar_item();
    void consultar_item();
    void buscar_items_por_taxonomia();
    void generar_evaluacion();
    void menu();  // Menú principal de interacción con el usuario
};

#endif

