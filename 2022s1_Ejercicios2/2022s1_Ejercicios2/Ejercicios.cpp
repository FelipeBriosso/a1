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
	ListaOrdInt ret = crearListaOrdInt();
	EnlistarAux(ret, a);
	return ret;
}

ListaOrdInt UnionListaOrd(ListaOrdInt l1, ListaOrdInt l2)
{
	ListaOrdInt ret = clon(l1);
	ListaOrdInt aux = clon(l2);
	while (!esVacia(aux)) {
		int n = minimo(aux);
		borrarMinimo(aux);
		agregar(ret, n);
	}
	destruir(aux);
	return ret;
}

bool EstaContenida(PilaInt p1, PilaInt p2)
{
	bool ret = true;
	PilaInt copia1 = clon(p1);
	PilaInt copia2 = clon(p2);
	while (!esVacia(copia1) && ret) {
		int dato = top(copia1);
		pop(copia1);
		PilaInt aux = crearPilaInt();
		bool esta = false;
		while (!esVacia(copia2) && !esta) {
			int n = top(copia2);
			pop(copia2);
			if (dato == n) {
				esta = true;
			}
			else {
				push(aux, n);
			}
		}
		if(esta) {
			while (!esVacia(aux)) {
				int n = top(aux);
				push(copia2, n);
				pop(aux);
			}
		}
		else {
			ret = false;
		}
		destruir(aux);
	}
	destruir(copia1);
	destruir(copia2);
	return ret;
}


ListaOrdInt ObtenerRepetidos(MultisetInt m) 
{
	ListaOrdInt ret = crearListaOrdInt();
	MultisetInt copia = clon(m);
	while (!esVacio(copia)) {
		int n = elemento(copia);
		borrar(copia, n);
		bool esta = false;
		while (pertenece(copia, n)) {
			esta = true;
			borrar(copia, n);
		}
		if (esta) {
			agregar(ret, n);
		}
	}
	destruir(copia);
	return ret;
}

MultisetInt Xor(MultisetInt m1, MultisetInt m2)
{
	MultisetInt copiam1 = diferenciaConjuntos(m1,m2);
	MultisetInt copiam2 = diferenciaConjuntos(m2,m1);
	MultisetInt ret = unionConjuntos(copiam1,copiam2);
	destruir(copiam1);
	destruir(copiam2);
	return ret;
}

ColaPrioridadInt MenorPrioridad(ColaPrioridadInt c) {
	ColaPrioridadInt copia = clon(c);
	ColaPrioridadInt aux = crearColaPrioridadInt(cantidadElementos(c));
	while (!esVacia(copia)) {
		int dato = principio(copia);
		int m = principioPrioridad(copia);
		desencolar(copia);
		encolar(aux,dato,m);
		bool fin = true;
		while(!esVacia(copia) && principioPrioridad(copia) == m) {
			dato = principio(copia);
			desencolar(copia);
			encolar(aux, dato, m);
		}
		if (!esVacia(copia)) {
			if (principioPrioridad(copia) != m) {
				fin = false;
			}
		}
		if (!fin) {
			while (!esVacia(aux)) {
				desencolar(aux);
			}
		}
	}
	ColaPrioridadInt ret = crearColaPrioridadInt(cantidadElementos(aux));
	while (!esVacia(aux)) {
		int dato = principio(aux);
		int m = principioPrioridad(aux);
		desencolar(aux);
		encolar(ret, dato, m);
	}
	destruir(aux);
	destruir(copia);
	return ret;
}

