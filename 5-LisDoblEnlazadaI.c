#include <stdio.h>
#include <stdlib.h>

typedef struct Nodo{
	float dato;
	struct Nodo *ant;
	struct Nodo *sig;
}tNodo;

typedef struct{
	tNodo *ini;
	tNodo *fin;
}tLista;

tNodo *creaNodo(float x);
tLista inicializarLista();
void insertaInicio(tLista *lis, float x);
void insertaFinal(tLista *lis, float x);
void insertaPosicion(tLista *lis, float x, unsigned p);
void eliminaInicio(tLista *lis);
void eliminaFinal(tLista *lis);
void eliminaPosicion(tLista *lis, unsigned p);
void mostrar(tLista lis);
void mostrarInverso(tLista lis);

int main(int argc, char *argv[]) {
	tLista lis;
	
	lis = inicializarLista();
	
	insertaInicio(&lis, 1);
	insertaInicio(&lis, 2);
	insertaInicio(&lis, 3);
	insertaInicio(&lis, 4);
	insertaInicio(&lis, 5);
	
	mostrar(lis);
	return 0;
}

tNodo *creaNodo(float x){
	tNodo *nodo = (tNodo *)malloc(sizeof(tNodo));
	
	nodo->dato = x;
	nodo->ant = NULL;
	nodo->sig = NULL;
	
	return nodo;
}

tLista inicializarLista(){
	tLista lis;
	
	lis.ini = NULL;
	lis.fin = NULL;
	
	return lis;
}

void insertaInicio(tLista *lis, float x){
	tNodo *nodo = creaNodo(x);
	
	if(lis->ini != NULL){
		nodo->sig = lis->ini;
		(lis->ini)->ant = nodo;
		lis->ini = nodo;
	}
	else{
		lis->ini = lis->fin = nodo;
	}
}

void insertaFinal(tLista *lis, float x){
	tNodo *nodo = creaNodo(x);
	
	if(lis->ini != NULL){
		nodo->ant = lis->fin;
		(lis->fin)->sig = nodo;
		lis->fin = nodo;
	}
	else{
		lis->ini = lis->fin = nodo;
	}
}

void insertaPosicion(tLista *lis, float x, unsigned p){
	tNodo *nodo, *aux;
	int i = 0;
	
	if(lis->ini != NULL){
		aux = lis->ini;
		while(aux != NULL && i < p){
			aux = aux->sig;
			i++;
		}
		if(p == 0)
			insertaInicio(lis, x);
		else{
			if(aux == NULL)
				insertaFinal(lis, x);
			else{
				nodo = creaNodo(x);
				nodo->ant = aux->ant;
				nodo->sig = aux;
				(aux->ant)->sig = nodo;
				aux->ant = nodo;
			}
		}
	}
	else
		lis->ini = lis->fin = creaNodo(x);
}

void mostrar(tLista lis){
	tNodo *aux = lis.ini;
	
	while(aux != NULL){
		printf("%f\t", aux->dato);
		aux = aux->sig;
	}
}
void mostrarInverso(tLista lis){
	tNodo *aux = lis.fin;
	
	while(aux != NULL){
		printf("%f\t", aux->dato);
		aux = aux->ant;
	}
}

void eliminaInicio(tLista *lis){
	tNodo *nodo;
	
	if(lis->ini != NULL){
		nodo = lis->ini;
		lis->ini = (lis->ini)->sig;
		free(nodo);
		
		if(lis->ini == NULL)
			lis->fin = NULL;
	}
	else
		printf("Error al eliminar. Lista vacia\n");
}
void eliminaFinal(tLista *lis){
	tNodo *nodo;
	
	if(lis->fin != NULL){
		nodo = lis->fin;
		lis->fin = (lis->fin)->ant;
		free(nodo);
		
		if(lis->fin == NULL)
			lis->ini = NULL;
	}
	else
		printf("Error al eliminar. Lista vacia\n");
}
void eliminaPosicion(tLista *lis, unsigned p){
	tNodo *aux;
	int i = 0;
	
	if(lis->ini != NULL){
		aux = lis->ini;
		while(aux->sig != NULL && i < p){
			aux = aux->sig;
			i++;
		}
		if(p == 0)
			eliminaInicio(lis);
		else{
			if(aux->sig == NULL)
				eliminaFinal(lis);
			else{
				(aux->ant)->sig = aux->sig;
				(aux->sig)->ant = aux->ant;
				free(aux);
			}
		}
	}
	else
		printf("Error al eliminar. Lista vacia\n");
}
