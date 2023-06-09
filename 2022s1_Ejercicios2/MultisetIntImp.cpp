#include "MultisetInt.h"

#ifdef MULTISET_INT_IMP
struct ListaMultiSetLista {
	int clave;
	int ocurrencias;
	ListaMultiSetLista* sig;
};

struct _cabezalMultisetInt {
	int cantE;
	ListaMultiSetLista* lista;
};


MultisetInt crearMultisetInt() {
	return NULL;
}
//pre:-
//post: agrega el elemento a la lista.

void agregarLista(ListaMultiSetLista*& l, int e, int ocu) {
	if (l != NULL) {
		if (l->clave == e) {
			l->ocurrencias += ocu;
		}
		else {
			agregarLista(l->sig, e, ocu);
		}
	}
	else {
		l = new ListaMultiSetLista;
		l->clave = e;
		l->ocurrencias = ocu;
		l->sig = NULL;
	}
}


void agregar(MultisetInt& s, int e, unsigned int ocurrencias) {
	
}

//pre: pertence(s,e);
//post:borra el elemento de la lista
void borrarLista(ListaMultiSetLista*& l, int e) {
	if (l != NULL) {
		if (l->clave == e) {
			if (l->ocurrencias > 1) {
				l->ocurrencias -= 1;
			}
			else {
				ListaMultiSetLista* borro = l;
				l = l->sig;
				delete borro;

			}
		}
		else {
			borrarLista(l->sig, e);
		}
	}
}

void borrar(MultisetInt& s, int e) {
	
}

bool buscoClave(ListaMultiSetLista* l, int e) {
	bool ret = false;
	if (l != NULL) {
		if (l->clave == e) {
			ret = true;
		}
		else {
			ret = buscoClave(l->sig, e);
		}
	}
	return ret;
}

bool pertenece(MultisetInt s, int e) {
	return false;
}



MultisetInt unionConjuntos(MultisetInt s1, MultisetInt s2) {
	return NULL;

}
MultisetInt interseccionConjuntos(MultisetInt s1, MultisetInt s2) {
	return NULL;
}


MultisetInt diferenciaConjuntos(MultisetInt s1, MultisetInt s2) {
	return NULL;
}


bool contenidoEn(MultisetInt s1, MultisetInt s2) {
	bool ret = false;
	return false;
}

int elemento(MultisetInt s) {
	return 0;
}

bool esVacio(MultisetInt s) {
	return true;
}

unsigned int cantidadElementos(MultisetInt s) {
	return 0;

}

void destruirLista(ListaMultiSetLista*& l) {
	
}

void destruir(MultisetInt& s) {
	
}


MultisetInt clon(MultisetInt s) {
	return NULL;
}

#endif