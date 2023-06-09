#include "PilaInt.h"

#ifdef PILA_INT_IMP

struct _cabezalPilaInt {
	NodoListaInt* cima;
	int cantE;
};


PilaInt crearPilaInt(){
	PilaInt ret = new _cabezalPilaInt;
	ret->cima = NULL;
	ret->cantE = 0;
	return ret;
}

void push(PilaInt& p, int e) {
	if (p != NULL) {
		NodoListaInt* nuevo = new NodoListaInt;
		nuevo->dato = e;
		nuevo->sig = p->cima;
		p->cima = nuevo;
		p->cantE += 1;
	}
}

int top(PilaInt p) {
	int ret = 0;
	if (!esVacia(p)) {
		ret = p->cima->dato;
	}
	return ret;
}

void pop(PilaInt& p) {
	if (!esVacia(p)) {
		NodoListaInt* borrar = p->cima;
		p->cima = p->cima->sig;
		p->cantE -= 1;
		delete borrar;
	}
}

unsigned int cantidadElementos(PilaInt p) {
	int ret = 0;
	if (p != NULL) {
		ret = p->cantE;
	}
		
	return ret;
}

bool esVacia(PilaInt p) {
	bool ret = true;
	if (p != NULL) {
		ret = p->cantE == 0;
	}
	return ret;
}

//pre:-
//post: llena la lista con los elementos sin compartir memoria.
NodoListaInt* clonPilaAux(NodoListaInt* l) {
	NodoListaInt* ret = NULL;
	if (l != NULL) {
		ret = new NodoListaInt;
		ret->dato = l->dato;
		ret->sig = clonPilaAux(l->sig);
	}
	return ret;
}

PilaInt clon(PilaInt p) {
	PilaInt ret = crearPilaInt();
	ret->cantE = p->cantE;
	ret->cima = clonPilaAux(p->cima);
	return ret;
}

//pre:-
//post: destruye la lista.
void destruirPilaAux(NodoListaInt*& l) {
	while (l != NULL) {
		NodoListaInt* borro = l;
		l = l->sig;
		delete borro;
	}
}

void destruir(PilaInt& p) {
	destruirPilaAux(p->cima);
	delete p;
}


#endif