#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define TAMMAX 100

typedef struct{
	char dni[TAMMAX], nombre[TAMMAX];
	float peso, altura;
	unsigned int edad, puedeVotar;
}tPersona;

typedef tPersona tListaPersonas[20];

// Prototipos
void cargarDesdeArchivo(tListaPersonas lis, int *N, FILE *archivo);
void mostrarPersona(tPersona p);
void mostrarTodasPersonas(tListaPersonas lis, int N);
void determinarSiPuedeVotar(tListaPersonas lis, int N);
void reescribirArchivo(tListaPersonas lis, int N, FILE *archivo);

// Funcion principal
int main(int argc, char *argv[]) {
	FILE *archivo;
	tListaPersonas personas;
	int N;
	
	archivo = fopen("personas.txt", "r+");
	if(archivo != NULL){
		cargarDesdeArchivo(personas, &N, archivo);
		printf("----Personas recien cargadas----\n");
		mostrarTodasPersonas(personas, N);
		determinarSiPuedeVotar(personas, N);
		printf("----Personas luego de procesar----\n");
		mostrarTodasPersonas(personas, N);
		reescribirArchivo(personas, N, archivo);
		fclose(archivo);
	}
	else{
		printf("Error al abrir al archivo. No se puede procesar\n");
	}
	
	return 0;
}

// Funciones y procedimientos
tPersona separarCadena(char *linea){
	tPersona p;
	char *token = strtok(linea, ",");
	
	strcpy(p.dni, token);
	
	token = strtok(NULL, ",");
	strcpy(p.nombre, token);
	
	token = strtok(NULL, ",");
	p.peso = atof(token);
	
	token = strtok(NULL, ",");
	p.altura = atof(token);
	
	token = strtok(NULL, ",");
	p.edad = atoi(token);
	
	return p;
}

void cargarDesdeArchivo(tListaPersonas lis, int *N, FILE *archivo){
	char linea[200];
	int i = 0;
	
	while(!feof(archivo)){
		fgets(linea, 200, archivo);
		lis[i] = separarCadena(linea);
		i++;
	}
	
	*N = i;
}

void mostrarPersona(tPersona p){
	printf("DNI: %s\n", p.dni);
	printf("Nombre: %s\n", p.nombre);
	printf("Edad: %d\n", p.edad);
	printf("Peso: %f\n", p.peso);
	printf("Altura: %f\n", p.altura);
	printf("Puede votar: %d\n\n", p.puedeVotar);
}

void mostrarTodasPersonas(tListaPersonas lis, int N){
	int i;
	
	for(i=0; i<N; i++){
		mostrarPersona(lis[i]);
	}
}

void determinarSiPuedeVotar(tListaPersonas lis, int N){
	int i;
	
	for(i=0; i<N; i++){
		if(lis[i].edad >= 18){
			lis[i].puedeVotar = 1;
		}
		else{
			lis[i].puedeVotar = 0;
		}
	}
}

void reescribirArchivo(tListaPersonas lis, int N, FILE *archivo){
	rewind(archivo);
	int i;
	
	for(i=0; i<N; i++){
		fprintf(archivo, "%s,%s,%f,%f,%u,%u\n", lis[i].dni, lis[i].nombre, lis[i].peso, lis[i].altura, lis[i].edad, lis[i].puedeVotar);
	}
}

