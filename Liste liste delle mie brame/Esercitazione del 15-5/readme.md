Esercitazione del 15/5
----------------------

Si consideri la struct

```
typedef struct {
  double lat;
  double lon;
} coordinate;

typdef struct {
  char *nome;
  coordinate coord;
} citta;

```

**1)** Utilizzando il codice visto a lezione scrivere un programma che legge il file [capitali.txt](https://www.dir.uniupo.it/mod/resource/view.php?id=168513 "capitali.txt") contenente nomi di città con le loro coordinate geografiche, e con il suo contenuto crea un array di `citta *` (potete usare i file [coordinate.c](https://www.dir.uniupo.it/mod/resource/view.php?id=169014 "coordinate.c") [coordinate.h](https://www.dir.uniupo.it/mod/resource/view.php?id=169015 "coordinate.h") [citta.c](https://www.dir.uniupo.it/mod/resource/view.php?id=169012 "citta.c") e [citta.h](https://www.dir.uniupo.it/mod/resource/view.php?id=169013 "citta.h") visti oggi a lezione).

**2)** Scrivere una funzione `void stampa_array_genrico(void *a[ ], int n, void (*stampa)(void *, FILE *), FILE *f)` prende in input un array *a[ ]* di puntatori a void e la sua lunghezza *n*, e chiama la funzione `stampa` su tutti gli elementi dell'array passando come secondo argomento alla funzione `stampa` il file *f*. Si usi poi la funzione `stampa_array_generico` per stampare su *stderr* tutti gli elementi dell'array di città costruito al punto 1. Per fare questo è necessario passare a `stampa_array_generico` una funzione `stampa_citta(void *a, FILE *f)` che trasforma il puntatore a void *a* in un puntatore a città, con un casting, e scrive il suo nome e coordinate nel file *f*.

**3)** Scrivere una funzione `void ordina_per distanza(citta *a[], int n, citta *o)` che dato un array di puntatori a città *a[ ]*, la sua lunghezza *n*, e il puntatore ad una città *o* esegue l'ordinamento delle città di *a[ ]* sulla base della distanza dalla città *o*. Successivamente scrivere un main che invoca `ordina_per_distanza` sull'array letto al punto **1)** passando come parametro *o* le città

```
Novosibirsk 54.990145, 82.919166
Sidney -33.857251 151.208747
Waterloo 50.717469 4.397911

```

e stampi i rispettivi [risultati](https://www.dir.uniupo.it/mod/resource/view.php?id=167144 "risultati").