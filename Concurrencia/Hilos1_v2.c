/*************************
HANDLE CreateThread(
LPSECURITY_ATTRIBUTES   lpThreadAttributes,
SIZE_T                  dwStackSize,
LPTHREAD_START_ROUTINE  lpStartAddress,
LPVOID                  lpParameter,
DWORD                   dwCreationFlags,
LPDWORD                 lpThreadId
);
*************************/

#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

DWORD WINAPI funcion_muestra(LPVOID arg);

int main(int argc, char *argv[]) {
	HANDLE manejadorHilo1, manejadorHilo2;
	DWORD hilo1, hilo2;
	
	manejadorHilo1 = CreateThread(NULL, 0, funcion_muestra, (LPVOID)1, 0, &hilo1); // Creo el hilo1
	manejadorHilo2 = CreateThread(NULL, 0, funcion_muestra, (LPVOID)11, 0, &hilo2); // Creo el hilo2
	if(manejadorHilo1 == NULL || manejadorHilo2 == NULL){
		printf("Error al crear los hilos\n");
		exit(-1);
	}
	
	WaitForSingleObject(manejadorHilo1, INFINITE);
	WaitForSingleObject(manejadorHilo2, INFINITE);
	
	printf("Termino la ejecucion de los hilos\n");
	
	CloseHandle(manejadorHilo1);
	CloseHandle(manejadorHilo2);
	
	return 0;
}

DWORD WINAPI funcion_muestra(LPVOID arg){
	int i, ini;
	
	ini = (int)arg;
	for(i=ini; i<ini+10; i++){
		if(ini == 1)
			Sleep(1000 + rand() % (5000-1000+1));
		else
			Sleep(5000 + rand() % (10000-5000+1));
		
		printf("%d\n", i);
	}
	
	return 0;
}
