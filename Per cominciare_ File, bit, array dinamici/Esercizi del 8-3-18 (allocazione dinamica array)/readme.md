## Esercizi del 8/3/18 (allocazione dinamica array)

<div class="box generalbox center clearfix">

<div class="no-overflow">

**1)** Scrivere una funzione C

    int max_array(int a[], int n)

che dato un array di interi `a[]` di lunghezza `n>0` restituisce il valore del massimo elemento di `a[]`. Si scriva poi un programma in C `maxa` che invoca la funzione _max_array_ passandogli l'array ottenuto convertendo in interi i valori forniti sulla linea di comando e stampa il valore restituito da _max_array_. Ad esempio:

    maxa 12 -5 3 20 4
    Massimo: 20

Utilizzare la funzione _atoi_ per convertire in interi le stringhe contenute in _argv_ secondo lo schema visto a lezione.

**2)** Scrivere una funzione C

    int *somme_parziali(int a[], int n)

che dato un array di interi `a[]` di lunghezza `n>0` alloca e restituisce un nuovo array `b[]` sempre di lunghezza `n` tale che `b[i] = a[0] + a[1] + ... + a[i]`. Si scriva poi un programma `somme` che invoca _somme_parziali_ passandogli l'array ottenuto convertendo in interi i valori forniti sulla linea di comando e successivamente stampa l'array restituito da _somme_parziali_. Ad esempio:

    somme 1 2
    1 3
    somme 2 3 1 10 -1
    2 5 6 16 15

**3)** Scrivere un programma in C che legge una sequenza di interi sulla linea di comando e stampa il più grande valore che appaia almeno 2 volte. Il programma deve stampare un messaggio di errore se nessun valore appare almeno due volte. Esempi:

<pre>max2v 3 -5 7 2 7 2 2 -5 100 2 1000 -5
-> 7   [solo  7, 2 e -5 appaiono piu' di una volta]
max2v 3 -5 7 -2 17 -5 100 -2 1000 -5
-> -2   [solo -2 e -5 appaiono piu' di una volta]
max2v 100 1000 1 2 3 -4
-> Errore, nessun valore appare almeno 2 volte
</pre>

_Suggerimento:_ per prima cosa si costruisca l'array contenente tutti gli interi passati sulla linea di comando. Successivamente scrivere una funzione

    int *doppi(int a[], int n, int *m)

che dato un array di interi `a[]` restituisce un nuovo array di interi `b[]` contenente gli elementi di `a[]` che appaiono almeno due volte, e calcolare poi il massimo degli elementi di `b[]` utilizzando la funzione _max_array_ dell'esercizio 1.
