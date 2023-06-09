#include "ListaPosInt.h"

#ifdef LISTA_POS_INT_IMP

struct _cabezalListaPosInt {
	int cota;
	int* lista;
	int cant;
};

ListaPosInt crearListaPosInt() {
	ListaPosInt ret = new _cabezalListaPosInt;
	ret->cota = 10;
	ret->lista = new int[10];
	ret->cant = 0;
	return ret;
}

void agregar(ListaPosInt& l, int e, unsigned int pos) {

}

void borrar(ListaPosInt& l, unsigned int pos) {
	
}

int elemento(ListaPosInt l, unsigned int pos) {
	return 0;
}

bool esVacia(ListaPosInt l)
{
	return true;
}

unsigned int cantidadElementos(ListaPosInt l){
	return 0;
}

ListaPosInt clon(ListaPosInt l) {
	return NULL;
}

void destruir(ListaPosInt& l) {

}
#endif