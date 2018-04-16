Esercizi per casa del 29/3/18
-----------------------------

La procedura per l'ordinamento di un array che avete realizzato martedì in laboratorio è chiamata *bubble sort* in quanto ad ogni iterazione il valore più grande risale verso l'alto come una bolla. Si noti che ad ogni passaggio l'array su cui si lavora diventa più piccolo mano a mano che "sistemiamo" gli elementi più grandi.

L'esercizio di oggi consiste nel realizzare un altro metodo di ordinamento, chiamato *insertion sort* che procede in maniera opposta: parte da un array di 1 elemento e inserisce un elemento alla volta mantenendo gli elementi ordinati. Quando anche l'ultimo elemento è stato inserito avremo realizzato l'ordinamento.

Per prima cosa è necessario scrivere un funzione *inserisci*. Dato un array *a[ ]* di *n>1* elementi tale che i primi *n-1* elementi sono ordinati:

a[0]≤a[1]≤⋯≤a[n-2]

la funzione *inserisci* deve spostare il valore *a[n-1]* all'interno di *a[ ]* in modo di mantenere l'ordinamento. Ad esempio se inizialmente *a= [2, 8, 13, 15, 10]* al termine dell'esecuzione di *inserisci(a,5)* si deve avere *a=[2,8,10,13,15]*. Per realizzare questo il valore 15 deve essere stato copiato da *a[3]* ad *a[4]*, il valore 13 da *a[2]* a *a[3]* e il valore 10 deve essere stato scritto in *a[2]*.

**1)** Si scriva una funzione in C

```
void inserisci(int a[ ], int n)

```

che dato un array di *n>0* interi svolga quanto descritto sopra. La funzione deve essere realizzata utilizzando solamente un ciclo *for*, dovete solamente stare attenti a non sovrascrivere gli elementi.

Se *insert* è scritta correttamente, la funzione

```
void insertion_sort(int a[ ], int n) {
  for(int i=2;i<= n; i++) {
    inserisci(a,i);
    stampa_array(a,n); // questa dovete scriverla voi
  }
}

```

se invocata con *a = [23, 10, 20, 25, 12]* dovrebbe stampare

**10** 23 20 25 12

10 **20** 23 25 12

10 20 23 **25** 12

10 **12** 20 23 25

dove ho evidenziato in bold l'elemento che è stato sistemato ad ogni iterazione. Notate che al termine di *insertion_sort* l'array è ordinato.

Si scriva poi un main che esegua il test di *insertion_sort* passandogli l'array di interi ottenuto convertendo gli argomenti passati sulla linea di comando.

**2)** Si scriva una funzione

```
void inserisci_stringhe(char *a[ ], int n)

```

che esegua le operazioni viste prima lavorando però con un array di stringhe e confrontando le stringhe utilizzando la funzione *strcmp* vista a lezione.

Si scriva poi una funzione *insertion_sort_stringhe* che ordina un array di stringhe chiamando *inserisci_stringhe* come visto per gli interi, e la si testi facendole ordinare le stringhe passate come argomenti sulla linea di comando.

**3)** Tornando all'esempio sulle coppie, scrivere una funzione

```
void somma_coppie(coppia *c, coppia *d)

```

che dato il puntatore a due coppie esegue la somma delle componenti *x* e *y* e le memorizza in *c*. Quindi se *c=(2,3)* e *d=(5,8)* dopo la chiamata

```
somma_coppie(&c, &d);

```

deve essere *c=(7,11)* e *d* rimanere invariata.

Utilizzare la funzione *somma_coppie* per scrivere una funzione

```
coppia somma_elementi(coppia a[ ], int n)

```

che dato un array di *n* coppie restituisce la [coppia](https://www.dir.uniupo.it/mod/resource/view.php?id=165099 "coppia") contenete la somma di tutte le componenti *x* e di tutte le componenti *y*.

Quindi se

```
arr[] = {(2,3), (4,5), (7,0), (-2,4), (2,0)}

```

la chiamata

```
somma_elementi(arr, 5)

```

deve restituire la [coppia](https://www.dir.uniupo.it/mod/resource/view.php?id=165099 "coppia") *(13, 12)*

**Nota:** ho volutamente mischiato tra loro funzioni che lavorano con il tipo *[coppia](https://www.dir.uniupo.it/mod/resource/view.php?id=165099 "coppia")* e *[coppia](https://www.dir.uniupo.it/mod/resource/view.php?id=165099 "coppia") **, è importante che sappiate usarli correttamente entrambi.