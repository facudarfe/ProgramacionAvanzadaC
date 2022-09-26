#include <stdio.h>

int main(){
	FILE *archivo;
	char c;
	char linea[50];
	float x, y;
	
	archivo = fopen("archivo3.txt", "r");
	if(archivo != NULL){
		while(!feof(archivo)){
			fscanf(archivo, "%f,%f", &x, &y);
			printf("Punto x: %f, punto y: %f\n", x, y);
		}
		fclose(archivo);
	}
	else{
		printf("Error al abrir el archivo\n");
	}
	
	return 0;
}
