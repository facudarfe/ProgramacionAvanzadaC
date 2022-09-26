#include <stdio.h>
#include <stdlib.h>

int **inicializarMatriz(int N, int M);
void cargarMatriz(int **A, int N, int M);
void mostrarMatriz(int **A, int N, int M);

int main(int argc, char *argv[]) {
	int **A;
	int N = 3, M = 3;
	
	A = inicializarMatriz(N, M);
	cargarMatriz(A, N, M);
	mostrarMatriz(A, N, M);
	
	return 0;
}

int **inicializarMatriz(int N, int M){
	int **A;
	int i;
	
	A = (int **)calloc(N, sizeof(int *));
	for(i=0; i<N; i++){
		A[i] = (int *)calloc(M, sizeof(int));
	}
	
	return A;
}

void cargarMatriz(int **A, int N, int M){
	int i, j;
	
	for(i=0; i<N; i++){
		for(j=0; j<M; j++){
			printf("Ingrese elemento (%d, %d): ", i, j);
			scanf("%d", &A[i][j]);
		}
	}
}

void mostrarMatriz(int **A, int N, int M){
	int i, j;
	
	for(i=0; i<N; i++){
		for(j=0; j<M; j++){
			printf("%d\t", A[i][j]);
		}
		printf("\n");
	}
}

