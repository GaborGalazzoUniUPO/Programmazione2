## Esercizi per casa del 15/3/18

<div class="box generalbox center clearfix">

<div class="no-overflow">

**1)** Scrivere una funzione

    int conta_uni(int n)

che dato un intero _n_ restituisce il numero di bit 1 all'interno della sua rappresentazione binaria. Per il calcolo utilizzare le operazioni su bit **&**, **|** e **<<** viste a lezione. Scrivere poi un _main_ che invoca _conta_uni_ passandogli come argomento un intero passato sulla linea di comando e stampa il risultato ottenuto.

**2)** Scrivere un programma _converti_ che legge dalla linea di comando una sequenza di stringhe contenenti solo 0 e 1 e stampa gli interi ottenuti convertendo le sequenze di bit. Ad esempio:

    converti 011 1001 1 1111 100000000

deve produrre i valori 3, 17, 1, 15, 512\. Si verifichi che le singole stringhe siano lunghe al massimo 32 cara<span></span>tteri e di conseguenza gli interi possano essere rappresentati in una variabile di tipo _int_.

**3)** Scrivere un programma _scrivi_interi_ che invocato dalla linea di comando nella forma

    scrivi_interi nomefile 23 0 45 51 -1

crea un file di nome _nomefile_ contenente la sequenza di bit contenuti degli interi passati sulla linea di comando. Si memorizzi ognuno degli interi sulla linea di comando in una variabile di tipo _int_ e di conseguenza il file creato dovrebbe avere una dimensione in byte pari a 4 volte il numeri di interi sulla linea di comando (nell'esempio 20 byte). _Suggerimento:_ si crei un array di interi contenete i valori passati sulla linea di comando e lo scriva nel file utilizzando la funzione _fwrite_.

Si scriva poi un programma _leggi_interi_ che legge il nome di un file dalla linea di comando e stampa gli interi in esso contenuto (si dovrebbero quindi riotttenere i valori passati sulla linea di comando a _scrivi_interi_).