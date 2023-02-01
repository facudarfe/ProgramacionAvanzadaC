#include <stdio.h>
#include <stdlib.h>
#define TAM_MAX 100000

void cargarLista(int lista[], long tam);

int main(int argc, char *argv[]) {
	int i, lista[TAM_MAX];
	long tamLista, sumaTotal = 0;
	
	tamLista = 100000;
	cargarLista(lista, tamLista);
	
	for(i=0; i<tamLista; i++){
		sumaTotal += lista[i];
	}
	
	printf("Suma total: %ld\n", sumaTotal);
	
	return 0;
}

void cargarLista(int lista[], long tam){
	long i;
	
	for(i=0; i<tam; i++){
		lista[i] = 1 + rand() % 1000;
	}
}
