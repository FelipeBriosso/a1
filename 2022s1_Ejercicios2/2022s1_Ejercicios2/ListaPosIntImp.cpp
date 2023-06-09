#include "ListaPosInt.h"

#ifdef LISTA_POS_INT_IMP

struct _cabezalListaPosInt {
	int cota;
	int* lista;
	int cant;
};

ListaPosInt crearListaPosInt(){
	ListaPosInt ret = new _cabezalListaPosInt;
	ret->cota = 10;
	ret->lista = new int[10];
	ret->cant = 0;
	return ret;
}

void agregar(ListaPosInt& l, int e, unsigned int pos){
	if (esVacia(l)) {
		l->lista[0] = e;
	}
	else {
		if (l->cant == l->cota) {
			int nuevaCota = 2 * l->cota;
			int* nuevaLista = new int[nuevaCota];
			for (int i = 0; i < l->cota; i += 1) {
				nuevaLista[i] = l->lista[i];
			}
			delete[] l->lista;
			l->lista = nuevaLista;
			l->cota = nuevaCota;
			for (int i = l->cota; i > pos; i -= 1) {
				l->lista[i] = l->lista[i - 1];
			}
			l->lista[pos] = e;
		}
		else {
			if (pos >=0 && pos < l->cota) {
				for (int i = l->cota; i > pos; i -= 1) {
					l->lista[i] = l->lista[i-1];
				}
				l->lista[pos] = e;
			}
			else {
				l->lista[l->cant] = e;
			}
		}

	}
	l->cant += 1;
}

void borrar(ListaPosInt& l, unsigned int pos){
	if (l->cant > 0) {
		if (pos < l->cota) {
			for (int i = pos; i < l->cota - 1; i += 1) {
				l->lista[i] = l->lista[i + 1];
			}
			l->cant -= 1;
		}
	}
}

int elemento(ListaPosInt l, unsigned int pos){
	if (pos >= 0 && pos < l->cota) {
		return l->lista[pos];
	}
}

bool esVacia(ListaPosInt l)
{
	if (l != NULL) {
		return l->cant == 0;
	}
}

unsigned int cantidadElementos(ListaPosInt l)
{
	if (l != NULL) {
		return l->cant;
	}
}

ListaPosInt clon(ListaPosInt l){
	ListaPosInt ret = new _cabezalListaPosInt;
	ret->cant = l->cant;
	ret->cota = l->cota;
	int* a = new int[ret->cant];
	for (int i = 0; i < ret->cant; i += 1) {
		a[i] = l->lista[i];
	}
	ret->lista = a;
	return ret;
}

void destruir(ListaPosInt& l)
{
	delete l;
}
#endif