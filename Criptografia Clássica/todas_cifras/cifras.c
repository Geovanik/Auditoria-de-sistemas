
//como compilar: gcc cifra_cesar.c -o cifra_cesar -Wall       ./cifra_cesar < texto > criptografado  "texto é o arquivo com dados a serem criptografados"

//OBS: SE NÃO TRABALHAR COM UNSIGNED CHAR OS VALORES FICAM NEGATIVOS, É POSSÍVEL IMPRIMIR CARACTERES NEGATIVOS???
// e quando a entrada for menor que a chave????
 
#include <stdio.h>
#include <string.h>
#include <stdlib.h>


void cifra_cesar(int chave,FILE *arq){
	FILE *arq_escrita;
	char lendo;
	
	arq_escrita = fopen("criptografado","w+");//criando arquivo onde sera colocado o texto criptografado
	if(!arq_escrita){
		printf("Impossivel abrir arquivo para salvar dados\n");
		return;
	}
	
	while( (lendo=fgetc(arq))!= EOF ){//criptografando o arquivo e guardando

		lendo=(lendo+256+chave)%256;//formula de criptografia
		putc (lendo,arq_escrita);//escreve caracter no arquivo
	}
	
	fclose(arq_escrita);
}

void decifra_cesar(int chave,FILE *arq){
	char lendo;
	FILE *arq_escrita;
	
	arq_escrita = fopen("text_original","w+");//criando arquivo onde sera colocado o texto criptografado
	if(!arq_escrita){
		printf("Impossivel abrir arquivo para salvar dados\n");
		return;
	}
	
	while( (lendo=fgetc(arq))!= EOF ){

		lendo=(lendo+256-chave)%256;//formula de criptografia
		putc (lendo,arq_escrita);//escreve caracter no arquivo
	}
	fclose(arq_escrita);
}


void cifra_vigenere (char chave[],FILE *arq){
	int tam_entrada=0,aux=0,i=0;
	char lendo;
	unsigned char entrada[1000],criptografado[1000];
	unsigned int tam_chave=0;
	
	while(scanf("%c",&lendo)!=EOF){//le o arquivo vindo por montagem de arquivo na compilação
		entrada[tam_entrada]=lendo;
		tam_entrada++;
	}
	entrada[tam_entrada-1]='\0';
	
	
	
	//printf("\ntamanho %d %d\n",tam_entrada,tam_chave);
	
	//strlen nao funciona para unsigned char
	while(chave[i] != '\0'){
		tam_chave++;
		i++;
	}
	
	while(tam_chave < (tam_entrada-1)){//deixando a chave no tamanho da entrada
		chave[tam_chave] = chave[aux];
		tam_chave++;
		aux++;
		if(aux > tam_chave)
			aux=0;
	}
	
	for(i=0;i < tam_entrada;i++){
		
		criptografado[i] = ((entrada[i]+chave[i]+256)%256);
		/*printf("entrada na posicao i: %d\n",entrada[i]);
		printf("chave na posicao i: %d\n",chave[i]);
		printf("criptografado na posicao i: %d\n",criptografado[i]);
		printf("%c\n",criptografado[i]);*/
	}

	criptografado[i]='\0';

	printf("%s\n",entrada);
	//printf("%s\n",chave);
	printf("%s\n",criptografado);
}

int main(int tam_vet, char *parametros[]){
	int op=-1,chave=-1;
	char chave_text[1000];
	FILE *arq=NULL; 
	
	printf("\n\n");
	printf(".----------------------------------------------------.\n");
	printf("| MENU digite o numero para executar a funcao:       |\n");
	printf("|                                                    |\n");
	printf("| 0-cifra de cesar                                   |\n");
	printf("| 1-cifra de transposicao                            |\n");
	printf("| 2-cifra de vigenere                                |\n");
	printf("| 3-cifra de substiuicao                             |\n");
	printf("| 10-Sair                                            |\n");
	printf("'----------------------------------------------------'\n");
	scanf("%d", &op);
	printf("\n\n");
	
	arq = fopen(parametros[1],"r");
	if(!arq){
		printf("Impossivel abrir arquivo passado\n");
		return 0;
	}
	
	switch (op){
		case 0://cifra de cesar
			printf(" 1 para cifrar : 2 para decifrar \n");
			scanf("%d",&op);
			
			printf("Digite a chave: ");
			scanf("%d",&chave);
			
			if(op==1)
				cifra_cesar(chave,arq);
			else
				decifra_cesar(chave,arq);
				
			fclose(arq);
		break;
		case 1://cifra de 
			printf("Digite a chave: ");
			//guardar chave
			
			//coloque /0 na chave
			
			cifra_vigenere (chave_text,arq);
		break;
		case 2://cifra de 
		
		break;
		case 3://cifra de 
		
		break;
		case 10://sair
			printf("FIM \n");
		break;
	}
	
	return 0;
}
