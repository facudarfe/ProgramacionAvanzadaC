#include <stdio.h>
#include <mysql.h>
#include "DatosConexion.h"

int conectar(MYSQL **conexion);
void ejecutar_consulta(MYSQL *conexion, char *consulta);

int main(int argc, char *argv[]) {
	int error;
	char consulta[200], id[100];
	MYSQL *conexion;
	
	error = conectar(&conexion);
	if(!error){
		printf("Ingresar nombre del usuario: "); gets(id);
		sprintf(consulta, "SELECT * FROM usuarios WHERE id=%s", id); //SELECT * FROM usuarios WHERE id=1 OR 1=1
		ejecutar_consulta(conexion, consulta);
		mysql_close(conexion);
	}
	return 0;
}

int conectar(MYSQL **conexion){
	int error;
	
	*conexion = mysql_init(NULL);

	if(mysql_real_connect(*conexion, HOST, USERNAME, PASSWORD, DATABASE, PORT, NULL, 0) != NULL){
		printf("Se establecio la conexion con la base de datos\n");
		error = 0;
	}
	else{
		printf("Error al conectarse con la base de datos\n");
		error = 1;
	}
	
	return error;
}

void ejecutar_consulta(MYSQL *conexion, char *consulta){
	int error, filas, columnas, i, j;
	MYSQL_RES *res_ptr;
	MYSQL_FIELD *campo;
	MYSQL_ROW res_fila;
	
	error = mysql_query(conexion, consulta);
	if(!error){
		res_ptr = mysql_store_result(conexion);
		if(res_ptr){
			filas = mysql_num_rows(res_ptr);
			columnas = mysql_num_fields(res_ptr);
			
			while(campo = mysql_fetch_field(res_ptr)){
				printf("%15s", campo->name);
			}
			printf("\n");
			
			for(i=1; i<=filas; i++){
				res_fila = mysql_fetch_row(res_ptr);
				for(j=0; j<columnas; j++){
					printf("%15s", res_fila[j]);
				}
				printf("\n");
			}
		}
		else{
			printf("Error al obtener resultados\n");
		}
	}
	else{
		printf("Ocurrio un error al ejecutar la consulta SQL\n");
	}
}
