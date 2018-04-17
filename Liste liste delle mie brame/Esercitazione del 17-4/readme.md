Esercitazione del 17/4
----------------------

**1)** Definire la struct

```
typedef struct sq {
  char *nome;
  int punti;
  struct sq *next;
} squadra;

```

che rappresenta una squadra e il suo punteggio. Si vuole mantenere una lista delle squadre che partecipano al campionato ordinate lessicograficamente. Si definisca la funzione:

```
squadra *aggiungi_punti(squadra *lis, char n[], int p)

```

che aggiunge alla squadra di nome *n* esattamente *p* punti. Se la lista *lis* contiene già la squadra di nome *n* si deve semplicemente aumentare di *p* il suo punteggio; se invece *lis* non contiene tale squadra essa deve essere creata e gli deve essere assegnato il punteggio *p*. Si ricordi che dentro *lis* le squadre devono sempre essere ordinate lessicograficamente. Inoltre, quando viene creato un oggetto di tipo *squadra* la stringa contente il nome deve essere allocata con *malloc* e il contenuto di *n* copiato con la funzione *strcpy*.

Per testare questa prima parte dell'esercizio, mettere nel main le seguenti istruzioni:

```
squadra *classifica = NULL;
classifica = aggiungi_punti(classifica,"Juve",1);
classifica = aggiungi_punti(classifica,"Chievo",3);
classifica = aggiungi_punti(classifica,"Milan",1);
classifica = aggiungi_punti(classifica,"Juve",3);
classifica = aggiungi_punti(classifica,"Spal",1);
classifica = aggiungi_punti(classifica,"Milan",1);
classifica = aggiungi_punti(classifica,"Roma",3);
scrivi_lista(classifica,stdout); // da scrivere in analogia a quanto fatto per le citta'
distruggi_lista(classifica);     // da scrivere in analogia a quanto fatto per le citta'

```

che dovrebbero produrre un output del tipo

```
Chievo: 3
Juve: 4
Milan: 2
Roma: 3
Spal: 1

```

**2)** Aggiungere al programma precedente una funzione

```
squadra *aggiungi_partita(squadra *classifica, char s1[], int g1, char s2[], int g2)

```

e considera i parametri passati come il risultato di una partita nella quale la squadra *s1* ha fatto *g1* gol, e la squadra *s2* ha fatto *g2* gol. La classifica deve essere di conseguenza aggiornata (usando *aggiungi_punti*) assegnando 1 o 3 punti a *s1* e/o *s2* e la nuova classifica restituita via return.

Scrivere poi una funzione main che legge il nome di un file da linea di comando, apre il file in lettura e legge ripetutamente il risultato di una partita con l'istruzione

```
fscanf(f, "%d %d %ms %ms",&g1, &g2, &s1, &s2)

```

(stiamo assumendo che i nomi delle squadre non contengano spazi) e provvede ad aggiornare la classifica usando *aggiungi_partita*. Quando non è più possibile leggere risultati dal file, il programma deve stampare la classifica ordinata per punteggio decrescente.

**3)** Aggiornare alla struttura *squadra* i campi *gol_fatti* e *gol_subiti* e fare in modo che *aggiungi_partita* aggiorni anche questi capi e che i gol fatti e subiti siano visualizzati nella classifica finale.