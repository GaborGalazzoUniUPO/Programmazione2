Lezione 12
----------

### Argomenti trattati

-   Abbiamo visto un esempio completo di uso della struct *[persona](https://www.dir.uniupo.it/mod/resource/view.php?id=165680 "persona")*, con funzioni per la lettura, scrittura, creazione e distruzione (dei dati di) una [persona](https://www.dir.uniupo.it/mod/resource/view.php?id=165680 "persona"). In tutte le funzioni abbiamo usato puntatori ad oggetti di tipo [persona](https://www.dir.uniupo.it/mod/resource/view.php?id=165680 "persona"), e abbiamo visto la notazione *->* per accedere ad un campo di una struct da un puntatore.

-   Abbiamo visto il concetto di *memory leak*: memoria allocata e non restituita, e abbiamo visto l'uso del tool *valgrind* per verificare che in un programma tuttta la memoria venga correttamente deallocata.

-   Abbiamo visto l'uso di pattern nei *[makefile](https://www.dir.uniupo.it/mod/resource/view.php?id=165949 "makefile")* utilizzando il carattere *%*.

-   Abbiamo iniziato a parlare di *liste* (*linked list* in inglese, *liste collegate* nel vostro libro di testo) descrivendo la loro struttura e confrontando le loro caratteristiche con quelle degli array.

### Esercizio per casa

Partendo da *[persone](https://www.dir.uniupo.it/mod/resource/view.php?id=165948 "persone").c* scrivere un programma che legge un elenco di [persone](https://www.dir.uniupo.it/mod/resource/view.php?id=165948 "persone") da un file di testo memorizzandole in un array di puntatori a [persona](https://www.dir.uniupo.it/mod/resource/view.php?id=165680 "persona"). Successivamente, il programma deve ordinare l'array delle [persone](https://www.dir.uniupo.it/mod/resource/view.php?id=165948 "persone") in ordine di età crescente utilizzando il metodo di ordinamento fatto nell'esercizio 2 del 27/3 (o se volete l'*insertion_sort* fatto per casa la volta scorsa) e infine stampare l'elenco delle [persone](https://www.dir.uniupo.it/mod/resource/view.php?id=165948 "persone") ordinate per età.