#include <stdio.h>    // permette di usare scanf printf
#include <stdlib.h>   // conversioni stringa/numero rand() abs() exit() etc ...
#include <stdbool.h>  // gestisce tipo bool (per variabili booleane)
#include <assert.h>   // permette di usare la funzione assert


// programma per scrivere un array di bit in un file
// prende come input un intero n e il nome di un file
// e scrive nel file m bytes (con m il piu' piccolo intero maggiore di n/8)
// tali che l'iesimo bit e' 1 se e solo se i e' primo 


// prototipi
bool primo(int n);
void die(char *s);
char *crea_array_primi(int n);

int main(int argc, char *argv[])
{
    // controlla numero argomenti
    if(argc!=3) {
        printf("Uso: %s numero_positivo nome_file\n",argv[0]);
        return 1;
    }
    // converto primo input in intero
    int n = atoi(argv[1]);
    printf("Inserito il valore %d\n",n);
    if(n<=0) {
      printf("Valore non valido\n");
      exit(1);
    }
    // rendo n un multiplo di 8
    if(n%8!=0) {
     n = n + (8 - n%8);
    }
    assert(n%8==0);
    printf("Creo un array di bit di lunghezza: %d\n",n);
    char *primi = crea_array_primi(n);
    FILE *f = fopen(argv[2],"wb");
    if(f==NULL) die("Impossibile aprire il file");
    int scritti = fwrite(primi,sizeof(char),n/8,f);
    if(scritti!=n/8) die("Scrittura su file fallita");
    if(fclose(f)!=0) die("Errore chiusura file");
    free(primi);
    puts("Finito!");
    return 0;
}


// crea e restituisce un array di n/8 bytes 
// tale che l'iesimo bit e' 1 se e solo se i e' primo  
char *crea_array_primi(int n)
{
  assert(n>0 && n%8==0);
  char *p = malloc(sizeof(char) * (n/8));
  if(p==NULL) die("Allocazione fallita");
  // azzero tutti i bit
  for(int i=0;i<n/8;i++)
    p[i]=0;
  // metto gli 1 dove sono i primi
  for(int i=2;i<n;i++) 
    if(primo(i)){
      int byte = i/8;
      int bit = i%8;
      p[byte] = p[byte] | (1<<bit);  // setto a 1 l'iesimo bit senza modificare gli altri  
    }
  return p;  
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

// termina stampando prima un messaggio che cerca di spiegare perche'
void die(char *s)
{
  // perror stampa s seguito dal messaggio 
  // associato all'ultimo errore di sistema 
  perror(s); 
  exit(1);
}
