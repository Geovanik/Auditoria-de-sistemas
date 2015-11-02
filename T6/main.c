/*definições
 a entrada é um vetor de 10 posições, cada posição com 10⁸ valores
 int de 32 bits
 
 * 
 * */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

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
	printf("valor de 8 bits %d",valor);
	
	entrada[posicao]=valor;
	printf("entrada  %d",entrada[posicao]);
	
	inicializa_vetores(8,swap2);
}

void quebra_valores(long long int swap[],int entrada[],int t){//quebra os valores da entrada colocando eles na entrada
	int swap2[8],a=0,cont=7,posicao=9;
	long long int valor=0;
	
	while(a<8)//inicializa vetror de swap2
		swap2[a++]=0;
		
	valor=swap[--t];
	printf("\n%lld",valor);
	while (t>-1){//controla a quantidade de numeros dentro do vetor de swap

		swap2[cont--]=(valor%10);//colocando os digitos no vetor de swap/
		if(cont==-1){//colocando os valores na entrada
			uniao_valores(swap2,entrada,posicao);
			posicao--;
			cont=7;
		}
			
		//printf("\nvalor %lld ",valor);
		valor/=10;
		if(valor==0)
			valor=swap[--t];
		
		
	}
	//printf("\nswap 2 %d\n",swap2[0]);
	if(swap2[7]!=0)//para valores menores que 8 bits, valores mais significativos
		uniao_valores(swap2,entrada,posicao);
	
	cont=0;
	while(cont<8){
		printf("\n%d ",cont);
		printf("swap %d\n",swap2[cont++]);
	}	
}

int main(){
	int entrada[10],controle=1,t=0;
	long long int valor=0,swap[50];
	//inicializando vetor swap
	
	while(t<50){
		swap[t++]=0;
	}
	t=0;
	while(t<10){
		entrada[t++]=0;
	}
	t=0;
	//recebendo a entrada preenchendo o vetor de swap
	printf("Digite a entrada, 18 digitos por vez\n");
	while(controle==1){
		scanf("%lld",&valor);
		printf("%lld",valor);
		swap[t++]=valor;
		
		printf("Deseja continuar digitando um mesmo numero?\n 1 - sim\n 0 - nao\n");
		scanf("%d",&controle);
	}
	quebra_valores(swap,entrada,t);//quebrando os digitos e colocando na entrada
	int h=0;
	while(h<10){
		printf("%d ",h);
		printf("entrada %d\n",entrada[h++]);
	}
	
	return 0;
}
