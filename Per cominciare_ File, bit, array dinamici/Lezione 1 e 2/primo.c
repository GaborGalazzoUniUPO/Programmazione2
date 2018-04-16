#include <stdio.h>    // permette di usare scanf printf
#include <stdlib.h>   // conversioni stringa/numero rand() abs() exit() etc ...
#include <stdbool.h>  // gestisce tipo bool (per variabili booleane)
#include <assert.h>   // permette di usare la funzione assert


bool primo(int n);

int main(int argc, char *argv[])
{
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
    // invoco la funzione
    bool risultato = primo(n); 
    if(risultato)
      puts("Il numero e' primo");
    else
      puts("Il numero e' composto");
  
    return 0;
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








