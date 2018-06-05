#define _GNU_SOURCE  // permette di usare estensioni GNU
#include <stdio.h>   // permette di usare scanf printf
#include <stdlib.h>  // conversioni stringa/numero rand() abs() exit() etc ...
#include <stdbool.h> // gestisce tipo bool (per variabili booleane)
#include <assert.h>  // permette di usare la funzione assert
#include <string.h>  // permette di usare le funzioni per le stringhe strlen, strcmp

// prototipo funzione per terminazione con stampa messaggio d'errore
void die(const char *s);

// esegue il merge di f1 e f2 mettedo il risultato in f
void mergefiles(FILE *dest, FILE *f1, FILE *f2)
{
  rewind(dest);
  rewind(f1);
  rewind(f2);
  char *i1;
  char *i2;
  i1 = NULL;
  i2 = NULL;
  int letti1, letti2;
  size_t n;
  letti1 = getline(&i1, &n, f1);
  letti2 = getline(&i2, &n, f2);

  while (letti1 != -1 || letti2 != -1)
  {
    char *next;
    if (letti1 == -1)
    {
      if(i1!=NULL){
        free(i1);
        i1=NULL;
      }
      next = strdup(i2);
      free(i2);
      i2 = NULL, n = 0;
      letti2 = getline(&i2, &n, f2);
    }
    else if (letti2 == -1)
    {
       if(i2!=NULL){
        free(i1);
        i2=NULL;
      }
      next = strdup(i1);
      free(i1);
      i1 = NULL;
      n = 0;
      letti1 = getline(&i1, &n, f1);
    }
    else if (strcmp(i1, i2) < 0)
    {
      next = strdup(i1);
      free(i1);
      i1 = NULL;
      n = 0;
      letti1 = getline(&i1, &n, f1);
    }
    else
    {
      next = strdup(i2);
      free(i2);
      i2 = NULL;
      n = 0;
      letti2 = getline(&i2, &n, f2);
    }
    if (fputs(next, dest) == -1)
      die("Errore scrittura");
    free(next);
  }
  free(i1);
  free(i2);
}

// ordina gli n interi contenuti in f (4 byte per intero)
void mergesort(FILE *f, int n)
{
  if (n == 1)
    return;
  int n1 = n / 2;
  int n2 = n - n1;
  FILE *f1 = tmpfile();
  FILE *f2 = tmpfile();
  if (f1 == NULL || f2 == NULL)
    die("Creazione file temporanei");
  rewind(f);
  // copio n1 interi da  f a f1
  for (int i = 0; i < n1; i++)
  {
    char *buffer = NULL;
    size_t n = 0;
    if (getline(&buffer, &n, f) == -1)
      die("Errore lettura 1");
    if (fputs(buffer, f1) == -1)
      die("Errore scrittura 1");
    free(buffer);
  }
  // copio n2 interi da  f a f2
  for (int i = 0; i < n2; i++)
  {
    char *buffer = NULL;
    size_t n = 0;
    if (getline(&buffer, &n, f) == -1)
      die("Errore lettura 2");
    if (fputs(buffer, f2) == -1)
      die("Errore scrittura 2");
    free(buffer);
  }
  // chiamate ricorsive
  mergesort(f1, n1);
  mergesort(f2, n2);
  // merge

  mergefiles(f, f1, f2);
  fclose(f1);
  fclose(f2);
  return;
}

int main(int argc, char *argv[])
{
  if (argc != 2)
  {
    printf("Uso: %s nome_file_da_ordinare\n", argv[0]);
    return 1;
  }
  FILE *f = fopen(argv[1], "r+");
  if (f == NULL)
    die("Errore apertura file");
  int num = 0;
  char *b = NULL;
  size_t n = 0;
  while (getline(&b, &n, f) != -1)
    num++;
  rewind(f);
  mergesort(f, num);
  fclose(f);
  free(b);
  return 0;
}

// stampa messaggio d'errore e termina
void die(const char *s)
{
  perror(s);
  exit(1);
}
