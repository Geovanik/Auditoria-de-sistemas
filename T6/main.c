/*definições
 vetor de 10 posições, cada posição com 10⁸ valores
 int de 32 bits
 * 
 * */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
void quebra_valores(long long int swap[],int entrada[],int t){
	int swap2[8],valor=0,cont=0;
	valor=swap[t-1];
	printf("%d",valor);
	while (valor>0){
		if(valor<10)
			//swap2[cont]=(valor%10);//colocando os digitos no vetor de swap//L[OGICA ERRADA
		printf("\nvalor %d",valor);
		valor/=10;
		//cont++;
	}
	printf("\nswap 2 %d\n",swap2[0]);
	/*cont=0;
	while(cont<8){
		printf("%d ",cont);
		printf("swap %d\n",swap2[cont++]);
	}*/
		
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
	printf("numeros\n");
	
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
