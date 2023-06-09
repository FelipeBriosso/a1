#include "ListaOrdInt.h"

#ifdef LISTA_ORD_INT_IMP_2
struct NodoABB {
	int dato;
	int ocurrencias;
	NodoABB* izq;
	NodoABB* der;
};

struct _cabezalListaOrdInt {
	int cantE;
	NodoABB* lista;
};

ListaOrdInt crearListaOrdInt() {
	ListaOrdInt ret = new _cabezalListaOrdInt;
	ret->cantE = 0;
	ret->lista = new NodoABB;
	ret->lista->dato = 0;
	ret->lista->ocurrencias = 0;
	ret->lista->izq = NULL;
	ret->lista->der = NULL;
	return ret;
}
void agregarListaOrdIntAux(NodoABB*& l, int e) {
	if (l != NULL) {
		if (l->dato == e) {
			l->ocurrencias += 1;
		}
		else {
			if (l->dato < e) {
				agregarListaOrdIntAux(l->der, e);
			}
			else {
				agregarListaOrdIntAux(l->izq, e);
			}
		}
	}
	else {
		l = new NodoABB;
		l->dato = e;
		l->ocurrencias = 1;
		l->der = NULL;
		l->izq = NULL;
	}

}

void agregar(ListaOrdInt& l, int e) {
	if (l != NULL) {
		if (l->lista->ocurrencias == 0) {
			l->lista->dato = e;
			l->lista->ocurrencias = 1;
			l->lista->izq = NULL;
			l->lista->der = NULL;
		}
		else {
			agregarListaOrdIntAux(l->lista, e);
		}
		l->cantE += 1;
	}
}
void borrarMinAux(NodoABB*& l) {
	if (l != NULL) {
		if (l->izq != NULL) {
			borrarMinAux(l->izq);
		}
		else {
			if (l->ocurrencias > 1) {
				l->ocurrencias -= 1;
			}
			else {
				if (l->der != NULL) {
					NodoABB* borro = l;
					l = l->der;
					delete borro;
				}
				else {
					delete l;
					l = NULL;
				}
			}
		}
	}
}

void borrarMinimo(ListaOrdInt& l) {
	if (!esVacia(l)) {
		borrarMinAux(l->lista);
		l->cantE -= 1;
	}
}
void borrarMaxAux(NodoABB*& l) {
	if (l != NULL) {
		if (l->der != NULL) {
			borrarMaxAux(l->der);
		}
		else {
			if (l->ocurrencias > 1) {
				l->ocurrencias -= 1;
			}
			else {
				if (l->izq != NULL) {
					NodoABB* borro = l;
					l = l->izq;
					delete borro;
				}
				else {
					delete l;
					l = NULL;
				}
			}
		}
	}
}

void borrarMaximo(ListaOrdInt& l) {
	if (!esVacia(l)) {
		borrarMaxAux(l->lista);
		l->cantE -= 1;
	}
}
void colocoIzq(NodoABB*& l, NodoABB* izq) {
	if (l != NULL) {
		colocoIzq(l->izq, izq);
	}
	else {
		l = izq;
	}
}
void borrarAux(NodoABB*& l, int e) {
	if (l != NULL) {
		if (l->dato == e) {
			if (l->ocurrencias > 1) {
				l->ocurrencias -= 1;
			}
			else {
				NodoABB* izq = l->izq;
				NodoABB* borro = l;
				l = l->der;
				colocoIzq(l, izq);
				delete borro;
			}
		}
		else {
			if (l->dato > e) {
				borrarAux(l->izq, e);
			}
			else {
				borrarAux(l->der, e);
			}
		}
	}
}

void borrar(ListaOrdInt& l, int e) {
	if (existe(l, e)) {
		borrarAux(l->lista, e);
		l->cantE -= 1;
	}
}
int buscoMin(NodoABB* l) {
	int ret = 0;
	if (l != NULL && l->izq != NULL) {
		ret = buscoMin(l->izq);
	}
	else {
		ret = l->dato;
	}
	return ret;
}

int minimo(ListaOrdInt l) {
	if (l != NULL) {
		return buscoMin(l->lista);
	}

}
int buscoMax(NodoABB* l) {
	int ret = 0;
	if (l != NULL && l->der != NULL) {
		ret = buscoMax(l->der);
	}
	else {
		ret = l->dato;
	}
	return ret;
}

int maximo(ListaOrdInt l) {
	if (l != NULL) {
		return buscoMax(l->lista);
	}
}

bool buscoExiste(NodoABB* l, int e) {
	bool ret = false;
	if (l != NULL) {
		if (l->dato == e) {
			ret = true;
		}
		else {
			if (l->dato > e) {
				ret = buscoExiste(l->izq, e);
			}
			else {
				ret = buscoExiste(l->der, e);
			}
		}
	}
	return ret;
}

bool existe(ListaOrdInt l, int e) {
	if (l != NULL) {
		return buscoExiste(l->lista, e);
	}
}

bool esVacia(ListaOrdInt l) {
	if (l != NULL) {
		return l->cantE == 0;
	}
}

unsigned int cantidadElementos(ListaOrdInt l) {
	if (l != NULL) {
		return l->cantE;
	}
}
NodoABB* clonAuxABB(NodoABB* l) {
	NodoABB* ret = NULL;
	if (l != NULL) {
		ret = new NodoABB;
		ret->dato = l->dato;
		ret->ocurrencias = l->ocurrencias;
		ret->izq = clonAuxABB(l->izq);
		ret->der = clonAuxABB(l->der);
	}
	return ret;
}

ListaOrdInt clon(ListaOrdInt l) {
	ListaOrdInt ret = crearListaOrdInt();
	ret->cantE = l->cantE;
	ret->lista = clonAuxABB(l->lista);
	return ret;
}
void destruirNodoABB(NodoABB* l) {
	if (l != NULL) {
		destruirNodoABB(l->izq);
		destruirNodoABB(l->der);
		delete l;
	}
}

void destruir(ListaOrdInt& l) {
	destruirNodoABB(l->lista);
	delete l;
}



#endif