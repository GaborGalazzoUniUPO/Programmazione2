#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

/**
la funzione inserisci deve spostare il valore a[n-1] all'interno di a[ ] in modo di mantenere l'ordinamento. Ad esempio se inizialmente a= [2, 8, 13, 15, 10] al termine dell'esecuzione di inserisci(a,5) si deve avere a=[2,8,10,13,15]. Per realizzare questo il valore 15 deve essere stato copiato da a[3] ad a[4], il valore 13 da a[2] a a[3] e il valore 10 deve essere stato scritto in a[2].
*/
//dato un array di n>0 interi svolga quanto descritto sopra. La funzione deve essere realizzata utilizzando solamente un ciclo for, dovete solamente stare attenti a non sovrascrivere gli elementi
void inserisci_stringhe(char *a[ ], int n){
	assert(n>0);
	char* v = a[n-1];
	for(int i = 0; i<n; i++){
		if(strcmp(a[i],v)>0)
		{
			for(int j = n-1; j>i; j--)
				a[j] = a[j-1];
			a[i] = v;
			return;
		}
	}
}

void stampa_array(char* a[],int n){
	for(int i = 0; i<n; i++)
		printf(" %s ", a[i]);
	puts("");
}

void insertion_sort_stringhe(char* a[ ], int n) {
  for(int i=2;i<= n; i++) {
    inserisci_stringhe(a,i);
    stampa_array(a,n);
  }
}

int main(int argc, char* argv[]){
	if(argc<2)
	{
		printf("usage: %s str1, str2, ... strN", argv[0]);
		return 1;
	}
	char* a[argc-1];
	for(int i = 1; i<argc; i++)
		a[i-1] = argv[i];
	insertion_sort_stringhe(a, argc-1);
	return 0;
}