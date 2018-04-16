
/* EsempiStringhe.c sull'utilizzo della libreria string.h */

#include <stdio.h>    // permette di usare scanf printf
#include <stdlib.h>   // conversioni stringa/numero rand() abs() exit() etc ...
#include <stdbool.h>  // gestisce tipo bool (per variabili booleane)
#include <assert.h>   // permette di usare la funzione assert
#include<string.h>    /* libreria che contiene le funzioni sulle strighe: strcmp() */

#define MAX 50      /* Costante che definisce la lunghezza massima della stringa */

int main(int argc, char *argv[])
{

  int i = 0;

  /* Una stringa e' un array di caratteri che contiene una sequenza di caratteri
     che forma la stringa, seguita dal carattere speciale di fine stringa: '\0'. */

  char stringa1[10] = {'p','i','p','p','o','\0'};

  /* Il seguente array di caratteri non non e' una stringha perche' non termina con '\0' */

  char non_stringa1[2] = {'p','i'};

  /* Una stringa puo' essere inizializzata utilizzando una stringa letterale */

  char stringa2[] = "pippo";

  /* Si noti che stringa2 e' un array *statico* di 6 caratteri:
     'p','i','p','p','o','\0' */

  /* E' ovviamente possibile memorizzare una stringa in un array di caratteri
     dinamico */

  char *buffer = malloc(80*sizeof(char));

  /* In questo caso, come per tutti gli array dinamici, non possiamo
     inizializzare l'array contestualmente alla sua creazione */

  /* Possiamo anche scrivere: */

  char *buffer2;
  buffer2 = "pippo";

  /* si noti che con questa assegnazione abbiamo assegnato a buffer2, di tipo
     char*, la stringa costante "pippo", di tipo char * costante. Quindi
     l'istruzione

     buffer2[0] = 't';

     da errore a runtime poiche' stiamo cercando di cambiare un carattere
     dichiarato costante.  */

  /* Per stampare una stringa si deve utilizzare il formattatore "%s" */

  printf("stringa1: %s\n", stringa1);
  printf("non_stringa1: %s\n", non_stringa1);    /* nota: non e' una stringa! */
  printf("stringa2: %s\n", stringa2);
  printf("buffer2: %s\n", buffer2);

  /* Per leggere una stringa si deve utilizzare il formattatore "%s". */

  printf("Inserisci una stringa: ");
  scanf("%s", buffer);

  /* Con questa istruzione viengono letti da input i caratteri in sequenza fino
     a trovare il primo carattere bianco, oppure un tab, un
     interlinea,. ecc. questi carattesi vengono messi denotro il vettore
     buffer, al posto del carattere bianco, ecc, viene posto il carattere
     '\0'. Il vettore deve essere sufficiantemente grande da contenere tutti i
     caratteri letti.  */

  /* Nota non si usa &buffer ma direttamente buffer! questo perche' buffer
     essendo di tipo char* e' gia' un indirizzo!! */

  printf("Hai inserito la stringa: %s\n", buffer);


  /* Per manipolare la stringa si deve accedere ai singoli caratteri
     singolarmente. Ad esempio: */

  while (buffer[i] != '\0') {
    // fai qualcosa con buffer[i], ad esempio
    printf("%c\n", buffer[i]);
    i++;
  }



  /* Per verificare l'uguaglianza tra due stringhe non si puo' usare == perche'
     questo confronta i puntatori.

     Si devono necessariamente scadire le due
     stringhe. E' anche possibile usare la funzione di libreria per le
     stringhe: 

     int strcmp(char* st1, char* st2)

     Che restituisce:
      0  se st1 = st2
      <0 se st2 < st2 (lessicograficamente)
      >0 se st1 > st2 (lessicograficamente)
  */


  char   s1[MAX],   s2[MAX];
  int  dim=0;

  strcpy(s1, "");
  dim = strlen(s1);
  
  printf("\ns1 vale '%s' , la sua lunghezza e' %d\n", s1, dim);

  strcpy(s1, "Ciao");
  dim = strlen(s1);
  printf("\ns1 vale '%s' , la sua lunghezza e' %d\n", s1, dim);

  strcpy(s2, s1);
  strcat(s2, " Carlotta!!");

  dim = strlen(s2);
  printf("\ns2 vale '%s' , la sua lunghezza e' %d\n", s2, dim);


  if (!strcmp(s1,s2))
      printf("\ns1 e' uguale a s2\n");

  if (strcmp(s1,s2) == 0)
      printf("\ns1 e' uguale a s2\n");

  if (strcmp(s1,s2) > 0)
      printf("\ns1 e' maggiore di s2\n");

  if (strcmp(s1,s2) < 0)
    printf("\ns1 e' minore di s2\n");


  return 0;
}