#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#define MAX_THREADS 20
#define TAM_MAX 100000

void cargarLista(int lista[], long tam);
DWORD WINAPI sumarLista(LPVOID arg);

typedef struct {
	int *lista;
	long ini, fin, suma;
} TdatosLista;

int main(int argc, char *argv[]) {
	int i, cantHilos, lista[TAM_MAX];
	long ini, fin, tamLista, sumaTotal = 0;
	TdatosLista **parms;
	HANDLE manejadoresHilos[MAX_THREADS];
	DWORD hilos[MAX_THREADS];
	
	tamLista = 100000;
	cargarLista(lista, tamLista);
	
	cantHilos = 4;
	parms = (TdatosLista **)malloc(sizeof(TdatosLista *));
	for(i=0; i<cantHilos; i++){
		ini = ((int)tamLista / cantHilos) * i;
		fin = i < cantHilos ? ((int)tamLista / cantHilos) * (i+1) : tamLista;
		
		parms[i] = (TdatosLista*)malloc(sizeof(TdatosLista));
		parms[i]->lista = lista;
		parms[i]->ini = ini;
		parms[i]->fin = fin;
		parms[i]->suma = 0;
		
		manejadoresHilos[i] = CreateThread(NULL, 0, sumarLista, (LPVOID)parms[i], 0, &hilos[i]);
		if(manejadoresHilos[i] == NULL){
			printf("Error al crear el hilo %d\n", i);
			exit(-1);
		}
	}
	
	WaitForMultipleObjects(cantHilos, manejadoresHilos, TRUE, INFINITE);
	
	printf("Termino la ejecucion de los hilos\n");
	
	for(i=0; i<cantHilos; i++){
		printf("Suma hilo %d: %ld\n", i, parms[i]->suma);
		sumaTotal += parms[i]->suma;
		CloseHandle(manejadoresHilos[i]);
	}
	
	printf("\nSuma total: %ld\n", sumaTotal);
	
	return 0;
}

void cargarLista(int lista[], long tam){
	long i;
	
	for(i=0; i<tam; i++){
		lista[i] = 1 + rand() % 1000;
	}
}

DWORD WINAPI sumarLista(LPVOID arg){
	TdatosLista *parms = (TdatosLista *)arg;
	int *lista = parms->lista;
	long i, ini, fin, *suma;
	
	ini = parms->ini;
	fin = parms->fin;
	suma = &(parms->suma);
	
	for(i=ini; i<fin; i++){
		*suma = *suma + lista[i];
	}
	
	return 0;
}
