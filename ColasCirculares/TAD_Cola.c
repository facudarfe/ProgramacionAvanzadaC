#include "TAD_Cola.h"
#include <stdio.h>

tCola inicializaCola(){
	tCola cola;
	
	cola.ini = cola.fin = 0;
	
	return cola;
}
	
int estaVacia(tCola cola){
	return cola.ini == cola.fin;
}
	
int estaLlena(tCola cola){
	if(cola.fin == TAMMAX - 1 && cola.ini == 0)
		return 1;
	else
		return cola.fin == cola.ini - 1;
}
	
void push(tCola *cola, int elem){
	if(!estaLlena(*cola)){
		cola->lis[cola->fin] = elem;
		if(cola->fin == TAMMAX -1)
			cola->ini = 0;
		else
			cola->ini = cola->ini + 1;
	}
	else
		printf("Cola vacia.\n");
}
	
int pop(tCola *cola){
	int elem;
	
	if(!estaVacia(*cola)){
		elem = cola->lis[cola->ini];
		if(cola->ini == TAMMAX - 1)
			cola->ini = 0;
		else
			cola->ini = cola->ini + 1;
		
		return elem;
	}
	else{
		printf("Cola vacia.\n");
		return -1;
	}
}
