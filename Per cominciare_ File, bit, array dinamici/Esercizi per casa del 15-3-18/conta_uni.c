#include <stdio.h>
#include <stdlib.h>

int conta_uni(int n);

int main(int argc, char* argv[]){
	if(argc!=2){
		printf("usage %s numero_intero",argv[0]);
		return 1;
	}
	int n = atoi(argv[1]);
	int uni = conta_uni(n);
	printf("Numero di uni: %d", uni);
	return 0;
}

int conta_uni(int n){
	int cont = 0;
	while(n!=0)
	{
		cont += n&1;
		n = n>>1;
	}
	return cont;	
}
/**
int conta_uni(int n){
	int cont = 0;
	for(int i = 0; i<sizeof(int); i++){
		cont += (n>>i)&1;
	}
	return cont;	
}
*/