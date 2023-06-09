#include "MultisetInt.h"

#ifdef MULTISET_INT_IMP
struct ListaMultiSetLista {
	int clave;
	int ocurrencias;
	ListaMultiSetLista* sig;
};

struct _cabezalMultisetInt {
	int cantE;
	int largo;
	ListaMultiSetLista** lista;
};
//pre:-
//post: hash

int hashMultiSetInt(int c, int t) {
	return c % t;
}
//pre:-
//post: devuelve si es primo o no.
bool esPrimoMultiSetInt(int n) {
	bool ret = n % 2 != 0 || n == 2;
	for (int i = 3; i < sqrt(n) && ret; i += 2) {
		ret = n % i != 0;
	}
	return ret;
}

//pre:-
//post: devuelve el siguiente primo.
int siguientePrimoMultiSetInt(int n) {
	while (!esPrimoMultiSetInt(n)) {
		n += 1;
	}
	return n;
}


MultisetInt crearMultisetInt() {
	MultisetInt ret = new _cabezalMultisetInt;
	ret->cantE = 0;
	ret->largo = siguientePrimoMultiSetInt(10);
	ret->lista = new ListaMultiSetLista * [ret->largo];
	for (int i = 0; i < ret->largo; i += 1) {
		ret->lista[i] = NULL;
	}
	return ret;
}


void agregar(MultisetInt& s, int e, unsigned int ocurrencias){
	int pos = hashMultiSetInt(abs(e), s->largo);
	ListaMultiSetLista* l = s->lista[pos];
	bool esta = false;
	ListaMultiSetLista* conClave = NULL;
	while (l != NULL && !esta) {
		conClave = l;
		esta = l->clave == e;
		l = l->sig;
	}
	if (esta) {
		conClave->clave = e;
		conClave->ocurrencias += ocurrencias;
		s->cantE += ocurrencias;
	}
	else {
		ListaMultiSetLista* nuevo = new ListaMultiSetLista;
		nuevo->clave = e;
		nuevo->ocurrencias = ocurrencias;
		nuevo->sig = s->lista[pos];
		s->lista[pos] = nuevo;
		s->cantE += ocurrencias;
	}
}
//pre:-
//post: borra el elemento de la lista del Multiset.
void borrarAuxMultiSet(ListaMultiSetLista*& l, int e) {
	if (l != NULL) {
		if (l->clave == e) {
			if (l->ocurrencias>1) {
				l->ocurrencias -= 1;
			}
			else {
				ListaMultiSetLista* borrar = l;
				l = l->sig;
				delete borrar;
			}
		}
		else {
			borrarAuxMultiSet(l->sig, e);
		}
	}
}

void borrar(MultisetInt& s, int e) {
	if (pertenece(s, e)) {
		int pos = hashMultiSetInt(abs(e), s->largo);
		ListaMultiSetLista* l = s->lista[pos];
		borrarAuxMultiSet(l, e);
		s->lista[pos] = l;
		s->cantE -= 1;
	}
}

bool pertenece(MultisetInt s, int e) {
	int pos = hashMultiSetInt(abs(e), s->largo);
	ListaMultiSetLista* l = s->lista[pos];
	bool esta = false;
	while (l != NULL && !esta) {
		esta = l->clave == e;
		l = l->sig;
	}
	return esta;
}

int recuperarOcurrencias(MultisetInt s, int i) {
	int ret = 0;
	int pos = hashMultiSetInt(abs(i), s->largo);
	ListaMultiSetLista* l = s->lista[pos];
	bool esta = false;
	while (l != NULL && !esta) {
		if (l->clave == i) {
			esta = true;
			ret = l->ocurrencias;
		}
		
		l = l->sig;
	}
	return ret;
}

MultisetInt unionConjuntos(MultisetInt s1, MultisetInt s2) {
	MultisetInt ret = clon(s1);
	MultisetInt aux = clon(s2);
	while (!esVacio(aux)) {
		int i = elemento(aux);
		int ocurrencia= recuperarOcurrencias(aux, i);
		if (pertenece(ret, i)) {
			int ocurrencia2 = recuperarOcurrencias(ret, i);
			if (ocurrencia > ocurrencia2) {
				borrar(ret, i);
				agregar(ret, i, ocurrencia);
			}
			borrar(aux, i);
		}
		else {
			agregar(ret, i, ocurrencia);
			borrar(aux, i);
		}
		
	}
	destruir(aux);
	return ret;
}

