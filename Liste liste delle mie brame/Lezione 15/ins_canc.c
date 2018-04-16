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

// crea una citta creando una copia del nome e allocandola con 
// malloc in modo che possa essere distrutta con distruggi_citta
citta *crea_citta_copia_nome(char *n, int p)
{
  citta *c = malloc(sizeof(citta));
  if(c==NULL) die("Errore allocazione");
  // inizializzo *c
  size_t size = 1 + strlen(n);
  c->nome = malloc(size*sizeof(char)); 
  if(c->nome==NULL) die("Errore allocazione");
  strcpy(c->nome,n);
  c->popolazione = p;
  return c;  
}

void distruggi_citta(citta *c)
{
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

// dealloca tutti gli elementi della lista 
void distruggi_lista(citta *head)
{
  while(head!=NULL) {
    citta *prossimo = head->next;
    distruggi_citta(head);
    head = prossimo;
  }
}

// aggiunge citta in cima alla lista lis
citta *aggiungi_citta_head(citta *lis, citta *c)
{
  assert(c!=NULL);
  c->next = lis;
  return c;
}


// aggiunge citta mantenendo l'ordine della popolazione
citta *inserisci_citta_ordinata(citta *lis, citta *c)
{
  assert(c!=NULL);
  citta *candidato = lis;
  citta *precedente = NULL;
  while(candidato!=NULL) {
    if(candidato->popolazione > c->popolazione)
      break;
    precedente = candidato;
    candidato = candidato->next;
  }
  // caso in cui sono arrivato in fondo alla lista
  if(candidato==NULL) {
    if(precedente!=NULL) {//lista non vuota
      precedente->next = c;
      c->next = NULL;
    }
    else {// lista vuota
      lis = c;
      c->next = NULL;
    }
  }
  else {// l'inserimento avviene non in fondo
    if(precedente!=NULL) {//lista non vuota
      c->next = precedente->next;
      precedente->next = c;
    }
    else {// lista vuota
      lis = c;
      c->next = candidato;
    }
  }
  return lis;
}


// versione alternativa (piu' semplice) della funzione precedente 
// in cui tratto separatamente il caso dell'inserimento in testa
citta *inserisci_citta_ordinata2(citta *lis, citta *c)
{
  assert(c!=NULL);
  // controlla se devo inserire in testa
  if(lis==NULL || lis->popolazione>c->popolazione) {
    c->next = lis; // corretto anche quando lis==NULL
    return c;
  }
  // l'inserimento non e' in testa: parto dal secondo elemento 
  citta *candidato = lis->next;
  citta *precedente = lis;
  while(candidato!=NULL) {
    if(candidato->popolazione > c->popolazione)
      break;
    precedente = candidato;
    candidato = candidato->next;
  }
  assert(precedente!=NULL); 
  c->next = candidato; // corretto anche quando candidato == NULL
  precedente->next = c;
  return lis;
}


// dato un file costruisce una lista con le citta in esso contenuto 
citta *leggi_lista_da_file(FILE *f)
{
  assert(f!=NULL);
  citta *lis=NULL;
  while(true) {
    citta *c = leggi_citta_da_file(f);
    if(c==NULL) break;
    lis = inserisci_citta_ordinata(lis,c);
  }
  return lis;
}


// cerca in lista citta' con nome n
// restituisco puntatore alla citta con nome n o NULL
// se non ci sono citta' con quel nome nella lista
citta *cerca_citta(citta *lis, char *n)
{
  assert(n!=NULL);
  while(lis!=NULL) {
    if(strcmp(lis->nome,n)==0)
      break;
    lis = lis->next;
  }
  return lis;
}

// cerca in lista citta' con nome n se la trova la cancella
// restituisce la nuova lista
// nella variabile a cui punta trovata viene scritto l'indirizzo
// della citta' eliminata e NULL se la citta' non viene trovata  
citta *cancella_citta(citta *lis, char *n, citta **trovata)
{
  assert(n!=NULL);
  *trovata = NULL;
  if(lis==NULL)  // NON SERVE
    return NULL; // lista vuota nulla da fare
  // sono sicuro che esiste almeno un elemento  
  citta *candidato = lis;
  citta *precedente = NULL;
  while(candidato!=NULL) {
    if(strcmp(candidato->nome,n)==0)
      break;
    precedente = candidato;
    candidato = candidato->next;  
  }
  if(candidato==NULL)
    return lis;
  // ho trovato un elemento da cancellare  
  assert(strcmp(candidato->nome,n)==0); 
  assert(precedente==NULL || precedente->next==candidato);
  *trovata = candidato;
  if(precedente==NULL) {
    assert(lis==candidato);
    lis = candidato->next;
  }
  else 
    precedente->next = candidato->next;
  return lis;  
}

int main(int argc, char *argv[])
{
  // controlla numero argomenti
  if(argc<2) {
      printf("Uso: %s nome_file [citta]\n",argv[0]);
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
  // ciclo operazioni
  for(int i=2;i<argc;i++) {
    printf("Cancello: <%s>\n",argv[i]);
    citta *cancellata;
    lis = cancella_citta(lis,argv[i],&cancellata);
    if(cancellata==NULL)
      printf("%s non trovata\n",argv[i]);
    else   
      distruggi_citta(cancellata);  
  }
  printf("--- dopo operazioni ----\n");
  scrivi_lista(lis, stdout);
  distruggi_lista(lis);
  return 0;
}
 
// stampa messaggio d'errore e termina
void die(char *s)
{
  perror(s);
  exit(1);
}    
