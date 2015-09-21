
//como compilar: gcc cifras.c -o cifras -Wall       ./cifra_cesar texto  "texto é o arquivo com dados a serem criptografados"

//T1
//cesar        	./cifras texto tabela3    ./cifras criptografado tabela3
//vigenere 		 igual cesar
//transposição	./cifras texto	./cifras criptografado		
//substituição  ./cifras texto tabela3  
 
 //T2 descobrir chave com texto claro e escuro
 
 
 
 //T3	DEscobrir a chave tendo apenas os textos escuros
 
 
//descriptografar texto, só 80%, ou menos já que existe o texto claro
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/* Tamanho máximo da string de entrada. */
#define MAX 100

typedef struct caracters{//usado na cifra de substituicao
	int comparando;
	int comparado;
}caracters;

typedef struct dicionario{//usado na leitura do dicionário
	char palavra[20];	
}dicionario;


int buscaBinaria (int x, caracters v[]) {
   int e, m, d;                              
   e = 0; d = 255;                           
   while (e <= d) {                          
      m = (e + d)/2;                         
      if (v[m].comparando == x) return m;               
      if (v[m].comparando < x) e = m + 1;               
      else d = m - 1;                        
   }                                         
   return -1;                                
}          

int hash(int chave){//mais tarde trate as colisões nessa função
	return chave/100;//aqui temos a posicao do vetor
}

//------------------------------------------------------------------------------------------------------cIFRA DE CESAR
void cifra_cesar(int chave,FILE *arq,int opcao){
	FILE *arq_escrita;
	char lendo;
	
	if(opcao==2){//decifrar
		chave*=-1;
		arq_escrita = fopen("descriptografado","w+");//criando arquivo onde sera colocado o texto criptografado
		if(!arq_escrita){
			printf("Impossivel abrir arquivo para salvar dados\n");
			return;
		}
	}else{//cifrar
		arq_escrita = fopen("criptografado","w+");//criando arquivo onde sera colocado o texto criptografado
		if(!arq_escrita){
			printf("Impossivel abrir arquivo para salvar dados\n");
			return;
		}
	}
	fseek(arq,0,SEEK_SET);
	while( (lendo=fgetc(arq))!= EOF ){//criptografando o arquivo e guardando

		lendo=(lendo+256+chave)%256;//formula de criptografia
		putc (lendo,arq_escrita);//escreve caracter no arquivo
	}
	
	fclose(arq_escrita);
}

void decifra_cesar_escuro(char *t_claro, char *t_escuro){
	
	FILE *escuro=NULL,*claro=NULL;
	int lendo=0,lendo2=0,escreve=0;
	
	escuro = fopen(t_escuro,"r");//abriu o arquivo passado por parametro
	if(!escuro){
		printf("Impossivel abrir arquivo texto escuro\n");
		return;
	}
	
	claro = fopen(t_claro,"r");//abriu o arquivo passado por parametro
	if(!claro){
		printf("Impossivel abrir arquivo texto claro\n");
		return;
	}
	
	fseek(escuro,0,SEEK_SET);//posiciona a agulha no comeco do arquivo
	fseek(claro,0,SEEK_SET);//posiciona a agulha no COMECO do arquivo
	
	lendo=fgetc(escuro); //le o arquivo escuro e claro
	lendo2=fgetc(claro);
	escreve=lendo-lendo2;//diminui o claro do escuro e teremos a chave
	
	printf("chave = %d\n",escreve);
	fclose(claro);
	fclose(escuro);
}

