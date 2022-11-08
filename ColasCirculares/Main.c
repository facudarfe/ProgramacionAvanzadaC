#include <stdio.h>
#include "TAD_Cola.h"

int main(){
	tCola cola;
	int i;
	
	cola = inicializaCola();
	for(i=1; i<=4; i++){
		push(&cola, i);
	}
	
	for(i=1; i<=4; i++){
		printf("%d\n", pop(&cola));
	}
}
