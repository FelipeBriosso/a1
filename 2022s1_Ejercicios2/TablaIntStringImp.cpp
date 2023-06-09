#include "TablaIntString.h"

#ifdef TABLA_INT_STRING_IMP

struct ListaIntString {
	int clave;
	char* valor;
	ListaIntString* sig;
};


struct _cabezalTablaIntString {
	int cantE;
	int largo;
	ListaIntString** lista;
};
//pre:-
//post: hash

int hashTabla(int c, int t) {
	return c % t;
}
//pre:-
//post: devuelve si es primo o no.
bool esPrimoTabla(int n) {
	bool ret = n % 2 != 0 || n == 2;
	for (int i = 3; i < sqrt(n) && ret; i += 2) {
		ret = n % i != 0;
	}
	return ret;
}
//pre:-
//post: devuelve el siguiente primo.
int siguientePrimoTabla(int n) {
	while (!esPrimoTabla(n)) {
		n += 1;
	}
	return n;
}


TablaIntString crearTablaIntString(unsigned int esperados) {
	TablaIntString ret = new _cabezalTablaIntString;
	ret->cantE = 0;
	ret->largo = siguientePrimoTabla(esperados);
	ret->lista = new ListaIntString * [ret->largo];
	for (int i = 0; i < ret->largo; i += 1) {
		ret->lista[i] = NULL;
	}
	return ret;
}


void agregar(TablaIntString& t, int d, const char* r) {
	int pos = hashTabla(d, t->largo);
	ListaIntString* l = t->lista[pos];
	bool esta = false;
	ListaIntString* conClave = NULL;
	while (l != NULL && !esta) {
		conClave = l;
		esta = l->clave == d;
		l = l->sig;
	}
	if (esta) {
		delete[] conClave->valor;
		conClave->valor = new char[strlen(r) + 1];
		strcpy_s(conClave->valor, strlen(r) + 1, r);
	}
	else {
		ListaIntString* nuevo = new ListaIntString;
		nuevo->clave = d;
		nuevo->valor = new char[strlen(r) + 1];
		strcpy_s(nuevo->valor, strlen(r) + 1, r);
		nuevo->sig = t->lista[pos];
		t->lista[pos] = nuevo;
		t->cantE += 1;
	}
}

bool estaDefinida(TablaIntString t, int d) {
	int pos = hashTabla(d, t->largo);
	ListaIntString* l = t->lista[pos];
	bool esta = false;
	while (l != NULL && !esta) {
		esta = l->clave == d;
		l = l->sig;
	}
	return esta;
}

char* recuperar(TablaIntString t, int d) {
	int pos = hashTabla(d, t->largo);
	ListaIntString* l = t->lista[pos];
	while (l != NULL && l->clave != d) {
		l = l->sig;
	}
	if (l != NULL) {
		char* ret = new char[strlen(l->valor) + 1];
		strcpy_s(ret, strlen(l->valor) + 1, l->valor);
		return ret;
	}
}
//pre:-
//post: borra el elemento de la lista de la tabla.
void borrarAux(ListaIntString*& l, int d) {
	if (l != NULL) {
		if (l->clave == d) {
			ListaIntString* borrar = l;
			l = l->sig;
			delete borrar;
		}
		else {
			borrarAux(l->sig, d);
		}
	}
}

void borrar(TablaIntString& t, int d) {
	if (estaDefinida(t, d)) {
		int pos = hashTabla(d, t->largo);
		ListaIntString* l = t->lista[pos];
		borrarAux(l, d);
		t->lista[pos] = l;
		t->cantE -= 1;
	}
}

int elemento(TablaIntString t) {
	int i = 0;
	if (t->cantE > 0) {
		while (t != NULL) {
			ListaIntString* l = t->lista[i];
			if (l != NULL) {
				return l->clave;
			}
			else {
				i += 1;
			}
		}
	}
}

bool esVacia(TablaIntString t) {
	bool ret = true;
	if (t != NULL) {
		ret = t->cantE == 0;
	}
	return ret;
}

unsigned int cantidadElementos(TablaIntString t) {
	int ret = 0;
	if (t != NULL) {
		ret = t->cantE;
	}
	return ret;
}
//pre:-
//post: destruye la lista de la tabla.
void destruirTablaIntStringAux(ListaIntString* l) {
	while (l != NULL) {
		ListaIntString* borrar = l;
		l = l->sig;
		delete borrar;
	}
}

void destruir(TablaIntString& t) {
	for (int i = 0; i < t->largo; i += 1) {
		destruirTablaIntStringAux(t->lista[i]);
	}
	delete[] t->lista;
	delete t;
}
//pre:-
//post: copia la lista de la tabla sin compartir memoria.
ListaIntString* copiarListaIntString(ListaIntString* l) {
	ListaIntString* ret = NULL;
	if (l != NULL) {
		ret = new ListaIntString;
		ret->clave = l->clave;
		char* aux = l->valor;
		ret->valor = new char[strlen(aux) + 1];
		for (int i = 0; i < strlen(aux) + 1; i += 1) {
			ret->valor[i] = aux[i];
		}
		ret->sig = copiarListaIntString(l->sig);
	}
	return ret;
}

TablaIntString clon(TablaIntString t) {
	TablaIntString ret = new _cabezalTablaIntString;
	ret->largo = t->largo;
	ret->cantE = t->cantE;
	ret->lista = new ListaIntString * [ret->largo];
	for (int i = 0; i < ret->largo; i += 1) {
		ret->lista[i] = copiarListaIntString(t->lista[i]);
	}
	return ret;
}

#endif