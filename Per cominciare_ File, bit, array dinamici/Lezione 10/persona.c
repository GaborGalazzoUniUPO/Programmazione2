#include <stdio.h>    // permette di usare scanf printf
#include <stdlib.h>   // conversioni stringa/numero rand() abs() exit() etc ...
#include <stdbool.h>  // gestisce tipo bool (per variabili booleane)
#include <assert.h>   // permette di usare la funzione assert
#include <string.h>   // permette di usare le funzioni per le stringhe strlen, strcmp


void die(char *s);

// definisce il tipo persona composto dai campi nome e cognome ed eta'
typedef struct {
  char *nome;
  char *cognome;
  int eta;
} persona;

// stampa la persona a cui punta c
void scrivi_persona(persona *c, FILE *f)
{
  fprintf(f,"NOME: %s\nCOGNOME: %s\nETA: %d",c->nome,c->cognome,c->eta);
}
 
// esempio di lettura di stringa con scanf e modificatore %ms
int main(int argc, char *argv[])
{
  persona p;
  printf("Inserisci nome cognome età: ");
  // si noti che passiamo gli indirizzi di p.nome e p.cognome
  int e = scanf("%ms %ms %d", &p.nome, &p.cognome, &p.eta);
  if(e!=3) die("Errore inserimento dati");
  printf("ho letto:\n");
  scrivi_persona(&p,stdout);
  printf("\n");
  return 0;
}
 
// stampa messaggio d'errore e termina
void die(char *s)
{
  perror(s);
  exit(1);
}    