void decifra_cesar_escuro_escuro(char *t_escuro,dicionario diciona[]){//decifra texto sem o texto claro
	FILE *escuro=NULL,*descripto=NULL;
	int chave=1,encontrou=0;
	char lendo, *palavra=NULL;
	long cont=0,buffer=0;
	
	escuro = fopen(t_escuro,"r");//abriu o arquivo passado por parametro
	if(!escuro){
		printf("Impossivel abrir arquivo texto escuro\n");
		return;
	}
	
	descripto = fopen("descriptografado","w+");//o arquivo deve existir previamente
		if(!descripto){
			printf("Impossivel abrir arquivo descriptografado\n");
			return;
		}
	
	//alocação dinâmica para leitura do arquivo decifrado. Quando decifrado com senha errada não se sabe o que vem do arquivo
	palavra = malloc (sizeof (char)*10485760);//10 mb
	if(palavra == NULL){
		printf("Impossível alocar 10 mb!\n");
		return;
	}
	
	while(chave<256){	

		fseek(escuro,0,SEEK_SET);//posiciona a agulha no comeco do arquivo
		cifra_cesar(chave,escuro,2);//decifrando arquivo

		cont=0;
		fseek(descripto,0,SEEK_SET);//posiciona a agulha no comeco do arquivo
		while( (lendo=fgetc(descripto))!= EOF ){//deve ler todas as palavras do arquivo descriptografado
		//somar as letras da palavar até o espaço em branco e com a soma fazer hash. if palavra na posicao hash é igual a do texto blz
			//printf("%c",lendo);
			
			if(lendo==' '){//talvez funcone apenas quando o texto decifrado esteja correto
				
				buffer = hash(buffer);//fazendo has das letras da palavra
				if(buffer<12)//posi o dicionario n possui mais que 10 palavras
					if(strcmp(diciona[buffer].palavra,palavra)==0){
						encontrou++;
						if(encontrou>10){
							printf("chave: %d\n",chave);
							return;
						}
					}
				
				buffer=0;
				cont=0;
			}else{//nao e o espaco e nem o eof
				palavra[cont]=lendo;
				palavra[cont+1]='\0';
				//printf("%s",palavra);
				buffer+=lendo;
				cont++;
			}
		}
		chave++;
		buffer=0;
		cont=0;
	}
	
	free(palavra);
	fclose(descripto);
	fclose(escuro);
}


//-------------------------------------------------------------------------------------------------------------------Vigenere
void cifra_vigenere (char chave[],FILE *arq, int opcao){//opcao 1 = cifrar 2 = decifrar
	long int tam_entrada=0,aux=0,i=0;
	char lendo='a';
	char *entrada,*criptografado;//texto pode ter ate 1000 caracteres
	unsigned long int tam_chave=0;
	FILE *arq_escrita;
	

		printf("\nchave %s\n",chave);

	
	//alocação dinamica 
	criptografado = malloc (sizeof (char)*10485760);//10 mb
	if(criptografado == NULL){
		printf("Impossível alocar 10 mb!\n");
		return;
	}
	
	//alocação dinamica 
	entrada = malloc (sizeof (char)*10485760);//10 mb
	if(entrada == NULL){
		printf("Impossível alocar 10 mb!\n");
		return;
	}
	fseek(arq,0,SEEK_SET);
	while( (lendo=fgetc(arq))!= EOF ){//le o arquivo e guarda-o em uma string
		entrada[tam_entrada]=lendo;//string que guarda a entrada
		tam_entrada++;//guarda o tamanho da entrada
	}
	printf("TAMNHO DA ENTRADA %ld",tam_entrada);
	//printf("ENTRADA %s\n",entrada);
	
	entrada[tam_entrada]='\0';
	
	while(chave[i] != '\0'){//feito para saber o tamanho da chave ja que unsigned char nao funciona strlen
		tam_chave++;
		i++;
	}
	printf("TAMNHO DA chave %ld",tam_chave);
	while(tam_chave < tam_entrada){//deixando a chave no tamanho da entrada
		chave[tam_chave] = chave[aux];
		tam_chave++;
		aux++;
	}
	printf("TAMNHO DA chave %ld\n",tam_chave);
	//printf("chave %s\n",chave);
	chave[tam_chave]='\0';
	
	if(opcao==1){//criptografa
		for(i=0;i < tam_entrada;i++){
			
			//printf("\nchave %d\n",chave[i]);
			//printf("\nentrada %d\n",entrada[i]);
			criptografado[i] = ((entrada[i]+chave[i]+256)%256);
			//printf("criptografado %d\n",criptografado[i]);
		}
		criptografado[i]='\0';
	
		arq_escrita = fopen("criptografado","w+");//criando arquivo onde sera colocado o texto criptografado
		if(!arq_escrita){
			printf("Impossivel abrir arquivo para salvar dados\n");
			return;
		}
		
		fprintf(arq_escrita,"%s",criptografado);//escreve no arquivo
		fclose(arq_escrita);
		
	}else{//descriptografa
		
		for(i=0;i < tam_entrada;i++){
			
			//printf("\nchave %d\n",chave[i]);
			//printf("\nchave %d\n",entrada[i]);
			
			criptografado[i] = ((entrada[i]-chave[i]+256)%256);
			//printf("criptografado %c\n",criptografado[i]);
		}
		criptografado[i]='\0';
	
		arq_escrita = fopen("descriptografado","w+");//criando arquivo onde sera colocado o texto descriptografado
		if(!arq_escrita){
			printf("Impossivel abrir arquivo para salvar dados\n");
			return;
		}
		//printf("%s\n",criptografado);
		
		fprintf(arq_escrita,"%s",criptografado);
		fclose(arq_escrita);
	}	
	
	free(entrada);
	free(criptografado);
}

