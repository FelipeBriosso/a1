#include "Ejercicios.h"
//pre:-
//post: llena la lista con el arbol
void EnlistarAux(ListaOrdInt ret, NodoABInt* a) {
	if (a != NULL) {
		agregar(ret, a->dato);
		EnlistarAux(ret, a->izq);
		EnlistarAux(ret, a->der);
	}
}


ListaOrdInt Enlistar(NodoABInt* a)
{
	return NULL;
}

ListaOrdInt UnionListaOrd(ListaOrdInt l1, ListaOrdInt l2)
{
	return NULL;
}

bool EstaContenida(PilaInt p1, PilaInt p2)
{
	return false;
}


ListaOrdInt ObtenerRepetidos(MultisetInt m)
{
	return NULL;
}

MultisetInt Xor(MultisetInt m1, MultisetInt m2)
{
	return NULL;
}

ColaPrioridadInt MenorPrioridad(ColaPrioridadInt c) {
	
	return NULL;;
}

