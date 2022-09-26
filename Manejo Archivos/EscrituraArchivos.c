#include <stdio.h>
#include <string.h>

int main(){
	FILE *archivo, *tmp;
	char linea[50], aux[60];
	int i = 1;
	
	archivo = fopen("archivo2.txt", "a");
	tmp = fopen("temporal.tmp", "w+");
	
	
	if(archivo != NULL && tmp != NULL){
		while(!feof(archivo)){
			fgets(linea, 50, archivo);
			sprintf(aux, "%d. ", i);
			strcat(aux, linea); //1. Hola mi nombre es facundo
			fputs(aux, tmp);
			i++;
		}
		
		rewind(archivo);
		rewind(tmp);
		
		while(!feof(tmp)){
			fgets(aux, 60, tmp);
			fputs(aux, archivo);
		}
		
		remove("temporal.tmp");
		
		fclose(archivo);
		fclose(tmp);
	}
	
	//Uso de fprintf
	/*if(archivo != NULL){
		fprintf(archivo, "Punto x: %f, punto y: %f\n", 15.1, -4.0);
		
		fclose(archivo);
	}*/
	else
	   printf("Error al abrir el archivo\n");
	
	return 0;
}
