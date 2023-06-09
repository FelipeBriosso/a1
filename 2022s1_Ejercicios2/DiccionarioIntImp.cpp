#include "DiccionarioInt.h"

#ifdef DICCIONARIO_INT_IMP
struct ListaDiccionario {
	int clave;
	ListaDiccionario* sig;
};

struct _cabezalDiccionarioInt {
	int cantE;
	int largo;
	ListaDiccionario** lista;
};
//pre:-
//post: hash

int hashDiccionario(int c, int t) {
	return c % t;
}
//pre:-
//post: devuelve si es primo o no.
bool esPrimoDiccionario(int n) {
	bool ret = n % 2 != 0 || n == 2;
	for (int i = 3; i < sqrt(n) && ret; i += 2) {
		ret = n % i != 0;
	}
	return ret;
}
//pre:-
//post: devuelve el siguiente primo.

int siguientePrimoDiccionario(int n) {
	while (!esPrimoDiccionario(n)) {
		n += 1;
	}
	return n;
}


DiccionarioInt crearDiccionarioInt(unsigned int esperados) {
	DiccionarioInt ret = new _cabezalDiccionarioInt;
	ret->cantE = 0;
	ret->largo = siguientePrimoDiccionario(esperados);
	ret->lista = new ListaDiccionario * [ret->largo];
	for (int i = 0; i < ret->largo; i += 1) {
		ret->lista[i] = NULL;
	}
	return ret;
}

void agregar(DiccionarioInt& d, int e) {
	int pos = hashDiccionario(abs(e), d->largo);
	ListaDiccionario* l = d->lista[pos];
	bool esta = false;
	ListaDiccionario* conClave = NULL;
	while (l != NULL && !esta) {
		conClave = l;
		esta = l->clave == e;
		l = l->sig;
	}
	if (esta) {
		conClave->clave = e;
	}
	else {
		ListaDiccionario* nuevo = new ListaDiccionario;
		nuevo->clave = e;
		nuevo->sig = d->lista[pos];
		d->lista[pos] = nuevo;
		d->cantE += 1;
	}
}

//pre:-
//post: borra el elemento de la lista del diccionario.
void borrarAux(ListaDiccionario*& d, int e) {
	if (d != NULL) {
		if (d->clave == e) {
			ListaDiccionario* borrar = d;
			d = d->sig;
			delete borrar;
		}
		else {
			borrarAux(d->sig, e);
		}
	}
}

void borrar(DiccionarioInt& d, int e) {
	if (pertenece(d, e)) {
		int pos = hashDiccionario(abs(e), d->largo);
		ListaDiccionario* l = d->lista[pos];
		borrarAux(l, e);
		d->lista[pos] = l;
		d->cantE -= 1;
	}
}

bool pertenece(DiccionarioInt d, int e) {
	int pos = hashDiccionario(abs(e), d->largo);
	ListaDiccionario* l = d->lista[pos];
	bool esta = false;
	while (l != NULL && !esta) {
		esta = l->clave == e;
		l = l->sig;
	}
	return esta;
}

int elemento(DiccionarioInt d) {
	int i = 0;
	int ret = 0;
	if (d->cantE > 0) {
		bool encontre = false;
		while (d != NULL && !encontre) {
			ListaDiccionario* l = d->lista[i];
			if (l != NULL) {
				ret = l->clave;
				encontre = true;
			}
			else {
				i += 1;
			}
		}
	}
	return ret;
}

bool esVacio(DiccionarioInt d) {
	bool ret = true;
	if (d != NULL) {
		ret = d->cantE == 0;
	}
	return ret;
}

unsigned int cantidadElementos(DiccionarioInt d) {
	int ret = 0;
	if (d != NULL) {
		ret = d->cantE;
	}
	return ret;
}
//pre:-
//post: copia la lista del diccionario sin compartir memoria.
ListaDiccionario* copiaListaDiccionario(ListaDiccionario* d) {
	ListaDiccionario* ret = NULL;
	if (d != NULL) {
		ret = new ListaDiccionario;
		ret->clave = d->clave;
		ret->sig = copiaListaDiccionario(d->sig);
	}
	return ret;
}

DiccionarioInt clon(DiccionarioInt d) {
	DiccionarioInt ret = new _cabezalDiccionarioInt;
	ret->largo = d->largo;
	ret->cantE = d->cantE;
	ret->lista = new ListaDiccionario * [ret->largo];
	for (int i = 0; i < ret->largo; i += 1) {
		ret->lista[i] = copiaListaDiccionario(d->lista[i]);
	}
	return ret;
}
//pre:-
//post: destruye la lista del diccionario.
void destruirListaDiccionario(ListaDiccionario* d) {
	while (d != NULL) {
		ListaDiccionario* borrar = d;
		d = d->sig;
		delete borrar;
	}
}

void destruir(DiccionarioInt& d) {
	for (int i = 0; i < d->largo; i += 1) {
		destruirListaDiccionario(d->lista[i]);
	}
	delete[] d->lista;
	delete d;
}


#endif