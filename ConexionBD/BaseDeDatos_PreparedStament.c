#include <stdio.h>
#include <mysql.h>
#include <string.h>
#include "DatosConexion.h"

#define TAM_CADENA 100
#define CONSULTA_POR_ID "SELECT * FROM usuarios WHERE id=?" 

int conectar(MYSQL **conexion);

int main(int argc, char *argv[]) {
	int error_conexion, id, id_res, columnas;
	unsigned long length[5];
	char nombre_res[TAM_CADENA], apellido_res[TAM_CADENA], telefono_res[TAM_CADENA], email_res[TAM_CADENA];
	bool is_null[5], error[5];
	MYSQL *conexion;
	MYSQL_STMT *stmt;
	MYSQL_BIND bind[1], bind2[5];
	MYSQL_RES *res_ptr;
	MYSQL_FIELD *campo;
	
	error_conexion = conectar(&conexion);
	if(!error_conexion){
		// Inicializacion de la variable stmt que va a gestionar todas las consultas preparadas
		stmt = mysql_stmt_init(conexion);
		
		if(stmt){
			// Cargar la sentencia preparada de CONSULTA_POR_ID en stmt
			if(!mysql_stmt_prepare(stmt, CONSULTA_POR_ID, strlen(CONSULTA_POR_ID))){
				
				// Cargar el vector que va a tener la informacion sobre los parametros necesarios para consulta
				memset(bind, 0, sizeof(bind));
				bind[0].buffer_type = MYSQL_TYPE_LONG;
				bind[0].buffer = (char *) &id;
				bind[0].is_null = 0;
				bind[0].length = 0;
				
				// Asociar el vector de parametros al prepared statement
				if(!mysql_stmt_bind_param(stmt, bind)){
					id = 3; // Se setean las variables asociadas a los parametros. En este caso solo tenemos una que es id
					
					// Ejecuto la consulta preparada
					if(!mysql_stmt_execute(stmt)){	
						// Cargo el vector que va a tener la informacion sobre lo que devuelve la consulta
						memset(bind2, 0, sizeof(bind2));
						
						bind2[0].buffer_type = MYSQL_TYPE_LONG;
						bind2[0].buffer = (char *) &id_res;
						bind2[0].is_null = &is_null[0];
						bind2[0].length = &length[0];
						bind2[0].error = &error[0];
						
						bind2[1].buffer_type = MYSQL_TYPE_STRING;
						bind2[1].buffer = (char *) apellido_res;
						bind2[1].buffer_length = TAM_CADENA;
						bind2[1].is_null = &is_null[1];
						bind2[1].length = &length[1];
						bind2[1].error = &error[1];
						
						bind2[2].buffer_type = MYSQL_TYPE_STRING;
						bind2[2].buffer = (char *) nombre_res;
						bind2[2].buffer_length = TAM_CADENA;
						bind2[2].is_null = &is_null[2];
						bind2[2].length = &length[2];
						bind2[2].error = &error[2];
						
						bind2[3].buffer_type = MYSQL_TYPE_STRING;
						bind2[3].buffer = (char *) telefono_res;
						bind2[3].buffer_length = TAM_CADENA;
						bind2[3].is_null = &is_null[3];
						bind2[3].length = &length[3];
						bind2[3].error = &error[3];
						
						bind2[4].buffer_type = MYSQL_TYPE_STRING;
						bind2[4].buffer = (char *) email_res;
						bind2[4].buffer_length = TAM_CADENA;
						bind2[4].is_null = &is_null[4];
						bind2[4].length = &length[4];
						bind2[4].error = &error[4];
						
						// Asocio el vector con el resultado de la consulta
						if(!mysql_stmt_bind_result(stmt, bind2)){
							res_ptr = mysql_stmt_result_metadata(stmt); // Obtengo metadatos
							
							if(res_ptr){
								columnas = mysql_num_fields(res_ptr);
								
								while(campo = mysql_fetch_field(res_ptr)){
									printf("%15s", campo->name);
								}
								printf("\n");
							}
							
							while(!mysql_stmt_fetch(stmt)){ // Recorro sobre las filas devueltas
								printf("%15d", id_res);
								printf("%15s", apellido_res);
								printf("%15s", nombre_res);
								printf("%15s", telefono_res);
								printf("%15s", email_res);
								printf("\n");
							}
							
							mysql_free_result(res_ptr); // Libero el MYSQQL_RES
							mysql_stmt_close(stmt); // Libero el prepared statement
						}
						else
							printf("Error al asociar los parametros de respuesta.\n");
					}
				}
				else
					printf("Error al asociar los parametros a la sentencia preparada.\n");
			}
			else
				printf("Error al preparar la sentencia.\n");
		}
		else
			printf("Error al inicializar la sentencia preparada.\n");
			
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
