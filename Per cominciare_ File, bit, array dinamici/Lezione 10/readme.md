Lezione 10
----------

### Argomenti trattati

-   Le stringhe di lunghezza prefissata sono scomodissime: problem con *scanf*, *strcmp*, esistono modi di leggere al più *n* [caratteri](https://www.dir.uniupo.it/mod/resource/view.php?id=164394 "caratteri") ma è facile confondersi con *\0* e a posteriori spesso si scopre che "serviva una stringa un po' più grande" di quanto prefissato.
-   Le funzioni *scanf* e simili sono scomode per leggere le stringhe perchè bisogna conoscere in anticipo la lunghezza. Usare la versione *%ms* alla quale va passato un puntatore a puntatore a char.
-   Inoltre nella *scanf* la lettura si interrompe quando si incontra uno spazio. In generale useremo quindi per leggere le stringhe da un file la funzione *getline*.

-   Abbiamo dato un una definizione della struct *[persona](https://www.dir.uniupo.it/mod/resource/view.php?id=165680 "persona")* utilizzando i puntatori in modo da non essere vincolati da una lunghezza stringa stabilita a priori:

    ```
     typedef struct {
       char *nome;
       char *cognome;
       int eta;
     } persona;

    ```

-   Abbiamo mostrato come passare il puntatore ad una struct ad una funzione, e iniziato a scrivere funzioni per la creazione, distruzione, stampa, confronto, etc. di [persone](https://www.dir.uniupo.it/mod/resource/view.php?id=165948 "persone") (DA FINIRE NELLA [LEZIONE 12](https://www.dir.uniupo.it/mod/page/view.php?id=165944 "Lezione 12")).