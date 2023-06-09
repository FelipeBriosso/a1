#include "ColaInt.h"

#ifdef COLA_INT_IMP

struct _cabezalColaInt {
	int cantE;
	NodoListaInt* primero;
	NodoListaInt* ultimo;
};

ColaInt crearColaInt() {
	ColaInt ret = new _cabezalColaInt;
	ret->primero = NULL;
	ret->ultimo = NULL;
	ret->cantE = 0;
	return ret;
}

void encolar(ColaInt& c, int e) {
	if (c->ultimo == NULL) {
		if (c->primero == NULL) {
			c->ultimo = new NodoListaInt;
			c->ultimo->dato = e;
			c->ultimo->sig = NULL;
			c->primero = c->ultimo;
		}
	}
	else {
		c->ultimo->sig = new NodoListaInt;
		c->ultimo->sig->dato = e;
		c->ultimo->sig->sig = NULL;
		c->ultimo = c->ultimo->sig;
	}
	c->cantE += 1;
}

int principio(ColaInt c) {
	int ret = 0;
	if (!esVacia(c)) {
		ret = c->primero->dato;
	}
	return ret;
}

void desencolar(ColaInt& c) {
	if (!esVacia(c)) {
		NodoListaInt* borrar = c->primero;
		c->primero = c->primero->sig;
		delete borrar;
		if (c->primero == NULL) {
			c->ultimo = NULL;
		}
		c->cantE -= 1;
	}
}

bool esVacia(ColaInt c) {
	bool ret = true;
	if (c != NULL) {
		ret = c->primero == NULL;
	}
	return ret;
}

unsigned int cantidadElementos(ColaInt c) {
	if (c != NULL) {
		return c->cantE;
	}
}


ColaInt clon(ColaInt c) {
	ColaInt ret = crearColaInt();
	int largo = c->cantE;
	while (largo > 0) {
		int n = principio(c);
		desencolar(c);
		encolar(ret, n);
		encolar(c, n);
		largo -= 1;
	}
	return ret;
}

void destruir(ColaInt& c) {
	while (!esVacia(c)) {
		desencolar(c);
	}
	delete c;
}

#endif