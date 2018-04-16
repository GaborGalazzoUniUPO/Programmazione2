#include <stdio.h>    // permette di usare scanf printf
#include <stdlib.h>   // conversioni stringa/numero rand() abs() exit() etc ...
#include <stdbool.h>  // gestisce tipo bool (per variabili booleane)
#include <assert.h>   // permette di usare la funzione assert

// programma che crea un array di numeri primi usando
// malloc/realloc/free

// prototipi
bool primo(int n);
int *crea_array_primi(int n, int *num_elementi);
void stampa_array(int a[], int n);

int main(int argc, char *argv[])
{
    // controlla numero argomenti
    if(argc!=2) {
        printf("Uso: %s numero_positivo\n",argv[0]);
        return 1;
    }
    // converte l'argomento in intero
    int n = atoi(argv[1]);
    if(n<1) {
      printf("L'argomento deve essere maggiore uguale a 1\n");
      return 1;
    }
    // costruisco array dei numeri primi <= n
    int num;
    int *primi = crea_array_primi(n,&num);
    // array riempito: contiene num elementi. Procedo con la stampa
    stampa_array(primi,num);
    // fine stampa, restituisco la memoria
    free(primi);
    // d'ora in poi non posso piu' usare primi[]
    return 0;
}

// funzione che prende come input un intero n positivo
// restituisce un puntatore all'array che contiene i 
// primi <=n e scrive in *num_elementi il numero di primi trovato
int *crea_array_primi(int n, int *num_elementi)
{
    int *primi;    // puntatore a intero
    primi = malloc(n*sizeof(int));
    if(primi==NULL) {
      puts("Memoria insufficiente");
      exit(1);
    }
    // da adesso posso scrivere primi[0], primi[1],...,primi[n-1]
    int messi=0; // elementi messi in primi[] e posizione del prossimo elemento da aggiungere
    for(int i=2;i<=n;i++)
      if(primo(i)) {
        primi[messi] = i;
        messi++;
      }
    *num_elementi = messi;
    primi = realloc(primi,messi*sizeof(int));
    return primi;
}

// prende in input un array di n interi e lo stampa
void stampa_array(int a[], int n)
{
    assert(n>0);
    for(int i=0;i<n;i++)
      printf("%8d",a[i]);
    printf("\n");  
}

// dato un intero positivo restituisce true
// se e' primo, false altrimenti 
bool primo(int n)
{
  assert(n>0);
  
  // caso n==1
  if(n==1) return false;
  // considero il caso n pari
  if(n%2==0) {    
    if(n==2) return true;
    else return false;
  }
  // considero il caso n dispari >= 3
  assert(n>=3 && n%2!=0);
  for(int i=3; i*i<= n; i+=2) {
    if(n%i==0)
      return false;
  }
  return true;
}
