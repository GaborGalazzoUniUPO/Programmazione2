#define _GNU_SOURCE  // permette di usare estensioni GNU
#include <stdio.h>   // permette di usare scanf printf
#include <stdlib.h>  // conversioni stringa/numero rand() abs() exit() etc ...
#include <stdbool.h> // gestisce tipo bool (per variabili booleane)
#include <assert.h>  // permette di usare la funzione assert
#include <string.h>  // permette di usare le funzioni per le stringhe strlen, strcmp
#include <math.h>    // permette di usare sin cos e altre funzioni matematiche avanzate
#include "coordinate.h"
#include "citta.h"

void die(char *s);

// ------- liste ------

citta *leggi_da_file(FILE *f, int *n)
{
    assert(f != NULL);
    int i = 0;
    citta *lis = NULL; // lista inzialmente vuota
    while (true)
    {
        double la, lo;
        char *s;
        int e = fscanf(f, "%ms %lf %lf", &s, &la, &lo);
        if (e != 3)
            break;
        citta *c = malloc(sizeof(citta));
        if (c == NULL)
            die("malloc");
        c->nome = s;
        c->coord.lat = la;
        c->coord.lon = lo;
        // inseriamo c in testa alla lista
        c->next = lis;
        lis = c;
        i++;
    }
    *n = i;
    return lis;
}


void stampa_citta_generico(void *a, FILE *f)
{

    stampa_citta((citta *)a, f);
}

void stampa_array_genrico(void *a[], int n, void (*stampa)(void *, FILE *), FILE *f)
{

    for (int i = 0; i < n; i++)
    {
        stampa(a[i], f);
        fprintf(f,"\n");
    }
}

// quicksort
int partition(citta *a[], int n, citta* origine)
{
  // scelgo pivot in posizione random 
  int k = random() % n;    // posizione random del pivot
  citta *pivot = a[k];            // pivot
  a[k]=a[0];a[0]=pivot;    // scambia A[k]<->A[0]

  int i= -1; // puntatore oltre estremo sinistro
  int j = n; //puntatore oltre estremo destro
  while(1) {
    while(vicino_citta(a[--j],pivot, origine)>0) 
      ; // esce se a[j]<=pivot
    while(vicino_citta(a[++i],pivot, origine)<0) 
      ; // esce se a[i]>=pivot
    if(i<j) {
      // scambia a[i] <-> a[j]
      citta *t=a[i]; a[i]=a[j]; a[j]=t;
    }
    else break;
  }
  // la prima meta' e' a[0] .. a[j] quindi ha j+1 elementi   
  assert(j+1 >0);
  assert(j+1 < n);
  return j+1; 
}


// Quicksort: ordina a[0]...a[n-1]
void ordina_per_distanza(citta *a[], int n, citta* origine){
  if(n>1) {
    int q = partition(a,n, origine);
    assert(q>0 && q<n);  // verifica che entrambe le partizioni siano non vuote
    ordina_per_distanza(a,q, origine);      // chiamata ricorsiva prima parte 
    ordina_per_distanza(a+q,n-q, origine);  // chiamata ricorsiva seconda parte
  }
}

// ---------------- main -------

int main(int argc, char *argv[])
{
    // controlla numero argomenti
    if (argc != 5)
    {
        printf("Uso: %s file nome_origine lat_origine lon_origine\n", argv[0]);
        return 1;
    }
    FILE *f = fopen(argv[1], "rt");
    if (f == NULL)
        die("Apertura file");
    int n;
    citta *lis = leggi_da_file(f, &n);

    citta *array_citta[n];
    int i = 0;
    // esempio scorriemnto di un array con ciclo for
    for (citta *a = lis; a != NULL; a = a->next)
    {
        array_citta[i++] = a;
    }

    citta* origine = malloc(sizeof(citta));
    origine->nome = argv[2];
    coordinate c;
    c.lat = atol(argv[3]);
    c.lon = atol(argv[4]);
    origine->coord = c;

    ordina_per_distanza(array_citta, n, origine);

    stampa_array_genrico((void **)array_citta, n, stampa_citta_generico, stderr);
    return 0;
}

// stampa messaggio d'errore e termina
void die(char *s)
{
    perror(s);
    exit(1);
}
