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

void multiplicacao(int entrada1[], int entrada2[], int resultado[]){
	int cont=9;
	while(cont>=0){
		resultado[cont]=entrada1[cont]*entrada2[cont];
		cont--;
	}
}

void soma(int entrada1[], int entrada2[], int resultado[]){
	int cont=9;
	while(cont>=0){
		resultado[cont]=entrada1[cont]+entrada2[cont];
		cont--;
	}
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
int main(int argc,char**argv){
	int entrada1[20],entrada2[20],resultado[39],cont=0,contador=8,posicao=10,cont_entrada=19,flag=1;
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
	//recebendo a entrada preenchendo o vetor de swap
	//LER DE 8 EM 8 E COLOCAR EM UMA POSICAO DA ENTRADA
	swap[contador--]='\0';//delimitando swap para 8 digitos
	while(posicao>0){													//le o arquivo até encontrar o : e guarda a posição
		
		if(lendo=='\n'){//muda o  vetor de entradas, reinicializa variaveis
			if(contador!=-1)
				printf("diferente");
			flag=0;
			cont_entrada=19;
			contador=8;
			swap[contador--]='\0';//delimitando swap para 8 digitos
		}
			
		lendo = fgetc(pt_file);
		cont--;
		fseek(pt_file, cont, SEEK_END);
		posicao=ftell(pt_file);
		
		swap[contador]=lendo;
		contador--;
		
		if(contador==-1){//8 dígitos foram lidos
			if(flag)
				entrada2[cont_entrada]=atoi(swap);
			else
				entrada1[cont_entrada]=atoi(swap);
			
			//printf("entra %d\n",entrada1[cont_entrada]);
			cont_entrada--;
			
			contador=8;
			swap[contador--]='\0';
		
		}
	}
	/*int h=0;
	while(h<17){
		printf("%d ",h);
		printf("entrada1 %d\n",entrada1[h++]);
	}*/
	/*while(controle==1){
		scanf("%lld",&valor);
		swap[t++]=valor;
		
		printf("Deseja continuar digitando um mesmo numero?\n 1 - sim\n 0 - nao\n");
		scanf("%d",&controle);
	}*/
	/*
	quebra_valores(swap,entrada1,t);//quebrando os digitos e colocando na entrada
	
	while(t<50){
		swap[t++]=0;
	}
	controle=1;
	t=0;
	
	printf("Digite a entrada para o segundo numero, 18 digitos por vez\n");
	while(controle==1){
		scanf("%lld",&valor);
		swap[t++]=valor;
		
		printf("Deseja continuar digitando um mesmo numero?\n 1 - sim\n 0 - nao\n");
		scanf("%d",&controle);
	}
	quebra_valores(swap,entrada2,t);//quebrando os digitos e colocando na entrada
	
	printf("\nqual e a operacao? 1 - soma\t 2 - exponenciacao\t 3 - inverso modular\n");
	scanf("%d",&operacao);
	if(operacao==1)
		soma(entrada1,entrada2,resultado);
	else if(operacao==2)
		exponenciacao();
	
	else 
		inverso_modular();
	
	int h=0;
	while(h<10){
		printf("%d ",h);
		printf("entrada1 %d\n",entrada1[h++]);
	}
	
	
	h=0;
	while(h<37){
		printf("%d ",h);
		printf("resultado %d\n",resultado[h++]);
	}
	* 
	* while(a>=0)
				printf("%c",swap[a--]);
	* */
	
	int h=0;
	while(h<20){
		printf("\n%d ",h);
		printf("entrada1 %d\n",entrada1[h++]);
	}
	
	h=0;
	while(h<20){
		printf("%d ",h);
		printf("entrada2 %d\n",entrada2[h++]);
	}
	
	return 0;
}
