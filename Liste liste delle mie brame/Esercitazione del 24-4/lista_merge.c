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
typedef struct citt0
{
    char *nome;
    int popolazione;
    struct citt0 *next;
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

// ---- operazioni sulle liste di citta

// stampa le citta della lista lis
void scrivi_lista(citta *lis, FILE *f)
{
    while (lis != NULL)
    {
        scrivi_citta(lis, f);
        fprintf(f, "\n");
        lis = lis->next;
    }
}

// dealloca tutti gli elementi della lista
void distruggi_lista(citta *head)
{
    while (head != NULL)
    {
        citta *prossimo = head->next;
        distruggi_citta(head);
        head = prossimo;
    }
}

// aggiunge citta in cima alla lista lis
citta *aggiungi_citta_head(citta *lis, citta *c)
{
    assert(c != NULL);
    c->next = lis;
    return c;
}

// aggiunge citta' c in fondo alla lista lis
citta *aggiungi_citta_tail(citta *lis, citta *c)
{
    // caso lista vuota
    if (lis == NULL)
    {
        c->next = NULL;
        return c;
    }
    // scorro fino al fondo della lista
    citta *head = lis;
    while (lis->next != NULL)
        lis = lis->next;
    assert(lis->next == NULL);
    lis->next = c;
    c->next = NULL;
    return head;
}

// aggiunge citta nella lista mantenendo l'ordine della popolazione
citta *inserisci_citta_ordinata(citta *lis, citta *c)
{
    assert(c != NULL);
    // controlla se devo inserire in testa
    if (lis == NULL || strcmp(lis->nome,c->nome)<0)
    {
        c->next = lis; // corretto anche quando lis==NULL
        return c;
    }
    // l'inserimento non e' in testa: parto dal secondo elemento
    citta *candidato = lis->next;
    citta *precedente = lis;
    while (candidato != NULL)
    {
        if (strcmp(candidato->nome,c->nome)<0)
            break;
        precedente = candidato;
        candidato = candidato->next;
    }
    assert(precedente != NULL);
    c->next = candidato; // corretto anche quando candidato == NULL
    precedente->next = c;
    return lis;
}

// dato un file costruisce una lista ordinata con le citta in esso contenuto
citta *leggi_lista_da_file(FILE *f)
{
    assert(f != NULL);
    citta *lis = NULL;
    while (true)
    {
        citta *c = leggi_citta_da_file(f);
        if (c == NULL)
            break;
        lis = inserisci_citta_ordinata(lis, c);
        //lis = aggiungi_citta_head(lis,c);
    }
    return lis;
}

// cerco dentro lis una citta' di nome n
// se c'e' restituisco un puntatore ad essa
// alrimenti restituisco null
citta *cerca_citta(citta *lis, char *n)
{
    if (lis == NULL)
        return NULL;
    if (strcmp(lis->nome, n) == 0)
        return lis;
    return cerca_citta(lis->next, n);
}

// merge liste iterativo
citta *merge(citta *lis1, citta *lis2)
{
    if (lis1 == NULL)
        return lis2;
    if (lis2 == NULL)
        return lis1;
    // se sono qui entrambe le liste sono non vuote
    citta *nuova = NULL;
    citta *prossimo = NULL;
    citta *ultimo = NULL;

    while (lis1 != NULL || lis2 != NULL)
    {
        if (lis1 == NULL)
        {
            assert(ultimo != NULL);
            ultimo->next = lis2;
            break;
        }
        else if (lis2 == NULL)
        {
            assert(ultimo != NULL);
            ultimo->next = lis1;
            break;
        }
        else
        {
            assert(lis1 != NULL && lis2 != NULL);
            if (lis1->popolazione < lis2->popolazione)
            {
                prossimo = lis1;
                lis1 = lis1->next;
            }
            else
            {
                prossimo = lis2;
                lis2 = lis2->next;
            }
        }
        // nuova = aggiungi_citta_tail(nuova,prossimo);
        if (nuova == NULL)
            nuova = prossimo;
        else
            ultimo->next = prossimo;
        prossimo->next = NULL;
        ultimo = prossimo;
    }
    return nuova;
}

// merge liste iterativo
citta *merge3(citta *lis1, citta *lis2, citta *lis3)
{

    if (lis1 == NULL)
        return lis3;
    if (lis1 == NULL)
        return lis2;
    if (lis2 == NULL)
        return lis1;
    // se sono qui entrambe le liste sono non vuote
    citta *nuova = NULL;
    citta *prossimo = NULL;
    citta *ultimo = NULL;

    while (lis1 != NULL || lis2 != NULL || lis3 != NULL)
    {
        if (lis1 == NULL)
        {
            assert(ultimo != NULL);
            ultimo->next = merge(lis2, lis3);
            break;
        }
        else if (lis2 == NULL)
        {
            assert(ultimo != NULL);
            ultimo->next = merge(lis1, lis3);
            break;
        }
        else if (lis3 == NULL)
        {
            assert(ultimo != NULL);
            ultimo->next = merge(lis1, lis2);
            break;
        }
        else
        {
            assert(lis1 != NULL && lis2 != NULL && lis3 != NULL);
            if (lis1->popolazione < lis2->popolazione)
            {
                if (lis1->popolazione < lis3->popolazione)
                {
                    prossimo = lis1;
                    lis1 = lis1->next;
                }
                else
                {
                    prossimo = lis3;
                    lis3 = lis3->next;
                }
            }
            else
            {
                if (lis2->popolazione < lis3->popolazione)
                {
                    prossimo = lis2;
                    lis2 = lis2->next;
                }
                else
                {
                    prossimo = lis3;
                    lis3 = lis3->next;
                }
            }
        }
        // nuova = aggiungi_citta_tail(nuova,prossimo);
        if (nuova == NULL)
            nuova = prossimo;
        else
            ultimo->next = prossimo;
        prossimo->next = NULL;
        ultimo = prossimo;
    }
    return nuova;
}

// per casa:
// modificare la fuzione merge_ric in modo che
// effettui i confronti fra le citta utilizzando una
// funzione passata come argomento

// esempi di funzioni che confrontano nomi e popolazioni
int confronta_nomi(citta *a, citta *b)
{
    return strcmp(a->nome, b->nome);
}

int confronta_popolazioni(citta *a, citta *b)
{
    return a->popolazione - b->popolazione ;
}

// merge liste ricorsivo
citta *merge_ric(citta *lis1, citta *lis2)
{
    if (lis1 == NULL)
        return lis2;
    if (lis2 == NULL)
        return lis1;
    // se sono qui entrambe le liste sono non vuote
    citta *prossimo = NULL;
    if (lis1->popolazione < lis2->popolazione)
    {
        prossimo = lis1;
        lis1 = lis1->next;
    }
    else
    {
        prossimo = lis2;
        lis2 = lis2->next;
    }
    prossimo->next = merge_ric(lis1, lis2);
    return prossimo;
}

// merge liste ricorsivo
citta *merge_ric3(citta *lis1, citta *lis2, citta *lis3, int (*compare)(citta*,citta*))
{
    if (lis1 == NULL)
        return lis2;
    if (lis2 == NULL)
        return lis1;
    if (lis3 == NULL)
        return lis1;
    // se sono qui entrambe le liste sono non vuote
    citta *prossimo = NULL;
    if (compare(lis1,lis2)>0)
    {
        if (compare(lis1,lis3)>0)
        {
            prossimo = lis1;
            lis1 = lis1->next;
        }
        else
        {
            prossimo = lis3;
            lis3 = lis3->next;
        }
    }
    else
    {
        if (compare(lis2,lis3)>0)
        {
            prossimo = lis2;
            lis2 = lis2->next;
        }
        else
        {
            prossimo = lis3;
            lis3 = lis3->next;
        }
    }
    prossimo->next = merge_ric3(lis1, lis2, lis3, compare);
    return prossimo;
}

int main(int argc, char *argv[])
{
    // controlla numero argomenti
    if (argc != 4)
    {
        printf("Uso: %s file1 file2 file3\n", argv[0]);
        return 1;
    }
    // prova ad aprire il primo file in lettura
    FILE *f = fopen(argv[1], "rt");
    if (f == NULL)
        die("Impossibile aprire il file1");
    // legge il file
    citta *lis1 = leggi_lista_da_file(f);
    fclose(f);

    // prova ad aprire il primo file in lettura
    f = fopen(argv[2], "rt");
    if (f == NULL)
        die("Impossibile aprire il file2");
    // legge il file
    citta *lis2 = leggi_lista_da_file(f);
    fclose(f);

    // prova ad aprire il primo file in lettura
    f = fopen(argv[3], "rt");
    if (f == NULL)
        die("Impossibile aprire il file2");
    // legge il file
    citta *lis3 = leggi_lista_da_file(f);
    fclose(f);

    // stampa liste su stdout
    puts("------- lista 1 -----");
    scrivi_lista(lis1, stdout);
    puts("------- lista 2 -----");
    scrivi_lista(lis2, stdout);
    puts("------- lista 3 -----");
    scrivi_lista(lis3, stdout);
    citta *lismerge = merge_ric3(lis1, lis2, lis3, confronta_nomi);
    puts("------- lista merge -----");
    scrivi_lista(lismerge, stdout);
    distruggi_lista(lismerge);
    // distruggi_lista(lis1);
    return 0;
}

// stampa messaggio d'errore e termina
void die(char *s)
{
    perror(s);
    exit(1);
}
