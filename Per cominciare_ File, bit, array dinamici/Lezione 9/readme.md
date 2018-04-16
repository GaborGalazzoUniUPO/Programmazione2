## Lezione 9

<div class="box generalbox center clearfix">

<div class="no-overflow">

### Argomenti trattati

*   Abbiamo ripassato l'uso delle funzioni _fwrite_ e _fread_ per scrivere e leggere il contenuto di una variabile o di un array su di un file
*   Abbiamo introdotto l'_aritmetica dei puntatori_: Se _a_ è un array sappiamo che scrivendo _&a[i]_ otteniamo un puntatore alla variabile _a[i]_. Lo stesso puntatore lo si ottiene scrivendo _a+i_ (o anche _i+a_). In altre parole è possibile sommare un puntatore e un intero ottenendo un puntatore.
*   Così come `&a[i]` e `a+i` sono equivalenti, lo sono anche le espressioni `a[i]`, `*(a+i)` e `*(i+a)`. Di conseguenza, se scriviamo`3["ls *"];`non otteniamo un errore in compilazione, ma la risposta alla "domanda fondamentale sulla vita l'universo e tutto quanto". Infatti per l'equivalenza vista sopra: `3["ls * "] = *(3+"ls *") = "ls *"[3] = '*'` e il codice ascii del carattere `*` è effettivamente 42.
*   Abbiamo poi mostrato come leggere delle coppie di numeri da un file di testo memorizzandole in un array. Il problema che non è possibile scoprire in anticipo quante coppie dovremo leggere lo abbiamo risolto ingrandendo l'array quando necessario utilizzando la funzione _realloc_.
*   Abbiamo mostrato diverse versioni di un ciclo _while_ per leggere coppie di interi da un file. Nella prima versione abbiamo usato l'istruzione _break_ per uscire dal ciclo, e abbiamo poi mostrato diversi metodi per eliminare l'istruzione _break_ discutendo vantaggi e svantaggi di ogni soluzione.
*   Abbiamo poi parlato di _stdout_ e _stderr_ due file speciali predefiniti che quando ci scriviamo qualcosa lo visualizzano sul terminale. Ce ne sono due diversi in quanto dalla linea di comando è possibile ridirigere quanto scritto su _stdout_ e/o _stderr_ su un file sul disco invece che sul terminale.
*   Infine abbiamo visto due altre scorciatoie per i _[makefile](https://www.dir.uniupo.it/mod/resource/view.php?id=165949 "makefile")_: quando viene eseguita una regola di compilazione alla variabile `$@` viene sostituito il nome del target, e alla variabile `$?` viene sostituito l'elenco delle dipendenze . Quindi la regola che dice come ottenere l'eseguibile _pippo_ dal sorgente _pippo.c_ la possiamo scrivere:

    pippo: pippo.c
        gcc $(CFLAGS) -o $@ $?

### Esercizi per casa

**1)** Definire una struct

    typedef struct {
      char nome[20];
      char cognome[20];
      int eta;
    } persona;

che rappresenta (alcuni dati di) una [persona](https://www.dir.uniupo.it/mod/resource/view.php?id=165680 "persona"). Analogamente a quanto fatto nel programma _[acoppie](https://www.dir.uniupo.it/mod/resource/view.php?id=165100 "acoppie")_ scrivere due funzioni

    persona crea_persona(char *n, char *c, int e);
    void print_persona(persona, FILE *);

che rispettivamente creano un oggetto di tipo [persona](https://www.dir.uniupo.it/mod/resource/view.php?id=165680 "persona") utilizzando e stampano i dati di una [persona](https://www.dir.uniupo.it/mod/resource/view.php?id=165680 "persona") (in formato testo) su di un file. Nota: dovete usare la funzione _strcpy_ per copiare il contenuto delle stringhe _n[ ]_ e _c[ ]_ all'interno dei campi _nome_ e _cognome_ della struct _[persona](https://www.dir.uniupo.it/mod/resource/view.php?id=165680 "persona")_. Per usare _strcpy_ si deve include _string.h_ (si veda [EsempioStringhe](https://www.dir.uniupo.it/mod/resource/view.php?id=165345 "EsempioStringhe") per un ripasso delel funzioni di manipolazione delle stringhe).

Scrivere poi un main che crea un array di [persone](https://www.dir.uniupo.it/mod/resource/view.php?id=165948 "persone") usando i dati passati sulla linea di comando (_argc-1_ deve essere un multiplo di 3) e che successivamente stampa gli elementi di tale array usando _print_[persona](https://www.dir.uniupo.it/mod/resource/view.php?id=165680 "persona")_.

**2)** Scrivere un programma _leggi_[persone](https://www.dir.uniupo.it/mod/resource/view.php?id=165948 "persone")_ che analogamente a quanto fatto in _leggi_coppie_ crea un array di coppie utilizzando i dati presenti in un file di testo passato come argomento sulla linea di comando. Supponete che il file contenga su ogni riga i dati di una [persona](https://www.dir.uniupo.it/mod/resource/view.php?id=165680 "persona") (quindi due stringhe e un intero).

Scrivere poi una funzione `[persona](https://www.dir.uniupo.it/mod/resource/view.php?id=165680 "persona") piu_giovane([persona](https://www.dir.uniupo.it/mod/resource/view.php?id=165680 "persona") p[], int n)` che dato un array *p[ ]* di *n* [persone](https://www.dir.uniupo.it/mod/resource/view.php?id=165948 "persone") restituisce la più giovane, e a parità di età di la precedenza a quella con il cognome lessicograficamente minore (quindi tra "Carlo Bo 17" "Alda Merini 17" "Arif Aziz 18") deve restituire il [primo](https://www.dir.uniupo.it/mod/resource/view.php?id=163435 "primo"). Usare la funzione *strcmp* per confrontare lessicograficamente i cognomi.

Testare _piu_giovani_ utilizzando l'array costruito dalla prima parte del programma. Nota: il file contenente nomi, cognomi, potete crearlo voi con geany o un altro editor solo testuale (no word o simili).