void decifra_vigenere_escuro(char *t_claro, char *t_escuro){//mostra a chave replicada
	FILE *escuro=NULL,*claro=NULL;
	
	int c=0;
	int lendo=0,lendo2=0;
	
	escuro = fopen(t_escuro,"r");//abriu o arquivo passado por parametro
	if(!escuro){
		printf("Impossivel abrir arquivo texto escuro\n");
		return;
	}
	
	claro = fopen(t_claro,"r");//abriu o arquivo passado por parametro
	if(!claro){
		printf("Impossivel abrir arquivo texto claro\n");
		return;
	}
	
	//fseek(claro,0,SEEK_END);//posiciona a agulha no final do arquivo
	//tamanho=ftell(claro);//pega o tamanho do arquivo
	
	//char buffer[tamanho];
	
	fseek(claro,0,SEEK_SET);
	while( (lendo=fgetc(escuro))!= EOF ){//lendo o arquivo escuro
		lendo2=fgetc(claro);//LEITURA DO CLARO
		lendo = lendo-lendo2;
		printf("%c",lendo);
		c++;
	}
	printf("\n");
	fclose(claro);
	fclose(escuro);
}

char * decifrando(char chave[],FILE *descripto,FILE *escuro,dicionario diciona[]){//verificando se a chave permutada esta certa
	char lendo,*palavra=NULL;
	long cont=0,buffer=0;
	int encontrou=0;	
	
	palavra = malloc (sizeof (char)*10485760);//10 mb
	if(palavra == NULL){
		printf("Impossível alocar 10 mb!\n");
		return NULL;
	}
	
	//fseek(escuro,0,SEEK_SET);//posiciona a agulha no comeco do arquivo
	cifra_vigenere(chave,escuro,2);//descriptografo o texto
	
	cont=0;
	fseek(descripto,0,SEEK_SET);//posiciona a agulha no comeco do arquivo
	while( (lendo=fgetc(descripto))!= EOF ){//deve ler todas as palavras do arquivo descriptografado
	//somar as letras da palavar até o espaço em branco e com a soma fazer hash. if palavra na posicao hash é igual a do texto blz
		//printf("%c",lendo);
		
		if(lendo==' '){//talvez funcone apenas quando o texto decifrado esteja correto
			
			buffer = hash(buffer);//fazendo has das letras da palavra
		
			if(buffer<12){//posi o dicionario n possui mais que 10 palavras
				
				if(strcmp(diciona[buffer].palavra,palavra)==0){
					//printf("palavra %s\n",palavra);
					//printf("dicionario %s\n",diciona[buffer].palavra);
					encontrou++;
					printf("\nENCONTROU %d\n",encontrou);
					if(encontrou>100){
						//printf("chave: %s\n",chave);
						return chave;
					}
				}
			}
			
			buffer=0;
			cont=0;
		}else{//nao e o espaco e nem o eof
			palavra[cont]=lendo;
			palavra[cont+1]='\0';
			//printf("formando palavra %s\n",palavra);
			buffer+=lendo;
			cont++;
		}
	}

	free(palavra);
	return NULL;
}

