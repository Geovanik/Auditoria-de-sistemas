

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define CHAVE 3

int main(void){
	
	char lendo;
	
	while(scanf("%c",&lendo)!=EOF){//le o arquivo vindo por montagem de arquivo na compilação
		lendo=(lendo+256-CHAVE)%256;//formula de criptografia
		printf("%c",lendo);	
	}
	return 0;
}
