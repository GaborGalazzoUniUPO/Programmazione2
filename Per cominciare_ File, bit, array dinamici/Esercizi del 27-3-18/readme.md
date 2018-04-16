Esercizi del 27/3/18
--------------------

Negli esercizi **1** e **2** si deve partire dal programma *leggi_coppie* fatto a lezione la settimana scorsa che legge da un file un insieme di coppie e le memorizza in un array.

**1)** Si scriva una funzione *int cmp_coppie([coppia](https://www.dir.uniupo.it/mod/resource/view.php?id=165099 "coppia") *a, [coppia](https://www.dir.uniupo.it/mod/resource/view.php?id=165099 "coppia") *b)* che dati i puntatori a due coppie restiuisce -1 se la prima [coppia](https://www.dir.uniupo.it/mod/resource/view.php?id=165099 "coppia") ha un peso minore della seconda, 0 se hanno lo stesso peso, 1 se la prima [coppia](https://www.dir.uniupo.it/mod/resource/view.php?id=165099 "coppia") ha un peso maggiore della seconda. Si scriva poi *int posizione_massimo([coppia](https://www.dir.uniupo.it/mod/resource/view.php?id=165099 "coppia") arr[ ], int n)* che dato un array *arr[ ]* di coppie utilizza la funzione *cmp_coppie* per calcolare e restituire la posizione dell'array *arr[]* dove si trova la [coppia](https://www.dir.uniupo.it/mod/resource/view.php?id=165099 "coppia") di peso massimo. Si scriva infine un *main()* che dopo aver letto le coppie come in *leggi_coppie* utilizza *posizione_massimo* per calcolare e stampare sul terminale la posizione della [coppia](https://www.dir.uniupo.it/mod/resource/view.php?id=165099 "coppia") di peso massimo.

**2)** Si scriva una funzione

```
void sposta_coppia_massima(coppie arr[], int n)

```

che dato un array *arr[ ]* di almeno *n>0* coppie mette in fondo all'array (quindi nella posizione *n-1*) scambiandola con la [coppia](https://www.dir.uniupo.it/mod/resource/view.php?id=165099 "coppia") che si trova in quella posizione. Ad esempio se

```
arr[] = {(2,3), (4,5), (7,0), (-2,4), (2,0)}

```

*sposta_[coppia](https://www.dir.uniupo.it/mod/resource/view.php?id=165099 "coppia")_massima* deve usare *posizione_massimo* per trovare l'indice della [coppia](https://www.dir.uniupo.it/mod/resource/view.php?id=165099 "coppia") di peso massimo --- in questo caso 1, in quanto *arr[1]=(4,5)* --- e successivamente deve scambiare di posto le coppie nelle posizioni 1 e 4 di *arr[ ]* in modo che si abbia

```
arr[ ] = {(2,3), (2,0), (7,0), (-2,4), (4,5)}

```

Si scriva poi una funzione

```
void ordina_coppie(coppia arr[], int n)

```

che dato un array *arr[]* di *n>0* coppie le ordina per peso crescente. Quindi se inizialmente

```
arr[] = {(2,3), (4,5), (7,0), (-2,4), (2,0)}

```

al termine di *ordina_coppie* deve essere

```
arr[] = {(2,0), (2,3),(-2,4), (7,0), (4,5)}

```

L'ordinamento deve essere ottenuto chiamando *n-1* volte la funzione *sposta_[coppia](https://www.dir.uniupo.it/mod/resource/view.php?id=165099 "coppia")_massima*. Nell'esempio, dopo la prima invocazione deve essere:

```
arr[ ] = {(2,3), (2,0), (7,0), (-2,4), (4,5)}

```

dopo la seconda

```
arr[ ] = {(2,3), (2,0), (-2,4), (7,0), (4,5)}

```

e così via. Si noti che anche se un array ha *n* elementi, posso chiamare *sposta_[coppia](https://www.dir.uniupo.it/mod/resource/view.php?id=165099 "coppia")_massima* passandogli una lunghezza minore di *n*.

Si scriva poi un *main* che legge un array di coppie da un file, lo ordina con *ordina_coppie* e visualizza sul terminale l'array ordinato.

**3)** Scrivere due funzioni *sposta_stringa_massima* e *ordina_stringhe* che svolgono le operazioni viste precedenti su un array di stringhe (quindi puntatori a [caratteri](https://www.dir.uniupo.it/mod/resource/view.php?id=164394 "caratteri")) invece che su un array di coppie. Usare la funzione *strcmp* per confrontre le stringhe invece della *cmp_coppie* usata per confrontare le coppie.

Scrivere poi un *main* che invoca *ordina_stringhe* sull'array di stringhe *argv* e visualizza sul terminale l'elenco delle stringhe ordinato.