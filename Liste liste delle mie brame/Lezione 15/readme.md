Lezione 15
----------

### Argomenti trattati

-   Abbiamo mostrato una funzione per la ricerca di un elemento all'interno della lista

-   Abbiamo considerato il problema della cancellazione di un elemento all'interno di una lista, osservando che è necessario mantenere anche il puntatore all'elemento precedente a quello corrente per effettuare la cancellazione. Abbiamo mostrato l'uso di un puntatore a puntare per restituire alla funzione chiamante l'elemento eliminato dalla lista.

-   Abbiamo considerato il problema dell'inserimento di un elemento in una lista ordinata, rispettando l'ordinamento. Anche in questo caso abbiamo visto che è necessario utilizzare due puntatori quando si scorre la lista.

-   Le funzioni fatte a lezione sono disponibili nel file *[ins_canc](https://www.dir.uniupo.it/mod/resource/view.php?id=166688 "ins_canc").c*

### Esercizio per casa

Scrivere un programma *ordina* che invocato sulla linea di comando scrivendo:

```
ordina nomefile

```

legge gli interi in formato testo da `nomefile` salvandoli in una lista di interi ordinata, e successivamente scrive gli interi ordinati nel file `nomefile.ordinati` (fa parte dell'esercizio creare il nome del file di output uguale al nome del file di input con l'estensione `.ordinati`).

Dopo aver creato il file di output, il programma deve rileggere gli interi da `nomefile` e dopo aver letto ogni intero cancellare il relativo elemento dalla lista. Verificare con *valgrind* che tutta la memoria venga correttamente deallocata.

Per la realizzazione potete fare riferimento al sorgente *[ins_canc](https://www.dir.uniupo.it/mod/resource/view.php?id=166688 "ins_canc").c*, utilizzando una lista di interi invece di una lista di città, ma provate a realizzare da soli le funzioni per la cancellazione e l'inserimento nella lista ordinata.

Se python3 è installato sul vostro computer potete creare il file *cento* con gli interi da 0 a 99 in ordine causale eseguendo la linea di comando:

```
python3 -c "import random; a = list(range(100)); random.shuffle(a); list(map(print, a))" > cento

```