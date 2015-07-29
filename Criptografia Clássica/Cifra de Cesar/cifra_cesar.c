#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int tam_vet, char *texto[]){//texto é o arquivo recebido
	FILE *arq=NULL;


	arq = fopen(texto[1],"r");
	if(!arq){
		return 0;//deve retornar ponteiro da lista nulo 
	}

	

	return 0;
}