char * permuta(char *t_escuro,dicionario diciona[]){
	int cont=0;
	char *chave_text=NULL,*retorno=NULL;
	
	
	chave_text = malloc (sizeof (char)*10485769);//+10 mb para chave de vegenere
	if(chave_text == NULL){
		printf("Impossível alocar 10 mb para a chave!\n");
		return NULL;
	}
	
	
    /* Nosso número na base n. Ele é um vetor
     * de n+1 posições representando um número
     * na base n.
     */
    int *num ;
    /* input é a string de entrada, e str
     * receberá cada permutação.
     */ 
    char input[MAX], str[MAX] ;
    int n, r, i, j, k ;

    printf("Entre com o conjunto inicial: ") ;
    scanf("%s", input) ;

    printf("Entre com o r: ") ;
    scanf("%d", &r) ;

	FILE *descripto=NULL;
	FILE *escuro=NULL;
	
	descripto = fopen("descriptografado","r");//abriu o arquivo onde o texto sera descriptografado
	if(!descripto){
		printf("Impossivel abrir arquivo texto descriptografado \n");
		return NULL;
	}
	
	escuro = fopen(t_escuro,"r");//abriu o arquivo passado por parametro
	if(!escuro){
		printf("Impossivel abrir arquivo texto escuro\n");
		return NULL;
	}
	
    /* Aqui elimina-se caracteres repetidos na entrada.
     * Esse procedimento não faz parte do algoritmo, e
     * só é feito por questões práticas.
     */
    n = strlen(input) ;
    j = 0;
    str[0] = 0 ;
    for ( i = 0; i < n; i++ ) {
        if ( strchr(str, input[i]) == NULL ) {
            str[j] = input[i] ;
            j++ ;
            str[j] = 0 ;
        }
    }
    strcpy(input, str) ;
    n = strlen(input) ;

    /* Cria o nosso número. Ele é um vetor de
     * r+1 posições, sendo que a última é 
     * reservada para indicar quando todos os
     * números de tamanho r foram gerados. */
    num = (int *) calloc( (r+1), sizeof(int)) ;
    if ( num == NULL ) {
        perror("calloc") ;
        return NULL;
    }

    /* Termina quando a última posição do vetor
     * for 1. */
    while ( num[r] == 0 ) {
        for ( i = 0; i < n; i++ ) {
            /* processo de mapeamento. */
            for ( j = 0, k = r-1; j < r; j++ ) {
                str[k] = input[num[j]] ;
                k-- ;
            }
            str[r] = 0 ;
            printf("\nstr %s\n",str);
			strcpy(chave_text,str);
			printf("chave antes de mandar %s",chave_text);
			chave_text[strlen(chave_text)]='\0';
            retorno=decifrando (chave_text,descripto,escuro,diciona);//manda a chave e o arquivo onde sera descriptografado o texto
            printf("retorno %p\n",retorno);
            if(retorno!=NULL)
				return chave_text;
            cont++;
            
            /* incrementa o algarismo menos significativo. */
            num[0]++ ;
        }

        /* Muda de "casa" e lança os vai uns. */ 
        for ( i = 0; i < r; i++ ) {
            if ( num[i] == n ) {
                num[i] = 0 ;
                num[i+1]++ ;
            }
        }
    }
    
	fclose(descripto);
	fclose(escuro);
    return NULL ;
}

void decifra_vigenere_escuro_escuro(char *t_escuro,dicionario diciona[]){
	char *chave2=NULL;
	int a=0;

	chave2 = permuta(t_escuro,diciona);
	
	if(chave2 == NULL)
		printf("chave nao encontrada\n");
	else{
		while(a<20){
			printf("%c",chave2[a]);
			a++;
		}
		printf("\n");
	}
}


