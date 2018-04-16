#include <stdio.h>    // permette di usare scanf printf
#include <stdlib.h>   // conversioni stringa/numero rand() abs() exit() etc ...
#include <stdbool.h>  // gestisce tipo bool (per variabili booleane)
#include <assert.h>   // permette di usare la funzione assert


// programma che prende come input un intero i e il nome di
// un file e mi dice se l'iesimo bit di quel file e' 0 o 1

// prototipi
void die(char *s);


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
    // copio il contenuto del file in un array
    FILE *f = fopen(argv[2],"rb");
    if(f==NULL) die("Impossibile aprire il file");
    // sposto la posizione alla fine del file
    fseek(f,0,SEEK_END);
    // leggo il numero di bytes nel file
    long numero_bytes = ftell(f);
    printf("Il file contiene %ld bytes\n",numero_bytes);
    char *a = malloc(sizeof(char)*numero_bytes);
    if(a==NULL) die("Allocazione memoria fallita");
    fseek(f,0,SEEK_SET);
    int letti = fread(a,sizeof(char),numero_bytes,f);
    if(letti!=numero_bytes) die("Lettura fallita");
    // l'array e pronto guardo nella posizione n
    if(n>=numero_bytes*8) 
      printf("Non ho informazioni\n");
    else {
      int byte = n/8;
      int bit = n%8;
      bool risultato = (a[byte] & (1<<bit)) != 0;
      printf("Il bit %d-esimo vale %d\n",n, (risultato? 1 : 0));
    }
    if(fclose(f)!=0) die("Errore chiusura file");
    free(a);
    puts("Finito!");
    return 0;
}


// termina stampando prima un messaggio che cerca di spiegare perche'
void die(char *s)
{
  // perror stampa s seguito dal messaggio 
  // associato all'ultimo errore di sistema 
  perror(s); 
  exit(1);
}

