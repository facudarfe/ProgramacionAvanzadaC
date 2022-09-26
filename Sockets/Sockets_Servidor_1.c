/***********************************************************/
/*********************PROGRAMA SERVIDOR*********************/
/***********************************************************/

// Estructura utilizada por el socket
/*
struct sockaddr_in{
	short int sin_family; 			// Familia de direcciones. Usaremos siempre "AF_INET"
	unsigned short int sin_port; 	// Numero de puerto
	struct in_addr sin_addr;		// Estructura que indica la direccion IP
	unsigned char sin_zero[8];		// Array de 8 bytes rellenados a cero.
}
*/


// Protocolos disponibles para el transporte de datos
/*
TCP (SOCK_STREAM) --> 	Socket de flujo que define una comunicacion bidireccional, confiables y orientada a la conexion.
						Todo lo que se mande desde el origen llegará al destino.
						Necesitan mantener una conexion abierta.
		
UDP (SOCK_DGRAM) --> 	Socket de datagramas que no esta orientado a la conexion y no es confiable.
						No precisan mantener una conexion abierta.
*/

#include <stdio.h>
#include <winsock2.h>
#include <string.h>

int main(int argc, char **argv){
	WSADATA wsa;
	SOCKET skt, skt2;
	int longitud_cliente, puerto = 55227;
	struct sockaddr_in server, cliente;
	
	/**********************INICIALIZACION WINSOCK**********************/
	printf("Inicializando Winsock...");
	if(WSAStartup(MAKEWORD(2, 2), &wsa) != 0){
		printf("Error al inicializar winsock\n");
		exit(-1);
	}
	printf("Winsock inicializado\n");
	
	/**********************CREACION SOCKET**********************/
	printf("Creando socket...");
	if((skt = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET){
		printf("Error creando socket\n");
		exit(-1);
	}
	printf("Socket creado\n");
	
	/**********************CONFIGURACION SOCKADDR_IN**********************/	
	server.sin_family = AF_INET; // Familia TCP/IP
	server.sin_port = htons(puerto); // Puerto
	server.sin_addr.s_addr = INADDR_ANY; // Cualquier cliente puede conectarse
	
	/**********************REALIZAR EL BIND**********************/
	if(bind(skt, (struct sockaddr*)&server, sizeof(server)) == SOCKET_ERROR){
		printf("Error al realizar el bind\n");
		exit(-1);
	}
	printf("Bind realizado\n");
	
	listen(skt, 5);
	printf("Esperando conexiones entrantes...");
	
	longitud_cliente = sizeof(struct sockaddr_in);
	skt2 = accept(skt, (struct sockaddr*)&cliente, &longitud_cliente);
	if(skt2 == INVALID_SOCKET)
		printf("Fallo al aceptar la conexion\n");
	
	
	closesocket(skt);
	WSACleanup();
	
	return 0;
}
