#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include <string.h>

//------------------------ UTILS -----------------------------

void die(char *s)
{
  perror(s);
  exit(1);
}

// ----------------------------------- LISTE GENERICHE ---------------------
typedef struct elem
{
  void *dato;
  struct elem *next;
} elemento;

elemento *inserisci_ordinato(elemento *lis, elemento *item, int (*f)(void *, void *))
{
  assert(item != NULL);
  elemento *candidato = lis;
  elemento *precedente = NULL;
  while (candidato != NULL)
  {
    if (f(candidato->dato, item->dato) > 0)
      break;
    precedente = candidato;
    candidato = candidato->next;
  }
  // caso in cui sono arrivato in fondo alla lista
  if (candidato == NULL)
  {
    if (precedente != NULL)
    { //lista non vuota
      precedente->next = item;
      item->next = NULL;
    }
    else
    { // lista vuota
      lis = item;
      item->next = NULL;
    }
  }
  else
  { // l'inserimento avviene non in fondo
    if (precedente != NULL)
    { //lista non vuota
      item->next = precedente->next;
      precedente->next = item;
    }
    else
    { // lista vuota
      lis = item;
      item->next = candidato;
    }
  }
  return lis;
}

void stampa_lista(elemento *lis, FILE *f, void (*print)(void *, FILE *))
{
  for (; lis != NULL; lis = lis->next)
  {
    print(lis->dato, f);
    fprintf(f, "\n");
  }
}

void distruggi_lista(elemento *lis, void (*distruggi)(void *))
{
  if (lis == NULL)
    return;
  distruggi_lista(lis->next, distruggi);
  distruggi(lis->dato);
  free(lis);
}

//----------------------- FUNZIONI CITTA ----------------------

typedef struct
{
  char *nome;
  double lat;
  double lon;
} citta;

int cmpnome(void *av, void *bv)
{
  citta *a = av;
  citta *b = bv;
  return strcmp(a->nome, b->nome);
}

void printcitta(void *av, FILE *f)
{
  citta *a = av;
  fprintf(f, "%s <%lf,%lf>", a->nome, a->lat, a->lon);
}

void distruggicitta(void *v)
{
  citta *c = v;
  free(c->nome);
  free(c);
}

// funzione per creare una nuova citta dati nome  e popolazione
citta *crea_citta(char *n, double lat, double lon)
{
  citta *c = malloc(sizeof(citta));
  if (c == NULL)
    die("Errore allocazione");
  // inizializzo *p
  c->nome = n;
  c->lat = lat;
  c->lon = lon;
  return c;
}

// legge una citta da file, se il file e' finito restituisce NULL
citta *leggi_citta_da_file(FILE *f)
{
  char *nome = NULL;
  double lat, lon;
  int e = fscanf(f, "%ms %lf %lf", &nome, &lat, &lon);
  if (e != 3)
  {
    return NULL;
  }
  return crea_citta(nome, lat, lon);
}

elemento *crea_lista_citta(FILE *f)
{
  assert(f != NULL);
  elemento *lis = NULL;
  while (true)
  {
    citta *c = leggi_citta_da_file(f);
    if (c == NULL)
      break;
    elemento *e = malloc(sizeof(elemento));
    e->dato = c;
    lis = inserisci_ordinato(lis, e, cmpnome);
    //lis = aggiungi_citta_head(lis,c);
  }
  return lis;
}

//-------------------------- MAIN --------------------------

int main(int argc, char *argv[])
{
  // controlla numero argomenti
  if (argc != 2)
  {
    printf("Uso: %s file\n", argv[0]);
    return 1;
  }
  FILE *f = fopen(argv[1], "rt");

  if (f == NULL)
    die("Apertura file");


  elemento *lis = crea_lista_citta(f);
  stampa_lista(lis, stdout, printcitta);
  distruggi_lista(lis, distruggicitta);
  fclose(f);
}