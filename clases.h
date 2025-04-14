#ifndef CLASES_H
#define CLASES_H

#include <string>
#include <vector>
using namespace std;

//
// CLASE ABSTRACTA BASE: Item
// Esta clase representa una pregunta genérica. Sirve como clase base para preguntas de tipo verdadero/falso y de alternativas.
// Contiene información común a todos los ítems como ID, nivel taxonómico, tipo de pregunta, enunciado y tiempo estimado.
//
class Item {
private:
    int id;                     // Identificador único del ítem
    int nivel_taxonomico;      // Nivel según la taxonomía de Bloom (1 a 5)
    int categoria;             // Tipo de pregunta: 1 = VF, 2 = Alternativa
    string enunciado;          // Texto de la pregunta
    int tiempo_estimado;       // Tiempo estimado para resolver la pregunta (en minutos)

public:
    Item(int id, int nivel_taxonomico, int categoria, string enunciado, int tiempo_estimado);
    virtual ~Item(); // Destructor virtual para asegurar destrucción correcta en herencia

    // Métodos getter para obtener información del ítem
    int get_id();
    int get_nivel_taxonomico();
    int get_categoria();
    string get_enunciado();
    int get_tiempo_estimado();

    // Métodos setter para modificar atributos editables
    void set_enunciado(string nuevo_enunciado);
    void set_tiempo_estimado(int nuevo_tiempo);

    // Método virtual puro que debe ser implementado por las clases derivadas
    virtual void mostrar() = 0;
};

//
// CLASE DERIVADA: PreguntaVerdaderoFalso
// Representa una pregunta de tipo verdadero o falso.
// Si la respuesta correcta es falsa, se solicita una justificación.
//
class PreguntaVerdaderoFalso : public Item {
private:
    bool respuesta_correcta;   // true si la respuesta es "Verdadero", false si es "Falso"
    string justificacion;      // Justificación si la respuesta es Falso

public:
    PreguntaVerdaderoFalso(int id, int nivel_taxonomico, string enunciado, bool respuesta, string justificacion, int tiempo_estimado);
    void mostrar(); // Implementación específica para mostrar preguntas tipo VF
};

//
// CLASE DERIVADA: PreguntaAlternativa
// Representa una pregunta de selección múltiple con varias alternativas y una correcta.
//
class PreguntaAlternativa : public Item {
private:
    vector<string> alternativas;  // Lista de alternativas posibles
    int correcta;                 // Índice de la alternativa correcta (base 0)

public:
    PreguntaAlternativa(int id, int nivel_taxonomico, string enunciado, vector<string> alternativas, int correcta, int tiempo_estimado);
    void mostrar(); // Implementación específica para mostrar preguntas tipo Alternativa
};

//
// CLASE CONTROLADORA: Sistema_Evaluacion
// Esta clase gestiona toda la lógica del sistema: CRUD de ítems, búsqueda, generación de evaluación, menú, etc.
//
class Sistema_Evaluacion {
private:
    vector<Item*> items;  // Contenedor de punteros a ítems (polimórfico)
    int next_id;          // Controla el ID incremental para los ítems

public:
    Sistema_Evaluacion();   // Constructor del sistema
    ~Sistema_Evaluacion();  // Destructor que libera memoria dinámica

    // Métodos que representan las funcionalidades principales del sistema
    void crear_item();                    // Crea un nuevo ítem
    void mostrar_items();                // Muestra todos los ítems registrados
    void actualizar_item();              // Modifica enunciado y tiempo de un ítem existente
    void borrar_item();                  // Elimina un ítem por ID
    void consultar_item();               // Muestra un ítem específico por ID
    void buscar_items_por_taxonomia();   // Muestra todos los ítems de un nivel taxonómico específico
    void generar_evaluacion();           // Genera una evaluación con preguntas seleccionadas y tiempo total estimado
    void menu();                         // Menú principal que permite acceder a todas las funciones
};

#endif
