#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

/**
la funzione inserisci deve spostare il valore a[n-1] all'interno di a[ ] in modo di mantenere l'ordinamento. Ad esempio se inizialmente a= [2, 8, 13, 15, 10] al termine dell'esecuzione di inserisci(a,5) si deve avere a=[2,8,10,13,15]. Per realizzare questo il valore 15 deve essere stato copiato da a[3] ad a[4], il valore 13 da a[2] a a[3] e il valore 10 deve essere stato scritto in a[2].
*/
//dato un array di n>0 interi svolga quanto descritto sopra. La funzione deve essere realizzata utilizzando solamente un ciclo for, dovete solamente stare attenti a non sovrascrivere gli elementi
void inserisci(int a[ ], int n){
	assert(n>0);
	int v = a[n-1];
	for(int i = 0; i<n; i++){
		if(a[i]>v)
		{
			for(int j = n-1; j>i; j--)
				a[j] = a[j-1];
			a[i] = v;
			return;
		}
	}
}

void stampa_array(int a[],int n){
	for(int i = 0; i<n; i++)
		printf(" %d ", a[i]);
	puts("");
}

void insertion_sort(int a[ ], int n) {
  for(int i=2;i<= n; i++) {
    inserisci(a,i);
    stampa_array(a,n);
  }
}

int main(int argc, char* argv[]){
	if(argc<2)
	{
		printf("usage: %s num1, num2, ... numN", argv[0]);
		return 1;
	}
	int a[argc-1];
	for(int i = 1; i<argc; i++)
		a[i-1] = atoi(argv[i]);
	insertion_sort(a, argc-1);
	return 0;
}