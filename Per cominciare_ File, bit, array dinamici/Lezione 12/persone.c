#define _GNU_SOURCE   // permette di usare estensioni GNU
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

// funzione per creare una nuova persona dati nome cognome e età
persona *crea_persona(char *n, char *cn, int e)
{
  persona *p = malloc(sizeof(persona));
  if(p==NULL) die("Errore allocazione");
  // inizializzo *p
  p->nome = n;
  p->cognome = cn;
  p->eta = e;
  return p;  
}

void distruggi_persona(persona *p)
{
    free(p->nome); // equivalente a ==  *p.nome
    free(p->cognome);
    free(p);
}


// legge una persona da file, se il file e' finito restituisce NULL
persona *leggi_persona_da_file(FILE *f)
{
  char *a, *b, *c;
  size_t n;
  // leggo il nome
  a = NULL; n=0;
  int e = getline(&a,&n,f);
  // fprintf(stderr, "e=%d n=%zu\n",e,n);
  if(e==EOF) {free(a); return NULL;} // se il file finisce mentre leggo il nome return NUL
  if(e<2) die("Nome illegale");
  // leggo il cognome
  b = NULL; n=0;
  e = getline(&b,&n,f);
  if(e==EOF) die("Dati persona incompleti");
  if(e<2) die("Cognome illegale");
  // leggo eta
  c = NULL; n=0;
  e = getline(&c,&n,f);
  if(e==EOF) die("Dati persona incompleti");
  if(e<2) die("Età illegale");
  // letture OK, elimino \n e converto eta' in intero
  a[strlen(a)-1] = '\0';
  b[strlen(b)-1] = '\0';
  int cint= atoi(c);
  free(c);
  // creo e restituisco una nuova persona
  return crea_persona(a,b,cint);
}


int main(int argc, char *argv[])
{
  // controlla numero argomenti
  if(argc!=2) {
      printf("Uso: %s nome_file\n",argv[0]);
      return 1;
  }
  // prova ad aprire il file in lettura
  FILE *f = fopen(argv[1],"rt");
  if(f==NULL) die("Impossibile aprire il file");
  persona *p;
  do {
    p = leggi_persona_da_file(f);
    if(p!=NULL) {
      printf("------\n");
      scrivi_persona(p,stdout);
      printf("\n");
      distruggi_persona(p);
    }
  } while(p!=NULL);
  fclose(f);
  return 0;
}
 
// stampa messaggio d'errore e termina
void die(char *s)
{
  perror(s);
  exit(1);
}    
    
