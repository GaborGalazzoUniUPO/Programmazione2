#define _GNU_SOURCE   // permette di usare estensioni GNU
#include <stdio.h>    // permette di usare scanf printf
#include <stdlib.h>   // conversioni stringa/numero rand() abs() exit() etc ...
#include <stdbool.h>  // gestisce tipo bool (per variabili booleane)
#include <assert.h>   // permette di usare la funzione assert
#include <string.h>   // permette di usare le funzioni per le stringhe strlen, strcmp


void die(char *s);

// ------- oggetto citta e funzioni per la sua manipolazione -------------

// definisce il tipo citta composto dai campi nome e popolazione e 
// da un capo next da usare per le liste
typedef struct citt0 {
  char *nome;
  int popolazione;
  struct citt0 *next; 
} citta;


// stampa la citta a cui punta c
void scrivi_citta(citta *c, FILE *f)
{
  fprintf(f,"%s: %d",c->nome,c->popolazione);
}

// funzione per creare una nuova citta dati nome  e popolazione
citta *crea_citta(char *n, int p)
{
  citta *c = malloc(sizeof(citta));
  if(c==NULL) die("Errore allocazione");
  // inizializzo *p
  c->nome = n;
  c->popolazione = p;
  return c;  
}

void distruggi_citta(citta *c)
{
  if(c->next!=NULL)
      distruggi_citta(c->next);
    free(c->nome); // equivalente a ==  *c.nome
    free(c);
}

// legge una citta da file, se il file e' finito restituisce NULL
citta *leggi_citta_da_file(FILE *f)
{
  char *a, *b;
  size_t n;
  // leggo il nome
  a = NULL; n=0;
  int e = getline(&a,&n,f);
  //fprintf(stderr, "e=%d n=%zu\n",e,n);
  if(e==EOF) {free(a); return NULL;} // se il file finisce mentre leggo il nome return NUL
  if(e<2) die("Nome illegale");
  // leggo il cognome
  b = NULL; n=0;
  e = getline(&b,&n,f);
  if(e==EOF) die("Dati citta incompleti");
  if(e<2) die("Popolazione illegale");
  // letture OK, elimino \n e converto eta' in intero
  a[strlen(a)-1] = '\0';
  int  p = atoi(b);
  free(b);
  // creo e restituisco una nuova citta
  return crea_citta(a,p);
}



// ---- operazioni sulle liste di citta

// stampa le citta della lista lis
void scrivi_lista(citta *lis, FILE *f)
{
  while(lis!=NULL) {
    scrivi_citta(lis,f);
    fprintf(f,"\n");
    lis = lis->next;
  }
}

// DA FARE

// aggiunge citta in cima alla lista lis
citta *aggiungi_citta_head(citta *lis, citta *c)
{
  assert(c!=NULL);
  c->next = lis;
  return c;
}

// dato un file costruisce una lista con le citta in esso contenuto 
citta *leggi_lista_da_file(FILE *f)
{
  assert(f!=NULL);
  citta *head= NULL;
  while(true) {
    citta *p = leggi_citta_da_file(f);
    if(p==NULL) break;
    head = aggiungi_citta_head(head, p);
  };
  return head;
}


// restituisce la somma delle popolazioni delle citta nella lista
int somma_pop_lista_citta(citta *lista)
{
  assert(lista!=NULL);
  int cont = 0;
  while(lista != NULL)
  {
    cont += lista->popolazione;
    lista = lista->next;
  }
  return cont;
}

// restituisce il numero di citta' con popolazione tra minp e maxp 
int conta_citta_in_range(citta *lista, int minp, int maxp)
{
assert(lista!=NULL);
  int cont = 0;
  while(lista != NULL)
  {
    int pop = lista->popolazione;
    if(pop > minp && pop < maxp)
      cont ++;
    lista = lista->next;
  }
  return cont;
}


// aggiunge citta' c in fondo alla lista lis
// restiuisce la nuova lista 
citta *aggiungi_citta_tail(citta *lista, citta *c)
{
  assert(c!=NULL);
  citta* head = lista;
  do{
    lista = lista->next;
  }while(lista->next!=NULL);
  lista->next = c;
  c->next = NULL;
  return head;
}

// esegue il reverse di una lista
citta *reverse(citta *vecchia)
{
  citta *nuova = NULL;
  while(vecchia!=NULL) {
    citta *corrente = vecchia;
    citta *prossimo = vecchia->next;
    nuova = aggiungi_citta_head(nuova,corrente);
    vecchia = prossimo;
  }
  return nuova;
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
  // legge il file
  citta *lis=leggi_lista_da_file(f) ;
  fclose(f);
  // stampa lista su stdout
  scrivi_lista(lis, stdout);
  // test funzioni popolazione
  printf("Totale popolazione: %d\n", somma_pop_lista_citta(lis));
  printf("Citta con meno di 500.000 abitanti: %d\n", conta_citta_in_range(lis,0,500000));
  // aggiungi citta in coda
  lis = aggiungi_citta_tail(lis,crea_citta("Paperopoli", 2000)); 
  scrivi_lista(lis, stdout);
  lis = reverse(lis);
  printf("--- dopo il reverse ----\n");
  scrivi_lista(lis, stdout);
  distruggi_citta(lis);
  lis = NULL;
  return 0;
}
 
// stampa messaggio d'errore e termina
void die(char *s)
{
  perror(s);
  exit(1);
}    
    
