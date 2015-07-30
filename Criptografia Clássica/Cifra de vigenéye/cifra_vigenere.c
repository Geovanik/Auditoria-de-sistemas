
//como compilar: gcc cifra_cesar.c -o cifra_cesar -Wall       ./cifra_cesar < texto > criptografado  "texto é o arquivo com dados a serem criptografados"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(void){

	int contador=0,tam_entrada=0,tam_chave=0,aux=0,i;
	char lendo,entrada[1000],chave[1000]="limao\0",criptografado[1000];
	
	
	while(scanf("%c",&lendo)!=EOF){//le o arquivo vindo por montagem de arquivo na compilação
		entrada[contador]=lendo;
		contador++;
	}
	entrada[contador]='\0';
	
	tam_entrada = strlen(entrada);
	tam_chave = strlen(chave);
	
	
	if( tam_chave < tam_entrada ){//deixando a chave no tamanho da entrada
		while(tam_chave < tam_entrada){
			chave[tam_chave] = chave[aux];
			tam_chave++;
			aux++;
			if(aux > tam_chave)
				aux=0;
		}
		
	}

	for(i=0;i < tam_entrada;i++){
		
		criptografado[i] = (((entrada[i]+chave[i])+256)%256);
		printf("entrada na posicao i: %d\n",entrada[i]);
		printf("chave na posicao i: %d\n",chave[i]);
		printf("criptografado na posicao i: %d\n",criptografado[i]);
	
		//printf("%d\n",criptografado);
	}

	criptografado[i]='\0';
	
	printf("%s\n",entrada);
	printf("%s\n",chave);
	//printf("%s\n",criptografado);
	
	
	return 0;
}
