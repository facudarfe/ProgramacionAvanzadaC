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
#include <stdlib.h>

void mostrarPilaDeMensajes(char pila_mensajes[][400], int cantMensajes);

int main(int argc, char **argv){
	WSADATA wsa;
	SOCKET skt, skt2;
	int longitud_cliente, puerto = 55227, recv_size, cantMensajes;
	struct sockaddr_in server, cliente;
	char mensaje[2000];
	char pila_mensajes[2000][400];
	
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
	printf("Esperando conexiones entrantes...\n");
	
	longitud_cliente = sizeof(struct sockaddr_in);
	skt2 = accept(skt, (struct sockaddr*)&cliente, &longitud_cliente);
	if(skt2 == INVALID_SOCKET){
		printf("Fallo al aceptar la conexion\n");
		exit(-1);
	}
	
	/**********************INICIO DEL CHAT**********************/	
	system("cls");
	sprintf(pila_mensajes[0], "----------------------------------------------------\n-----------------CHAT CON %s-----------------\n----------------------------------------------------\n\n",
			inet_ntoa(cliente.sin_addr));
	printf("%s", pila_mensajes[0]);
	
	cantMensajes = 0; // Variable usada para ir contando la cantidad de mensajes de la conversacion
	while((recv_size = recv(skt2, mensaje, 2000, 0)) != SOCKET_ERROR){
		cantMensajes++;
		mensaje[recv_size] = '\0';
		printf("\033[0;36m"); // Color verde
		sprintf(pila_mensajes[cantMensajes], "R: %s\n", mensaje); // Agrego mensaje a la pila
		printf(pila_mensajes[cantMensajes]);
		
		if(strcmp(mensaje, "<salir>") != 0){ // Si no recibo el comando <salir> entonces continuo
			printf("\033[0;37m"); // Color blanco
			printf("Ingrese respuesta: "); gets(mensaje);
			if(send(skt2, mensaje, strlen(mensaje), 0) >= 0){ // Mensaje enviado correctamente
				cantMensajes++;
				printf("\033[0;32m"); // Color blanco
				sprintf(pila_mensajes[cantMensajes], "E: %100s\n", mensaje); // Agrego mensaje a la pila
			}
			
			system("cls");
			mostrarPilaDeMensajes(pila_mensajes, cantMensajes);
			
			if(strcmp(mensaje, "<salir>") == 0)
				break;
		}
		else
			break; // Si recibi el comando <salir> se corta el programa
	}
	
	system("pause");
	
	closesocket(skt);
	WSACleanup();
	
	return 0;
}

void mostrarPilaDeMensajes(char pila_mensajes[][400], int cantMensajes){
	int i;
	
	printf("\033[0;37m"); // Color blanco
	printf(pila_mensajes[0]);
	for(i=1; i<=cantMensajes; i++){
		if(pila_mensajes[i][0] == 'R')
			printf("\033[0;36m"); // Color cyan
		else
			printf("\033[0;32m"); // Color verde
			
		printf(pila_mensajes[i]);
	}
}
