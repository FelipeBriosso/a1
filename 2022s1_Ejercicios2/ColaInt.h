#pragma once
// NOTA: Este archivo no debe ser modificado (excepto por los define que eligen la implementacion a usar)

// Elegir la implementacion a usar (solo 1 a la vez):
#define COLA_INT_IMP
//#define COLA_INT_IMP_2

#if defined(COLA_INT_IMP)
	#include "ColaIntImp.h"
#elif defined(COLA_INT_IMP_2)
	#include "ColaIntImp2.h"
#endif

// PRE: -
// POS: retorna una nueva cola vacia
ColaInt crearColaInt();

// PRE: -
// POS: inserta un elemento al fondo de la cola
void encolar(ColaInt& c, int e);

// PRE: !esVacia()
// POS: retorna el elemento del principio de la cola
int principio(ColaInt c);

// PRE: !esVacia()
// POS: elimina el elemento del principio de la cola
void desencolar(ColaInt& c);

// PRE: -
// POS: retorna true si y solo si la cola esta vacia
bool esVacia(ColaInt c);

// PRE: -
// POS: retorna la cantidad de elementos presentes en la cola
unsigned int cantidadElementos(ColaInt c);

// PRE: -
// POS: retorna una copia de la cola c sin compartir memoria
ColaInt clon(ColaInt c);

// PRE: -
// POS: libera la memoria de la cola
void destruir(ColaInt& c);


