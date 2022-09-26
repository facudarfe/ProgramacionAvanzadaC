#include <stdio.h>
#include <mysql.h>
#include <string.h>
#include "DatosConexion.h"

#define TAM_CADENA 100
#define QUERY_INSERTAR "INSERT INTO usuarios(id, apellido, nombre, telefono, email) VALUES(?,?,?,?,?)" 
#define QUERY_ACTUALIZAR "UPDATE usuarios SET telefono = ? WHERE id = ?" 
#define QUERY_ELIMINAR "DELETE FROM usuarios WHERE id = ?" 

int conectar(MYSQL **conexion);
int menu();

int main(int argc, char *argv[]) {
	int error_conexion, id, id_res, columnas;
	unsigned long length[4];
	char nombre[TAM_CADENA], apellido[TAM_CADENA], telefono[TAM_CADENA], email[TAM_CADENA];
	bool is_null[5], error[5];
	MYSQL *conexion;
	MYSQL_STMT *stmt;
	MYSQL_BIND bind[5];
	MYSQL_RES *res_ptr;
	MYSQL_FIELD *campo;
	
	error_conexion = conectar(&conexion);
	if(!error_conexion){
		// Inicializacion de la variable stmt que va a gestionar todas las consultas preparadas
		stmt = mysql_stmt_init(conexion);
		
		if(stmt){
			
			switch(menu()){
				case 1: // INSERTAR
					// Cargar la sentencia preparada de QUERY_INSERTAR en stmt
					if(!mysql_stmt_prepare(stmt, QUERY_INSERTAR, strlen(QUERY_INSERTAR))){
						
						// Cargar el vector que va a tener la informacion sobre los parametros necesarios para consulta
						memset(bind, 0, sizeof(bind));
						bind[0].buffer_type = MYSQL_TYPE_LONG;
						bind[0].buffer = (char *) &id;
						bind[0].is_null = 0;
						bind[0].length = 0;
						
						bind[1].buffer_type = MYSQL_TYPE_STRING;
						bind[1].buffer = (char *) apellido;
						bind[1].buffer_length = TAM_CADENA;
						bind[1].is_null = 0;
						bind[1].length = &length[0];
						
						bind[2].buffer_type = MYSQL_TYPE_STRING;
						bind[2].buffer = (char *) nombre;
						bind[2].buffer_length = TAM_CADENA;
						bind[2].is_null = 0;
						bind[2].length = &length[1];
						
						bind[3].buffer_type = MYSQL_TYPE_STRING;
						bind[3].buffer = (char *) telefono;
						bind[3].buffer_length = TAM_CADENA;
						bind[3].is_null = 0;
						bind[3].length = &length[2];
						
						bind[4].buffer_type = MYSQL_TYPE_STRING;
						bind[4].buffer = (char *) email;
						bind[4].buffer_length = TAM_CADENA;
						bind[4].is_null = 0;
						bind[4].length = &length[3];
						
						// Asociar el vector de parametros al prepared statement
						if(!mysql_stmt_bind_param(stmt, bind)){
							printf("Ingrese id: "); scanf("%d", &id);
							printf("Ingrese apellido: "); scanf("%s", &apellido);
							length[0] = strlen(apellido);
							printf("Ingrese nombre: "); scanf("%s", &nombre);
							length[1] = strlen(nombre);
							printf("Ingrese telefono: "); scanf("%s", &telefono);
							length[2] = strlen(telefono);
							printf("Ingrese email: "); scanf("%s", &email);
							length[3] = strlen(email);
							
							// Ejecuto la consulta preparada
							if(!mysql_stmt_execute(stmt)){	
								// Veo la cantidad de filas afectadas con la sentencia
								if(mysql_stmt_affected_rows(stmt) > 0)
									printf("Registro insertado exitosamente\n");
								else
									printf("Error al insertar registro\n");
								
								mysql_stmt_close(stmt); // Libero el prepared statement
							}
						}
						else
							printf("Error al asociar los parametros a la sentencia preparada.\n");
					}
					else
						printf("Error al preparar la sentencia.\n");
					break;
				case 2: // ACTUALIZAR
					// Cargar la sentencia preparada de QUERY_ACTUALIZAR en stmt
					if(!mysql_stmt_prepare(stmt, QUERY_ACTUALIZAR, strlen(QUERY_ACTUALIZAR))){
						
						// Cargar el vector que va a tener la informacion sobre los parametros necesarios para consulta
						memset(bind, 0, sizeof(bind));
						bind[0].buffer_type = MYSQL_TYPE_STRING;
						bind[0].buffer = (char *) telefono;
						bind[0].buffer_length = TAM_CADENA;
						bind[0].is_null = 0;
						bind[0].length = &length[0];
						
						bind[1].buffer_type = MYSQL_TYPE_LONG;
						bind[1].buffer = (char *) &id;
						bind[1].is_null = 0;
						bind[1].length = 0;
						
						// Asociar el vector de parametros al prepared statement
						if(!mysql_stmt_bind_param(stmt, bind)){
							printf("Ingrese id: "); scanf("%d", &id);
							printf("Ingrese telefono: "); scanf("%s", &telefono);
							length[0] = strlen(telefono);
							
							// Ejecuto la consulta preparada
							if(!mysql_stmt_execute(stmt)){	
								// Veo la cantidad de filas afectadas con la sentencia
								if(mysql_stmt_affected_rows(stmt) > 0)
									printf("Registro actualizado exitosamente\n");
								else
									printf("Error al actualizar registro\n");
								
								mysql_stmt_close(stmt); // Libero el prepared statement
							}
						}
						else
							printf("Error al asociar los parametros a la sentencia preparada.\n");
					}
					else
						printf("Error al preparar la sentencia.\n");
					break;
				case 3: // ELIMINAR
					// Cargar la sentencia preparada de QUERY_ELIMINAR en stmt
					if(!mysql_stmt_prepare(stmt, QUERY_ELIMINAR, strlen(QUERY_ELIMINAR))){
						
						// Cargar el vector que va a tener la informacion sobre los parametros necesarios para consulta
						memset(bind, 0, sizeof(bind));	
						bind[0].buffer_type = MYSQL_TYPE_LONG;
						bind[0].buffer = (char *) &id;
						bind[0].is_null = 0;
						bind[0].length = 0;
						
						// Asociar el vector de parametros al prepared statement
						if(!mysql_stmt_bind_param(stmt, bind)){
							printf("Ingrese id: "); scanf("%d", &id);
							
							// Ejecuto la consulta preparada
							if(!mysql_stmt_execute(stmt)){	
								// Veo la cantidad de filas afectadas con la sentencia
								if(mysql_stmt_affected_rows(stmt) > 0)
									printf("Registro eliminado exitosamente\n");
								else
									printf("Error al eliminar registro\n");
								
								mysql_stmt_close(stmt); // Libero el prepared statement
							}
						}
						else
							printf("Error al asociar los parametros a la sentencia preparada.\n");
					}
					else
						printf("Error al preparar la sentencia.\n");
					break;
				default:
					printf("Opcion incorrecta\n");
			}
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

int menu(){
	int opc;
	
	printf("1- Insertar registro\n");
	printf("2- Actualizar registro\n");
	printf("3- Eliminar registro\n");
	printf("Ingrese opcion: "); scanf("%d", &opc);
	
	return opc;
}
