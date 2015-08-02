
//como compilar: gcc cifras.c -o cifras -Wall       ./cifra_cesar texto  "texto é o arquivo com dados a serem criptografados"

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


void cifra_vigenere (char chave[],FILE *arq, int opcao){//opcao 1 = cifrar 2 = decifrar
	int tam_entrada=0,aux=0,i=0;
	char lendo;
	unsigned char entrada[1000],criptografado[1000];//texto pode ter ate 1000 caracteres
	unsigned int tam_chave=0;
	FILE *arq_escrita;
	
	
	while( (lendo=fgetc(arq))!= EOF ){//le o arquivo e guarda-o em uma string
		entrada[tam_entrada]=lendo;
		tam_entrada++;//guarda o tamanho da entrada
	}
	//tam_entrada-=1;
	entrada[tam_entrada]='\0';
	
	printf("tamanho da entrada : %d\n",tam_entrada);
	while(chave[i] != '\0'){//feito para saber o tamanho da chave ja que unsigned char nao funciona strlen
		tam_chave++;
		i++;
	}
	//tam_chaveaux = tam_chave;//guarda valor original da chave
	while(tam_chave < tam_entrada){//deixando a chave no tamanho da entrada
		chave[tam_chave] = chave[aux];
		tam_chave++;
		aux++;
		//if(aux > tam_chave)
			//aux=0;
	}
	
	chave[tam_chave]='\0';
	printf("tamanho da chave : %d\n",tam_chave);
	
	printf("/nop = %d/n",opcao);
	if(opcao==1){
		for(i=0;i < tam_entrada;i++){
			
			criptografado[i] = ((entrada[i]+chave[i]+256)%256);
		}
		criptografado[i]='\0';
		
		printf("%s\n\n\n",entrada);
		printf("%s\n\n\n",chave);
		printf("%s\n\n\n",criptografado);
	
		arq_escrita = fopen("criptografado","w+");//criando arquivo onde sera colocado o texto criptografado
		if(!arq_escrita){
			printf("Impossivel abrir arquivo para salvar dados\n");
			return;
		}
	
		fprintf(arq_escrita,"%s",criptografado);
		fclose(arq_escrita);
		
	}else{
		for(i=0;i < tam_entrada;i++){
			
			criptografado[i] = ((entrada[i]-chave[i]+256)%256);
		}
		criptografado[i]='\0';
		printf("crip %s\n",criptografado);
		
		printf("%s\n\n\n",entrada);
		printf("%s\n\n\n",chave);
		printf("%s\n\n\n",criptografado);
	
		arq_escrita = fopen("text_original","w+");//criando arquivo onde sera colocado o texto criptografado
		if(!arq_escrita){
			printf("Impossivel abrir arquivo para salvar dados\n");
			return;
		}
	
		fprintf(arq_escrita,"%s",criptografado);
		fclose(arq_escrita);
	}	
}