MultisetInt interseccionConjuntos(MultisetInt s1, MultisetInt s2) {
	MultisetInt aux1 = diferenciaConjuntos(s1, s2);
	MultisetInt aux2 = diferenciaConjuntos(s2, s1);
	MultisetInt ret = unionConjuntos(s1, s2);
	while (!esVacio(aux1)) {
		int i = elemento(aux1);
		borrar(aux1, i);
		if (pertenece(ret, i)) {
			borrar(ret, i);
		}
	}
	while (!esVacio(aux2)) {
		int i = elemento(aux2);
		borrar(aux2, i);
		if (pertenece(ret, i)) {
			borrar(ret, i);
		}
	}
	destruir(aux1);
	destruir(aux2);
	return ret;
}


MultisetInt diferenciaConjuntos(MultisetInt s1, MultisetInt s2) {
	MultisetInt aux1 = clon(s1);
	MultisetInt aux2 = clon(s2);
	MultisetInt ret = crearMultisetInt();
	while (!esVacio(aux1)) {
		int i = elemento(aux1);
		int ocurrencia1 = recuperarOcurrencias(aux1, i);
		if (pertenece(aux2, i)) {
			int ocurrencia2 = recuperarOcurrencias(aux2, i);
			while (pertenece(aux1, i)) {
				borrar(aux1, i);
			}
			int totalOcurrencias = ocurrencia1 - ocurrencia2;
			if (totalOcurrencias > 0) {
				agregar(ret, i, totalOcurrencias);
			}
		}
		else {
			agregar(ret, i, ocurrencia1);
			while (pertenece(aux1, i)) {
				borrar(aux1, i);
			}
		}
	}
	destruir(aux1);
	destruir(aux2);
	return ret;
}

bool contenidoEn(MultisetInt s1, MultisetInt s2) {
	bool ret = true;
	MultisetInt aux1 = clon(s1);
	MultisetInt aux2 = clon(s2);
	while (!esVacio(aux1) && ret) {
		int i = elemento(aux1);
		if (pertenece(aux2, i)) {
			if (recuperarOcurrencias(aux1, i) <= recuperarOcurrencias(aux2, i)) {
				borrar(aux1, i);
			}
			else {
				ret = false;
			}
		}
		else {
			ret = false;
		}
	}
	destruir(aux1);
	destruir(aux2);
	return ret;
}

int elemento(MultisetInt s) {
	int i = 0;
	if (s->cantE > 0) {
		while (s != NULL) {
			ListaMultiSetLista* l = s->lista[i];
			if (l != NULL) {
				return l->clave;
			}
			else {
				i += 1;
			}
		}
	}
}

bool esVacio(MultisetInt s) {
	bool ret = true;
	if (s != NULL) {
		ret = s->cantE == 0;
	}
	return ret;
}

unsigned int cantidadElementos(MultisetInt s) {
	int ret = 0;
	if (s != NULL) {
		ret = s->cantE;
	}
	return ret;
}

//pre:-
//post: destruye la lista del MultiSet.

void destruirMultiSetAux(ListaMultiSetLista* l) {
	while (l != NULL) {
		ListaMultiSetLista* borrar = l;
		l = l->sig;
		delete borrar;
	}
}

void destruir(MultisetInt& s) {
	for (int i = 0; i < s->largo; i += 1) {
		destruirMultiSetAux(s->lista[i]);
	}
	delete[] s->lista;
	delete s;
}
//pre:-
//post: copia la lista del Multiset sin compartir memoria.
ListaMultiSetLista* copiarListaMulti(ListaMultiSetLista* l) {
	ListaMultiSetLista* ret = NULL;
	if (l != NULL) {
		ret = new ListaMultiSetLista;
		ret->clave = l->clave;
		ret->ocurrencias = l->ocurrencias;
		ret->sig = copiarListaMulti(l->sig);
	}
	return ret;
}

MultisetInt clon(MultisetInt s) {
	MultisetInt ret = new _cabezalMultisetInt;
	ret->largo = s->largo;
	ret->cantE = s->cantE;
	ret->lista = new ListaMultiSetLista * [ret->largo];
	for (int i = 0; i < ret->largo; i += 1) {
		ret->lista[i] = copiarListaMulti(s->lista[i]);
	}
	return ret;
}

#endif