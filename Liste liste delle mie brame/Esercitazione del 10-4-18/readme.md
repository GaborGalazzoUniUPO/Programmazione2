Esercitazione del 10/4
----------------------

Nel file *lista_citta.c* trovate la definizione del tipo *citta* e alcune funzioni base per la allocazione, lettura, scrittura, deallocazione di oggetti che rappresentano una città.

Aggiungere al file le seguenti funzioni

```
// aggiunge citta c in cima alla lista lis
citta *aggiungi_citta_head(citta *lis, citta *c);

// dato un file costruisce una lista con le citta in esso contenuto
citta *leggi_lista_da_file(FILE *f);

// restituisce la somma delle popolazioni delle citta nella lista
int somma_pop_lista_citta(citta *lista);

// restituisce il numero di citta' con popolazione tra minp e maxp
int conta_citta_in_range(citta *lista, int minp, int maxp);

// aggiunge citta' c in fondo alla lista lis; restiuisce la lista modificata
citta *aggiungi_citta_tail(citta *lis, citta *c);

// esegue il reverse della lista
citta *reverse(citta *lis);

```

Il file contiene un *main* per eseguire un po' di test di queste funzioni. Utilizzzare il file *[cities](https://www.dir.uniupo.it/mod/resource/view.php?id=166364 "cities").txt* come input del programma.