void cifra_transposicao (int chave,FILE *arq, int opcao){
	int i=0,j=0,controle_entrada=0,cont=0,colunas=0,tam_entrada=0;
	char lendo,entrada[1000];
	FILE *arq_escrita=NULL;
	
	while( (lendo=fgetc(arq))!= EOF ){//le o arquivo e guarda-o em uma string
		entrada[tam_entrada]=lendo;
		tam_entrada++;//guarda o tamanho da entrada
	}
	tam_entrada-=1;//pq estava contando o eof
	entrada[tam_entrada]='\0';
	
	while(tam_entrada%chave!=0){//o tamanho da entrada deve ter divisao exata pela chave
		entrada[tam_entrada]='#';//simbolo escolhido para preencher 
		tam_entrada++;
		entrada[tam_entrada]='\0';//finalizando entrada
	}
	
	colunas=tam_entrada/chave;

	//char vetor[chave];
	char matriz[chave][colunas];
	
	if(opcao==1){//cifrando texto
		for(i=0;i < colunas; i++){//inserindo elementos do vetor na matriz
			/*while(cont<chave){//inserindo elementos no vetor de swap
				
				vetor[cont]=entrada[controle_entrada];
					
				cont++;
				controle_entrada++;
			}	*/
			
			for(j=0;j<chave;j++){//inserindo elementos na matriz na vertical
				//matriz[j][i]=vetor[j];
				matriz[j][i]=entrada[controle_entrada];
				printf("%c\n",matriz[j][i]);
				controle_entrada++;//adicionado
			}
			//cont=0;
		}
		
		arq_escrita = fopen("criptografado","w+");//criando arquivo onde sera colocado o texto criptografado
			if(!arq_escrita){
				printf("Impossivel abrir arquivo para salvar dados\n");
				return;
			}
			
		for(i=0;i < chave;i++){//lendo a matriz na horizontal e escrevendo no arquivo criptografado
			
			for(j=0;j < colunas;j++){
				printf("%c",matriz[i][j]);
				putc (matriz[i][j],arq_escrita);//escreve caracter no arquivo
			}
		}
		
		fclose(arq_escrita);
		
	}else{//decifrando

		for(i=0;i < chave;i++){//colocando os valores na matriz na horizontal
			
			for(j=0;j < colunas;j++){		
				matriz[i][j]=entrada[cont];
				cont++;
			}
		}
		
		arq_escrita = fopen("text_original","w+");//criando arquivo onde sera colocado o texto criptografado
		if(!arq_escrita){
			printf("Impossivel abrir arquivo para salvar dados\n");
			return;
		}
		
		for(i=0;i < colunas; i++){//lendo os valores na vertical
			for(j=0;j<chave;j++){
				
				if(matriz[j][i]=='#')
					putc (' ',arq_escrita);//escreve caracter no arquivo
				else
					putc (matriz[j][i],arq_escrita);//escreve caracter no arquivo
			}
		}
		fclose(arq_escrita);
	}
}

int main(int tam_vet, char *parametros[]){
	int op=-1,chave=-1,op2=-1;
	char chave_text[1000];
	FILE *arq=NULL; 
	
	printf("\n\n");
	printf(".----------------------------------------------------.\n");
	printf("| MENU digite o numero para executar a funcao:       |\n");
	printf("|                                                    |\n");
	printf("| 0-cifra de cesar                                   |\n");
	printf("| 1-cifra de vigenere                                |\n");
	printf("| 2-cifra de transposicao                            |\n");
	printf("| 3-cifra de substiuicao                             |\n");
	printf("| 10-Sair                                            |\n");
	printf("'----------------------------------------------------'\n");
	scanf("%d", &op);
	printf("\n\n");
	
	printf(" 1 para cifrar : 2 para decifrar \n");
	scanf("%d",&op2);
			
	switch (op){
		case 0://cifra de cesar
			
			printf("Digite a chave: ");
			scanf("%d",&chave);
			
			arq = fopen(parametros[1],"r");//abriu o arquivo passado por parametro
			if(!arq){
				printf("Impossivel abrir arquivo passado\n");
				return 0;
			}
			
			if(op2==1)
				cifra_cesar(chave,arq);
			else
				decifra_cesar(chave,arq);
				
			fclose(arq);//poderia fechar antes e abrir dentro das funcoes, ver relacao de beneficio
			
		break;
		case 1://cifra de vigenere
			printf("Digite a chave: ");
			getchar();//limpeza do buffer
			fgets(chave_text,sizeof(chave_text),stdin);//chave de ate 100 caracteres
			chave_text[strlen(chave_text)-1]='\0';//substitui /n por /0
			
			arq = fopen(parametros[1],"r");//abriu o arquivo passado por parametro
			if(!arq){
				printf("Impossivel abrir arquivo passado por parametro!\n");
				return 0;
			}

			cifra_vigenere (chave_text,arq,op2);//cifrando
		
			fclose(arq);
			
		break;
		case 2://cifra de transposicao
			printf("Digite a chave: ");
			scanf("%d",&chave);
			
			arq = fopen(parametros[1],"r");//abriu o arquivo passado por parametro
			if(!arq){
				printf("Impossivel abrir arquivo passado\n");
				return 0;
			}

			cifra_transposicao(chave,arq,op2);
				
			fclose(arq);
			
		break;
		case 3://cifra de 
		
		break;
		case 10://sair
			printf("FIM \n");
		break;
	}
	
	return 0;
}
