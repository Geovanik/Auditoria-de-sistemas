/*definições
 a entrada é um vetor de 10 posições, cada posição com 10⁸ valores
 int de 32 bits
 
 * //entrada em arquivo
 * //vetor de resultado de 1024 bits, 37 posicoes em que cada uma suporta 8 digitos
 * int 10 digitos
 * */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX 1123456789 

int retira_overflow(int valor){
	int aux=0,cont=8,aux2=0;
	
	while(cont>0){
		aux=valor%10;
		cont--;
		valor=valor/10;
		printf("valor = %d\n",valor);
		aux2=aux2+aux;
	}
	printf("AUX2 = %d\n",aux2);
	return aux2;
}



int overflow(int valor){//verificando se existe overflow em valor de 8 digitos
	int aux=0;
	aux=valor/10000000;//verificando se existe overflow
	if(aux>9)//retorna os 2 primeiros digito do valor
		return aux;
	else
		return 0;//nao tem overflow
}	


void multiplicacao(int entrada1[], int entrada2[], int resultado[]){
	int cont=19,cont2=36;//tamanho das entradas e resultado
	while(cont>=0){
		resultado[cont2]=entrada1[cont]*entrada2[cont];
		cont--;
		cont2--;
	}
}

void soma(int entrada1[], int entrada2[], int resultado[]){
	int cont=19,cont2=36,over=0;//tamanho das entradas e resultado
	while(cont>=0){
		resultado[cont2]=entrada1[cont]+entrada2[cont]+over;
		over = overflow(resultado[cont2]);
		if(over>0){
			printf("IDENTIFICADO %d\n",over);
			over=over/10;//real overflow
			retira_overflow(resultado[cont2]);//quebra o valor resultado retirando o digito da frente
		}
		cont--;
		cont2--;
	}
	//conta os digitos do resultado, se der mais que 8 coloca na posicao anterior
}

void exponenciacao(){
	
	
	
}

void inverso_modular(){
	
	
	
}
void inicializa_vetores(int tamanho, int vetor[]){
	int a=0;
	while(a<tamanho)//inicializa vetror de swap2
		vetor[a++]=0;
}

void uniao_valores(int swap2[],int entrada[],int posicao){
	int valor=0;
	
	valor=swap2[7];
	valor=(swap2[6]*10)+valor;
	valor=(swap2[5]*100)+valor;
	valor=(swap2[4]*1000)+valor;
	valor=(swap2[3]*10000)+valor;
	valor=(swap2[2]*100000)+valor;
	valor=(swap2[1]*1000000)+valor;
	valor=(swap2[0]*10000000)+valor;
	
	entrada[posicao]=valor;
	
	inicializa_vetores(8,swap2);
}

void quebra_valores(long long int swap[],int entrada[],int t){//quebra os valores da entrada colocando eles na entrada
	int swap2[8],cont=7,posicao=9;
	long long int valor=0;
	
	inicializa_vetores(8,swap2);
		
	valor=swap[--t];
	while (t>-1){//controla a quantidade de numeros dentro do vetor de swap

		swap2[cont--]=(valor%10);//colocando os digitos no vetor de swap/
		if(cont==-1){//colocando os valores na entrada
			uniao_valores(swap2,entrada,posicao);
			posicao--;
			cont=7;
		}	
		valor/=10;
		if(valor==0)
			valor=swap[--t];
	}
	if(swap2[7]!=0)//para valores menores que 8 bits, valores mais significativos
		uniao_valores(swap2,entrada,posicao);
}

void valores_menores(char swap[],int contador, int cont_entrada, int entrada[]){//coloca na entrada valores que possuem menos de 8 digitos
	int cont=0;
	char *aux=NULL;
	
	aux = (char*)malloc((8-contador)*sizeof(char));//alocando vetor exato de quantidade de digitos
	
	while(contador<8){
		aux[cont]=swap[contador];
		printf("%d",aux[contador]);
		contador++;	
		cont++;
	}
	entrada[cont_entrada]=atoi(aux);
	printf("\nmenor %d\n",entrada[cont_entrada]);
}

int main(int argc,char**argv){
	int entrada1[20],entrada2[20],resultado[39],cont=0,contador=8,posicao=10,cont_entrada=19,flag=1,operacao=0;
	//resultado em que cada posicao tem ate 8 digitos
	//os valores de entrada podem ser do max do tamanho 8*20
	//flag 1 indica entrada2 0 a entrada1
	
	char lendo='a',swap[10];
	FILE *pt_file=NULL;
	
	inicializa_vetores(20,entrada1);
	inicializa_vetores(20,entrada2);
	inicializa_vetores(39,resultado);
	
	pt_file = fopen(argv[1], "r");
	if(!pt_file){
		printf("Impossivel abrir arquivo passado\n");
		return 0;
	}
	fseek(pt_file, -2, SEEK_END);//posiciona o pont no final do arq no ultimo digito do numero
	cont=-2;
	//recebendo a entrada com espaço em branco no começo do arq, preenchendo o vetor de swap
	//LER DE 8 EM 8 E COLOCAR EM UMA POSICAO DA ENTRADA
	swap[contador--]='\0';//delimitando swap para 8 digitos
	while(posicao>0){													
		
		lendo = fgetc(pt_file);
		
		if(lendo=='\n'){//muda o  vetor de entradas, reinicializa variaveis
			if(contador!=-1)
				valores_menores(swap,(contador+1),cont_entrada,entrada2);//contador decrementou uma vez a mais
			
			flag=0;
			cont_entrada=19;
			contador=8;
			swap[contador--]='\0';//delimitando swap para 8 digitos
		}
			
		cont--;
		fseek(pt_file, cont, SEEK_END);
		posicao=ftell(pt_file);	
		
		swap[contador]=lendo;
		contador--;
		
		if(lendo=='\n')//para que na proxima leitura o \n seja subscrito
			contador++;
		
		if(contador==-1){//8 dígitos foram lidos
			if(flag)
				entrada2[cont_entrada]=atoi(swap);
			else
				entrada1[cont_entrada]=atoi(swap);
			
			cont_entrada--;
			contador=8;
			swap[contador--]='\0';
		}
	}

	if(contador!=-1)//verificando se n existe valores com menos de 8 digitos na entrada1
		valores_menores(swap,(contador+1),cont_entrada,entrada1);
		
	fclose(pt_file);
	printf("\nqual e a operacao? 1 - soma\t 2 - subtracao\t 3 - multiplicacao\t 4 - divisao\t 5 - exponencicao\n");
	scanf("%d",&operacao);
	if(operacao==1)
		soma(entrada1,entrada2,resultado);
	else if(operacao==2)
		multiplicacao(entrada1,entrada2,resultado);//fazer uma generica
	
	else 
		inverso_modular();
	
	int h=0;
	while(h<20){
		printf("%d ",h);
		printf("entrada1 %d\n",entrada1[h++]);
	}
	
	h=0;
	while(h<20){
		printf("%d ",h);
		printf("entrada2 %d\n",entrada2[h++]);
	}
	
	h=0;
	while(h<37){
		printf("%d ",h);
		printf("resultado %d\n",resultado[h++]);
	}
	return 0;
}
