### Esercizi del 20/3/2018

Si consideri la struttura 

[coppia](https://www.dir.uniupo.it/mod/resource/view.php?id=165099) vista a lezione e la funzione 

int peso([coppia](https://www.dir.uniupo.it/mod/resource/view.php?id=165099) c) che data una [coppia](https://www.dir.uniupo.it/mod/resource/view.php?id=165099) restituisce la somma dei moduli delle componenti, anche questa vista a lezione.

**1)**  Si scriva una funzione 

[coppia](https://www.dir.uniupo.it/mod/resource/view.php?id=165099) max_peso([coppia](https://www.dir.uniupo.it/mod/resource/view.php?id=165099) a[], int n) che dato un array _a_ di _n&gt;0_ coppie restituisce la [coppia](https://www.dir.uniupo.it/mod/resource/view.php?id=165099) di peso massimo. Si scriva poi una funzione _main_ che crea un array di coppie leggendo gli elementi dalla linea di comando (fatto questa mattina a lezione), invoca la funzione _max_peso_ e stampa la [coppia](https://www.dir.uniupo.it/mod/resource/view.php?id=165099) da essa restituita.

**2)** Si scriva una funzione 

void scrivi_coppie_bin([coppia](https://www.dir.uniupo.it/mod/resource/view.php?id=165099) a[], int n, FILE *f) che  dato un array _a_ di _n&gt;0_ coppie scrive le coppie sul file _f_ in formato binario (usando 4 byte per ogni intero, quindi 8 byte per ogni [coppia](https://www.dir.uniupo.it/mod/resource/view.php?id=165099) e _8n_ byte in totale). Si usi la funzione _fwrite_ come fatto a lezione nell'esempio _[scrivi_bits](https://www.dir.uniupo.it/mod/resource/view.php?id=164552)_. Si scriva poi una funzione _main_ che crea un array di coppie leggendo gli elementi dalla linea di comando e le scrive su file invocando _scrivi_coppie_bin_ (il nome del file deve essere passato anch'esso sulla linea di comando).

**3)** Si scriva un programma in C che legge dalla linea
 di comando il nome di un file binario (generato dal programma 
dell'esercizio precedente),  crea un array di coppie leggendo i dati dal
 file nel formato dell'esercizio precedente, e stampa la [coppia](https://www.dir.uniupo.it/mod/resource/view.php?id=165099) di peso massimo utilizzando la funzione _max_peso_ definita nell'esercizio 1.