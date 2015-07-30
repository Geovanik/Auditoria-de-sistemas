#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(void){
	int chave=0;
	char entrada[]="texto",lendo;
	FILE *arq;
	
	printf("digite a chave");
	scanf("%d",&chave);
	
	arq = fopen(entrada, "r");
	if(arq == NULL){
		printf("Erro, nao foi possivel abrir o arquivo\n");
		return 0;	
	}

	while( (lendo=fgetc(arq))!= EOF ){
		printf("letra %c\n",lendo);
		
		lendo=(lendo+256+chave)%256;//formula de criptografia
		
		
		printf("%c\n",lendo);	
	}
	fclose(arq);
	
	return 0;
}