//----------------------------------------------------------------------------------------------------------cifra de transposição
void cifra_transposicao (int chave,FILE *arq, int opcao){
	int i=0,j=0,controle_entrada=0,cont=0,colunas=0,tam_entrada=0;
	char lendo,*entrada=NULL;
	FILE *arq_escrita=NULL;
	
	//alocação dinamica 
	entrada = malloc (sizeof (char)*10485760);//10 mb
	if(entrada == NULL){
		printf("Impossível alocar 10 mb!\n");
		return;
	}
	
	fseek(arq,0,SEEK_SET);//adicionado para posicionar o cabe;ote de leitura sempre no comeco do arquivo
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

	char matriz[chave][colunas];
	
	if(opcao==1){//cifrando texto
		for(i=0;i < colunas; i++){//inserindo elementos do vetor na matriz
			
			for(j=0;j<chave;j++){//inserindo elementos na matriz na vertical
				matriz[j][i]=entrada[controle_entrada];
				controle_entrada++;//adicionado
			}
		}
		
		arq_escrita = fopen("criptografado","w+");//criando arquivo onde sera colocado o texto criptografado
			if(!arq_escrita){
				printf("Impossivel abrir arquivo para salvar dados\n");
				return;
			}
			
		for(i=0;i < chave;i++){//lendo a matriz na horizontal e escrevendo no arquivo criptografado
			
			for(j=0;j < colunas;j++){
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
		
		arq_escrita = fopen("descriptografado","w+");//criando arquivo onde sera colocado o texto dcriptografado
		if(!arq_escrita){
			printf("Impossivel abrir arquivo para salvar dados\n");
			return;
		}
		
		for(i=0;i < colunas; i++){//lendo os valores na vertical
			for(j=0;j<chave;j++){
				
				if(matriz[j][i]=='#')//retirando o #
					putc ('\0',arq_escrita);//escreve caracter no arquivo
					//putc (' ',arq_escrita);//funcionava para o trabalho 1
				else
					putc (matriz[j][i],arq_escrita);//escreve caracter no arquivo
			}
		}
		fclose(arq_escrita);
	}
	free(entrada);
}

void decifra_transposicao_escuro(char *t_claro, char *t_escuro){
	
	int chave=1,tamanho=0;
	FILE *escuro=NULL,*claro=NULL,*descriptografado=NULL;
	char text_claro[200],text_descrip[200];
	
	escuro = fopen(t_escuro,"r");//abriu o arquivo passado por parametro
	if(!escuro){
		printf("Impossivel abrir arquivo texto escuro\n");
		return;
	}
	
	claro = fopen(t_claro,"r");//abriu o arquivo passado por parametro
	if(!claro){
		printf("Impossivel abrir arquivo texto claro\n");
		return;
	}
	
	
	fgets(text_claro, sizeof(text_claro), claro);//le até 200 caracters do texto

	while(tamanho<=strlen(text_claro)){
		if(text_claro[tamanho] == '\n'){
			text_claro[tamanho] = '\0';
			break;
		}
		tamanho++;
		
	}
	while (chave<256) {
	
		cifra_transposicao(chave,escuro,2);//decifrando arquivo
		//comparando com o texto  claro
		
		descriptografado = fopen("descriptografado","r");//abriu o arquivo passado decifrado
		if(!descriptografado){
			printf("Impossivel abrir arquivo texto descriptografado\n");
			return;
		}
		
		tamanho=0;
		fseek(descriptografado,0,SEEK_SET);
		fgets(text_descrip, sizeof(text_descrip), descriptografado);//le até 200 caracters do descripto
		
		while(tamanho <= strlen(text_descrip)){
			
			if(text_descrip[tamanho] == '\n'){
				text_descrip[tamanho] = '\0';
				break;
			}
			tamanho++;	
		}
		
		if(strcmp(text_descrip,text_claro)==0){//compara com parte do texto
			printf("Texto compativel com chave = %d\n",chave);
			break;
		}
		fclose(descriptografado);
		chave++;
	}
	
	fclose(claro);
	fclose(escuro);
	
}
void decifra_transposicao_escuro_escuro(char *t_escuro,dicionario diciona[]){
	
	
}
//-------------------------------------------------------------------------------------------------------------------substituicao
void cifra_substituicao(FILE *arq,char *tabela_char,int opcao){//recebe dois arquivos ja abertos
	char lendo,pontos;
	int i=0,aux=0,procura;
	FILE *arq_escrita=NULL,*tabela=NULL;
	caracters vetor[256];
	
	if(opcao==1){//cifra
		arq_escrita = fopen("criptografado","w+");//criando arquivo onde sera colocado o texto criptografado
		if(!arq_escrita){
			printf("Impossivel abrir arquivo para salvar dados\n");
			return;
		}
	}else{//decifra, opcao==2
		arq_escrita = fopen("descriptografado","w+");//criando arquivo onde sera colocado o texto criptografado
		if(!arq_escrita){
			printf("Impossivel abrir arquivo para salvar dados\n");
		return;
		}	
	}
	
	tabela = fopen(tabela_char,"r");//abrir a tabela de caracters
		if(!tabela){
			printf("Impossivel abrir arquivo com a tabela de caracters\n");
		return;
		}		
		
	while( (fscanf(tabela,"%d%c%d\n", &vetor[i].comparando, &pontos, &vetor[i].comparado))!=EOF )//lendo a tabela de substituicao e guardando
		i++;
		
	while( (lendo=fgetc(arq))!= EOF ){//le o arquivo de entrada um caracter por vez

		if(lendo<0){//para leitura negatica de caracterres
			procura=256+lendo;
			aux = buscaBinaria(procura,vetor);
		}else
			aux = buscaBinaria(lendo,vetor);//procura pelo caracter a ser substituido
		
		if(opcao==1){
			//printf("lendo %c\n",lendo);
			fputc(vetor[aux].comparado,arq_escrita);
			
		}else{
			
			fputc(vetor[aux].comparado,arq_escrita);
			
		}	
	}
		
	fclose(tabela);
	fclose(arq_escrita);
}

void decifra_substituicao_escuro(char *t_claro, char *t_escuro){
	int lendo=0,lendo2=0,i=0;
	caracters vetor[256];
	FILE *escuro=NULL,*claro=NULL;
	
	escuro = fopen(t_escuro,"r");//abriu o arquivo passado por parametro
	if(!escuro){
		printf("Impossivel abrir arquivo texto escuro\n");
		return;
	}
	
	claro = fopen(t_claro,"r");//abriu o arquivo passado por parametro
	if(!claro){
		printf("Impossivel abrir arquivo texto claro\n");
		return;
	}
	
	while(i<256){//inicializando o vetor de caracters
		vetor[i].comparando=0;
		vetor[i].comparado=0;
		i++;
	}
	
	while( (lendo=fgetc(claro))!= EOF ){//lendo texto claro
		lendo2=fgetc(escuro);//le do texto claro e escuro e escreve a chave mostrando em int qual foi a transformacao do valor
		vetor[lendo].comparando=lendo;
		vetor[lendo].comparado=lendo2;
		
		vetor[lendo2].comparando=lendo2;
		vetor[lendo2].comparado=lendo;
	}
	
	i=0;
	while(i<256){
		printf("%d : %d\n",vetor[i].comparando, vetor[i].comparado);
		i++;
	}
	fclose(claro);
	fclose(escuro);
}


//----------------------------------------------------------------------------------------------------------------------------------------------MAIN()
int main(int tam_vet, char *parametros[]){
	int op=-1,chave=-1,op2=-1,cont=0;
	char *chave_text,lendo[20];
	FILE *arq=NULL; 
	dicionario buffer[11]; //so tem 10 palavras
	
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
	
	printf(" 1 para cifrar um texto : 2 para decifrar um texto : 3 para decifrar texto escuro (sem a chave): 4 para decifrar texto escuro com dicionario (sem a chave):\n");
	scanf("%d",&op2);
			
	switch (op){
		case 0://cifra de cesar
			
			if(op2==3){
				decifra_cesar_escuro(parametros[1],parametros[2]);//dados dois textos, claro e escuro encontrar a chave
				break;
			}
			
			if(op2==4){
				arq = fopen(parametros[2],"r");//abrindo dicionario e guardando em vetor
				if(!arq){
					printf("Impossivel abrir arquivo passado\n");
					return 0;
				}
				//le o dicionario e coloca no vetor de palavras
				while( (fscanf(arq,"%s ", lendo))!=EOF )
					strcpy(buffer[cont++].palavra,lendo);

				//VERIFICAR PARAMETROS
				decifra_cesar_escuro_escuro(parametros[1],buffer);				
				
				fclose(arq);
				break;
			}
			
				
			printf("Digite a chave: ");
			scanf("%d",&chave);
			
			arq = fopen(parametros[1],"r");//abriu o arquivo passado por parametro
			if(!arq){
				printf("Impossivel abrir arquivo passado\n");
				return 0;
			}
			
			cifra_cesar(chave,arq,op2);
		
			fclose(arq);//poderia fechar antes e abrir dentro das funcoes, ver relacao de beneficio
			
		break;
		case 1://cifra de vigenere
		
			chave_text = malloc (sizeof (char)*10485769);//+10 mb quando usa vegenere
			if(chave_text == NULL){
				printf("Impossível alocar 10 mb para a chave!\n");
				return 1;
			}
			
			if(op2==3){
				decifra_vigenere_escuro(parametros[1],parametros[2]);//passa texto claro e texto escuro, dados dois textos, claro e escuro encontrar a chave
				break;
			}
		
			if(op2==4){//escuro escuro com dicionário de palavars
				arq = fopen(parametros[2],"r");//abrindo dicionario e uardando em vetor
				if(!arq){
					printf("Impossivel abrir arquivo passado\n");
					return 0;
				}
				//le o dicionario e coloca no vetor de palavras
				while( (fscanf(arq,"%s ", lendo))!=EOF )
					strcpy(buffer[cont++].palavra,lendo);

				//VERIFICAR PARAMETROS
				decifra_vigenere_escuro_escuro(parametros[1],buffer);				
				
				fclose(arq);
				break;
			}
			
			printf("%d\n",strlen(chave_text));
			printf("Digite um texto como chave: ");
			getchar();//limpeza do buffer
			fgets(chave_text,sizeof(10485769),stdin);
			printf("%d\n",strlen(chave_text));
			//chave_text[strlen(chave_text)]='\0';//substitui /n por /0
			printf("chave antes de mandar main: %s\n",chave_text);
			
			arq = fopen(parametros[1],"r");//abriu o arquivo passado por parametro
			if(!arq){
				printf("Impossivel abrir arquivo passado por parametro!\n");
				return 0;
			}

			cifra_vigenere (chave_text,arq,op2);//cifrando
		
			//free(chave_text);
			fclose(arq);
			
			
		break;
		case 2://cifra de transposicao
			
			if(op2==3){
				decifra_transposicao_escuro(parametros[1],parametros[2]);//dados dois textos, claro e escuro encontrar a chave
				break;
			}
			
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
		case 3://cifra de substituicao
		
			if(op2==3){
				decifra_substituicao_escuro(parametros[1],parametros[2]);//dados dois textos, claro e escuro encontrar a chave
				break;
			}
		
			arq = fopen(parametros[1],"r");//abriu o arquivo passado por parametro
			if(!arq){
				printf("Impossivel abrir arquivo passado\n");
				return 0;
			}
			
			cifra_substituicao(arq,parametros[2],op2);//manda arquivos ja abertos
			
			fclose(arq);
		
		break;
		case 10://sair
			printf("FIM \n");
		break;
	}
	
	free(chave_text);
	return 0;
}
