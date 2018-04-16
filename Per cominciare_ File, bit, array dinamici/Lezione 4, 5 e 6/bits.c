#include <stdio.h>    // permette di usare scanf printf
#include <stdlib.h>   // conversioni stringa/numero rand() abs() exit() etc ...
#include <stdbool.h>  // gestisce tipo bool (per variabili booleane)
#include <assert.h>   // permette di usare la funzione assert


void die(char *s);
char *bits(int n);

int main(int argc, char *argv[])
{
    // controlla numero argomenti
    if(argc!=2) {
        printf("Uso: %s numero_positivo_minore_di_256\n",argv[0]);
        return 1;
    }
    // converto in intero
    int i = atoi(argv[1]);
    printf("Inserito il valore %d\n",i);
    if(i<0 || i>=256) {
      printf("Valore non valido\n");
      exit(1);
    }
    char *s = bits(i);
    printf("Risultato: %s\n",s);
    free(s);
    return 0;
}

char *bits(int n)
{
  assert(n>=0 && n< 256);
  char *s = malloc(9*sizeof(char));
  if(s==NULL) die("memoria finita in bits");
  s[8]='\0'; // uguale a s[8]=0;
  for(int i=0;i<8;i++) {
    //if( (n & (1<<i)) !=0) s[7-i] = '1';
    //else s[7-i] = '0';
    // equivalente a: 
    s[7-i] = (n & (1<<i)) ? '1' : '0';
  }
  return s;
}

// stampa messaggio d'errore e termina
void die(char *s)
{
  perror(s);
  exit(1);
}    
    

