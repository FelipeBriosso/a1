#include "ColaPrioridadInt.h"

#ifdef COLAPRIORIDAD_INT_IMP
struct NodoListaPrioridad {
	int dato;
	int prioridad;
	NodoListaPrioridad* sig;
};

struct _cabezalColaPrioridadInt {
	int cantE;
	int cota;
	NodoListaPrioridad* lista;
};


ColaPrioridadInt crearColaPrioridadInt(unsigned int cota) {
	ColaPrioridadInt ret = new _cabezalColaPrioridadInt;
	ret->cota = cota;
	ret->cantE = 0;
	ret->lista = NULL;
	return ret;
}
//pre:-
//post: guarda el elemento en la lista.
void encolarAux(NodoListaPrioridad*& l, int e, int p) {
	if (l != NULL) {
		if (l->prioridad >= p) {
			encolarAux(l->sig, e, p);
		}
		else {
			NodoListaPrioridad* aux = new NodoListaPrioridad;
			aux->dato = e;
			aux->prioridad = p;
			aux->sig = l;
			l = aux;
		}
	}
	else {
		l = new NodoListaPrioridad;
		l->dato = e;
		l->prioridad = p;
		l->sig = NULL;
	}
}

void encolar(ColaPrioridadInt& c, int e, int p) {
	if (!esLlena(c)) {
		encolarAux(c->lista,e,p);
		c->cantE += 1;
	}
}

int principio(ColaPrioridadInt c) {
	if (!esVacia(c)) {
		return c->lista->dato;
	}
}

int principioPrioridad(ColaPrioridadInt c) {
	if (!esVacia(c)) {
		return c->lista->prioridad;
	}
}

void desencolar(ColaPrioridadInt& c) {
	if (!esVacia(c)) {
		c->lista = c->lista->sig;
		c->cantE -= 1;
	}
}

bool esVacia(ColaPrioridadInt c) {
	if (c != NULL) {
		return c->cantE == 0;
	}
}

bool esLlena(ColaPrioridadInt c) {
	if (c != NULL) {
		return c->cantE == c->cota;
	}
}

unsigned int cantidadElementos(ColaPrioridadInt c) {
	if (c != NULL) {
		return c->cantE;
	}
}
//pre:-
//post: copia la lista sin compartir memoria.
NodoListaPrioridad* copiarListaColaPrioridad(NodoListaPrioridad* l) {
	NodoListaPrioridad* ret = NULL;
	if (l != NULL) {
		ret = new NodoListaPrioridad;
		ret->dato = l->dato;
		ret->prioridad = l->prioridad;
		ret->sig = copiarListaColaPrioridad(l->sig);
	}
	return ret;
}

ColaPrioridadInt clon(ColaPrioridadInt c) {
	ColaPrioridadInt ret = crearColaPrioridadInt(c->cota);
	ret->cantE = c->cantE;
	if (c->cota > 0) {
		ret->lista = copiarListaColaPrioridad(c->lista);
	}
	return ret;
}
void destruirNodoListaPrioridad(NodoListaPrioridad* l) {
	if (l != NULL) {
		destruirNodoListaPrioridad(l->sig);
		delete l;
	}

}

void destruir(ColaPrioridadInt& c) {
	if (!esVacia(c)) {
		destruirNodoListaPrioridad(c->lista);
	}
	delete c;
}


#endif