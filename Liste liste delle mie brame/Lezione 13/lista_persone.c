#define _GNU_SOURCE   // permette di usare estensioni GNU
#include <stdio.h>    // permette di usare scanf printf
#include <stdlib.h>   // conversioni stringa/numero rand() abs() exit() etc ...
#include <stdbool.h>  // gestisce tipo bool (per variabili booleane)
#include <assert.h>   // permette di usare la funzione assert
#include <string.h>   // permette di usare le funzioni per le stringhe strlen, strcmp


void die(char *s);

// definisce il tipo persona composto dai campi nome e cognome ed eta'
// e con il campo next da usare per le liste
typedef struct pers {
  char *nome;
  char *cognome;
  int eta;
  struct pers *next;
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


// ------------- operazioni sulle liste -------

// aggiunge la persona p in cima alla lista head
persona *aggiungi_head(persona *head, persona *p)
{
  // la persona da aggiungere deve esistere
  assert(p!=NULL); 
  p->next = head;
  return p;
}

// scrive il contenuto della lista head nel file f
void scrivi_lista_persone(persona *head, FILE *f)
{
  while(head!=NULL) {
    scrivi_persona(head,f);
    fprintf(f,"\n--------------------------\n");
    head = head->next;
  }
}

// restituisce il numero di elementi della lista 
int lunghezza_lista(persona *head)
{
  int tot=0;
  while(head!=NULL) {
    tot++;
    head = head->next;
  }
  return tot;
}

// dealloca tutti gli elementi della lista 
void distruggi_lista(persona *head)
{
  while(head!=NULL) {
    persona *prossimo = head->next;
    distruggi_persona(head);
    head = prossimo;
  }
}

// restiuisce una nuova lista con gli elementi della vecchia in ordine inverso
persona *reverse(persona *vecchia)
{
  persona *nuova = NULL;
  while(vecchia!=NULL) {
    persona *corrente = vecchia;
    persona *prossimo = vecchia->next;
    nuova = aggiungi_head(nuova,corrente);
    vecchia = prossimo;
  }
  return nuova;
}



// ---------- main -----------------

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

  // ---lettura della lista da file  
  persona *head= NULL;
  while(true) {
    persona *p = leggi_persona_da_file(f);
    if(p==NULL) break;
    head = aggiungi_head(head, p);
  };
  fclose(f);
  // stampa lista persone e # numero elementi
  scrivi_lista_persone(head, stdout);
  printf("La lista contiene %d elementi\n",lunghezza_lista(head));
  // calcola il reverse ed esegue nuova stampa
  printf("Eseguo il reverse\n");
  head = reverse(head);
  scrivi_lista_persone(head, stdout);
  printf("La lista reverse contiene %d elementi\n",lunghezza_lista(head));
  // dealloca la lista 
  distruggi_lista(head);
  return 0;
}


// stampa messaggio d'errore e termina
void die(char *s)
{
  perror(s);
  exit(1);
}    
    
