Esercitazione del 24/4
----------------------

**1)** Si scriva una funzione

```
citta *merge3(citta *lis1, citta *lis2, citta *lis3)

```

che date tre liste di città ordinate per popolazione crescente restituisce la lista contenente tutte le città ordinate per popolazione crescente. La funzione deve operare in maniera simile alla funzione merge del file *[merge_liste](https://www.dir.uniupo.it/mod/resource/view.php?id=167340 "merge_liste").c* tranne che ad ogni iterazione vanno confrontati fino a tre elementi (uno per lista) e il minore viene messo in fondo alla lista risultato. Scrivere poi una funzione main che prende in input sulla linea di comando il nome di tre file, li legge creando tre liste ordinate, chiama la procedura *merge3*, e stampa la lista risultato.

**2)** Come l'esercizio precedente, ma eseguire il merge delle tre liste con una funzione ricorsiva

```
citta *merge3_ric(citta *lis1, citta *lis2, citta *lis3, int (*f)(citta *a, citta *b))

```

che utilizza la funzione *f* per confrontare le città. Ad esempio, per ordinare le città in ordine lessicografico la funzione da usare per confrontare le città deve essere

```
int confronta_nomi(citta *a, citta *b)
{
  return strcmp(a->nome,b->nome);
}

```

**3)** Partendo dal codice in *[merge_array](https://www.dir.uniupo.it/mod/resource/view.php?id=167341 "merge_array").c* scrivere una funzione

```
void mergesort(citta *a[], int n)

```

che dato un array *a* di *n* puntatori a città lo ordina utilizzando la seguente strategia ricorsiva:

-   Se *n<2*, l'array è già ordinato e non c'è nulla da fare
-   Se *n >= 2*, si pone *i = n/2* e si considera separatamente le due metà *a[0], a[1], ..., a[i-1]* e *a[i], a[i+1], ..., a[n-1]*. Notare che la prima metà parte dall'elemento *a[0]* e contiene $i$ elementi, mentre la seconda metà parte dell'elemento *a[i]* e contiene $n-i$ elementi.
-   Si utilizza la ricorsione per ordinare separatamente le due metà, e successivamente si usa la procedura

```
citta **merge_array(citta *a1[], int n1, citta *a2[], int n2, int *n3)

```

vista a lezione per effettuare il merge delle due metà.

Scrivere poi una funzione main che prende in input sulla linea di comando il nome di un file di città, ne copia il contenuto in un array, ordina l'array con *mergesort*, e stampa il risultato.