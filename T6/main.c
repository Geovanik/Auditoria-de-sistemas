/*definições
 vetor de 10 posições, cada posição com 10⁸ valores
 int de 32 bits
 * 
 * */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
void uniao_valores(int swap2[],int entrada[]){
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
	
	//entrada[]=valor;
}

void quebra_valores(long long int swap[],int entrada[],int t){//quebra os valores da entrada colocando eles na entrada
	int swap2[8],a=0,cont=7;
	long long int valor=0;
	
	while(a<8)//inicializa vetroe de swap2
		swap2[a++]=0;
		
	valor=swap[--t];
	printf("\n%lld",valor);
	while (t>-1){//controla a quantidade de numeros dentro do vetor de swap

		swap2[cont--]=(valor%10);//colocando os digitos no vetor de swap/
		if(cont==-1)//colocando os valores na entrada ------------------------------e quando o valor n tiver 8 bits??????
			uniao_valores(swap2,entrada);
			
		//printf("\nvalor %lld ",valor);
		valor/=10;
		if(valor==0)
			valor=swap[--t];
		
	}
	//printf("\nswap 2 %d\n",swap2[0]);
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
		swap[t++]=-0;
		
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
	return 0;
}
/*
 * while (valor>0){
			swap[t]=(valor%10);//colocando os digitos no vetor de swap
			valor/=10;
			t++;
		}
		* 
		* t=0;
	while(t<50){
		printf("%d ",t);
			printf("swap %lld\n",swap[t++]);
		}
		* */
