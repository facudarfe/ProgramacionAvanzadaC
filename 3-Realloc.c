#include <stdio.h>
#include <stdlib.h>

void cargarVector(int *V, int N);
void mostrarVector(int *V, int N);

int main(int argc, char *argv[]) {
	int *V = NULL, N;
	void *tmp = NULL;
	
	printf("Ingrese N: "); scanf("%d", &N);
	V = (int *)calloc(N, sizeof(int));
	
	if(V != NULL){
		cargarVector(V, N);
		mostrarVector(V, N);
	}
	else
	   printf("Error. No se pudo reservar memoria.");
	
	printf("Ingrese nuevo tamanio del vector: "); scanf("%d", &N);
	tmp = realloc(V, N);
	
	if(tmp != NULL)
		mostrarVector(V, N);
	else
		printf("Ocurrio un error");
	
	free(V);
	V = NULL;
	
	return 0;
}

void cargarVector(int *V, int N){
	int i;
	
	for(i=0; i<N; i++){
		printf("Elemento %d: ", i);
		scanf("%d", &V[i]);
	}
}

void mostrarVector(int *V, int N){
	int i;
	
	for(i=0; i<N; i++){
		printf("%d\t", V[i]);
	}
	printf("\n");
}

