#define _GNU_SOURCE  // permette di usare estensioni GNU
#include <stdio.h>   // permette di usare scanf printf
#include <stdlib.h>  // conversioni stringa/numero rand() abs() exit() etc ...
#include <stdbool.h> // gestisce tipo bool (per variabili booleane)
#include <assert.h>  // permette di usare la funzione assert
#include <string.h>  // permette di usare le funzioni per le stringhe strlen, strcmp

void die(char *s);

// ------- oggetto citta e funzioni per la sua manipolazione -------------

// definisce il tipo citta composto dai campi nome e popolazione e
// da un capo next da usare per le liste
typedef struct
{
    char *nome;
    int popolazione;
} citta;

// stampa la citta a cui punta c
void scrivi_citta(citta *c, FILE *f)
{
    fprintf(f, "%s: %d", c->nome, c->popolazione);
}

// funzione per creare una nuova citta dati nome  e popolazione
// se deallocata con free potrebbe dare errore
citta *crea_citta(char *n, int p)
{
    citta *c = malloc(sizeof(citta));
    if (c == NULL)
        die("Errore allocazione");
    // inizializzo *p
    c->nome = n;
    c->popolazione = p;
    return c;
}

// crea una citta creando una copia del nome e allocandola con malloc
// cosi' siamo sicuri puo' essere deallocata con free
citta *crea_citta_copia_nome(char *n, int p)
{
    citta *c = malloc(sizeof(citta));
    if (c == NULL)
        die("Errore allocazione");
    // inizializzo *c
    size_t size = 1 + strlen(n);
    c->nome = malloc(size * sizeof(char));
    if (c->nome == NULL)
        die("Errore allocazione");
    strcpy(c->nome, n);
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
    a = NULL;
    n = 0;
    int e = getline(&a, &n, f);
    //fprintf(stderr, "e=%d n=%zu\n",e,n);
    if (e == EOF)
    {
        free(a);
        return NULL;
    } // se il file finisce mentre leggo il nome return NUL
    if (e < 2)
        die("Nome illegale");
    // leggo il cognome
    b = NULL;
    n = 0;
    e = getline(&b, &n, f);
    if (e == EOF)
        die("Dati citta incompleti");
    if (e < 2)
        die("Popolazione illegale");
    // letture OK, elimino \n e converto eta' in intero
    a[strlen(a) - 1] = '\0';
    int p = atoi(b);
    free(b);
    // creo e restituisco una nuova citta
    return crea_citta(a, p);
}

// ---- operazioni sugli array di citta

// stampa le citta dell'array a[]
void scrivi_array(citta *a[], int n, FILE *f)
{
    for (int i = 0; i < n; i++)
    {
        scrivi_citta(a[i], f);
        fprintf(f, "\n");
    }
}

// dealloca tutti gli elementi dell'array
void distruggi_array(citta *a[], int n)
{
    for (int i = 0; i < n; i++)
    {
        distruggi_citta(a[i]);
    }
}

// dato un file costruisce una lista ordinata con le citta in esso contenuto
citta **leggi_array_da_file(FILE *f, int *n)
{
    assert(f != NULL);
    citta **a = NULL;
    int capacita = 0;
    int size = 0;
    while (true)
    {
        citta *c = leggi_citta_da_file(f);
        if (c == NULL)
            break;
        if (size >= capacita)
        {
            assert(size == capacita);
            capacita += 10;
            a = realloc(a, sizeof(citta *) * capacita);
            if (a == NULL)
                die("allocazione fallita");
        }
        assert(size < capacita);
        a[size++] = c;
    }
    a = realloc(a, size * sizeof(citta *));
    if (a == NULL)
        die("alloczione fallita");
    *n = size;
    return a;
}

// funzione che esegue la maggior parte del lavoro dell'insertion sort
// metto a[n] al suo posto in a[0...n-1] che devono essere gia' ordinati
void insert(citta *a[], int n)
{
    assert(n > 0);
    citta *tmp = a[n]; // creo il buco in a[n]
    for (int i = n - 1; i >= 0; i--)
    {
        // in a[i+1] c'e' un buco
        if (tmp->popolazione >= a[i]->popolazione)
        {
            a[i + 1] = tmp; // metto tmp nel buco e mi fermo
            return;
        }
        else                 // tmp < a[i]
            a[i + 1] = a[i]; // metto a[i] nel buco e procedo, il buco ora e' in a[i]
    }
    // c'e' un buco in a[0] e ci metto tmp perche' e' il piu' piccolo
    a[0] = tmp;
}

// fuzione che esegue il sorting delle citta' in a[]
void insertion_sort(citta *a[], int n)
{
    if (n <= 1)
        return;
    for (int i = 1; i < n; i++)
        insert(a, i);
}

// merge di a1[] di n1 elementi ordinato con
// a2[] di n2 elementi oridnato
// restituisce array di *n3 = n1+n2 elementi ordinati
citta **merge_array(citta *a1[], int n1, citta *a2[], int n2, int *n3)
{
    citta **c = malloc((n1 + n2) * sizeof(citta *));
    if (c == NULL)
        die("Allocazione fallita");
    int ic = 0, i1 = 0, i2 = 0;
    while (i1 < n1 || i2 < n2)
    {
        if (i1 == n1)
            c[ic++] = a2[i2++];
        else if (i2 == n2)
            c[ic++] = a1[i1++];
        else
        {
            if (a1[i1]->popolazione < a2[i2]->popolazione)
                c[ic++] = a1[i1++];
            else
                c[ic++] = a2[i2++];
        }
    }
    *n3 = n1 + n2;
    return c;
}

void mergesort(citta *a[], int n)
{
    
    if (n < 2)
        return;

    int i = n / 2;

    mergesort(a, i);
    mergesort(a+i,n-i);
    int c;
    citta** b = merge_array(a, i, a+i, n-i, &c);
    for(int i = 0; i<c; i++)
        a[i] = b[i];
    free(b);
}

int main(int argc, char *argv[])
{
    // controlla numero argomenti
    if (argc != 2)
    {
        printf("Uso: %s file1\n", argv[0]);
        return 1;
    }
    // prova ad aprire il primo file in lettura
    FILE *f = fopen(argv[1], "rt");
    if (f == NULL)
        die("Impossibile aprire il file1");
    // legge il file
    int n1;
    citta **lis1 = leggi_array_da_file(f, &n1);
    fclose(f);

    // stampa array su stdout
    puts("------- array 1 -----");
    scrivi_array(lis1, n1, stdout);

    puts("------- array ordinato -----");
    mergesort(lis1, n1);
    scrivi_array(lis1, n1, stdout);
    distruggi_array(lis1, n1);
    // dealloca gli array
    free(lis1);
    return 0;
}

// stampa messaggio d'errore e termina
void die(char *s)
{
    perror(s);
    exit(1);
}
