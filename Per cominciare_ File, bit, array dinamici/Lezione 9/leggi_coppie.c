#include <stdio.h>    // permette di usare scanf printf
#include <stdlib.h>   // conversioni stringa/numero rand() abs() exit() etc ...
#include <stdbool.h>  // gestisce tipo bool (per variabili booleane)
#include <assert.h>   // permette di usare la funzione assert


// prototipo funzione di terminazione del programma con stampa messaggi d'errore
void die(char *s);

// definisce il tipo coppia composto dalle componenti x e y entrambe intere
typedef struct {
  int x;
  int y;
} coppia;

// definisce il tipo array di coppie 
typedef struct {
  coppia *elementi;
  int size;
} array_coppie;


// restituisce la somma dei valori assoluti delle componenti
int peso(coppia c)
{
  int p = 0;
  p += (c.x>0) ? c.x : -c.x;
  p += (c.y>0) ? c.y : -c.y;
  return p;
}

void print_coppia(coppia c, FILE *f)
{
  fprintf(f,"%d %d",c.x,c.y);
}

coppia crea_coppia_str(char *a, char *b)
{
  coppia c;
  c.x = atoi(a);
  c.y = atoi(b);
  return c;
}

coppia crea_coppia_int( int a,  int b)
{
  coppia c;
  c.x = a;
  c.y = b;
  return c;
}

// funzione che prende come input un file (di testo)
// e resituisce l'array delle coppie lette dal file
array_coppie leggi_coppie_da_file(FILE *f) 
{
  // settare a true per avere messaggi di debug
  bool debug = true;
  // prima inizializzazione array
  int passo = 5;
  int messi = 0;
  int size = 5;
  coppia *a = malloc(size*sizeof(coppia));
  if(a==NULL) die("malloc fallita");
  // ora a[] ha capienza 5 e non contiene elementi
  // size=5  e  messi = 0

  while(true) {
    int c,d,e;
    e = fscanf(f,"%d %d",&c,&d);
    if(debug) fprintf(stderr,"fscanf restituisce: %d\n",e);
    if(e!=2) { // se non leggo 2 valori ho un errore o e'finito il file
      if(e==1) die("Input file non contiene tutte coppie");
      else break;
    }
    // coppia letta correttamente, aggiungiamola all'array
    if(messi>=size) {
      // allargo l'array se necessario
      assert(messi==size);
      size += passo;
      a = realloc(a,size*sizeof(coppia));
      if(a==NULL) die("Errore realloc");
      if(debug) fprintf(stderr, "realloc eseguita\n");
    }
    // ora sono sicuro che nell'array c'e' spazio 
    assert(messi<size);
    a[messi] = crea_coppia_int(c,d);
    messi+=1;
  }
  // rimodifico l'array alla dimensione minima 
  a = realloc(a,messi*sizeof(coppia));
  // restituisco array dentro una variabile di tipo array_coppie
  array_coppie ac;
  ac.elementi = a;
  ac.size = messi;
  return ac;
}

// le righe fra #if 0 e #endif sono ignorate dal compilatore
#if 0
// versioni alternativa del while della funzione precedente 
// senza utilizzare il break

// in questa versione nel test del while assegno alla variabile e l'output 
// di fscanf e contemporaneamente verifico se e' uguale a 2  
  int c,d,e;
  while((e=fscanf(f,"%d %d",&c,&d))==2 ) {
    if(debug) fprintf(stderr,"fscanf restituisce: %d\n",e);
    // coppia letta correttamente, aggiungiamola all'array
    if(messi>=size) {
      // questa parte non cambia
      // allargo l'array se necessario
      assert(messi==size);
      size += passo;
      a = realloc(a,size*sizeof(coppia));
      if(a==NULL) die("Errore realloc");
      if(debug) fprintf(stderr, "realloc eseguita\n");
    }
    // ora sono sicuro che nell'array c'e' spazio 
    assert(messi<size);
    a[messi] = crea_coppia_int(c,d);
    messi+=1;
  }
  // verifica che non abbiamo trovato un intero singolo
  if(e==1) die("Input file non contiene tutte coppie");


// in questa versione uso una variabile aggintiva finito
  bool finito = false;
  while(finito=false) {
    int c,d,e;
    e = fscanf(f,"%d %d",&c,&d);
    if(debug) fprintf(stderr,"fscanf restituisce: %d\n",e);
    if(e!=2) { // se non leggo 2 valori ho un errore o e' finito il file
      if(e==1) die("Input file non contiene tutte coppie");
      else finito=true;
    }
    else {
      // coppia letta correttamente, aggiungiamol all'array
      if(messi>=size) {
        // allargo l'array se necessario
        assert(messi==size);
        size += passo;
        a = realloc(a,size*sizeof(coppia));
        if(a==NULL) die("Errore realloc");
        if(debug) fprintf(stderr, "realloc eseguita\n");
      }
      // ora sono sicuro che nell'array c'e' spazio 
      assert(messi<size);
      a[messi] = crea_coppia_int(c,d);
      messi+=1;
    }
  }
#endif



int main(int argc, char *argv[])
{
    // controlla numero argomenti
    if(argc!=2 ) {
        printf("Uso: %s nome_file\n",argv[0]);
        return 1;
    }
    // prova ad prire il file in lettura
    FILE *f = fopen(argv[1],"rt");
    if(f==NULL) die("Impossibile aprire il file");
    // creo array di coppie
    array_coppie a = leggi_coppie_da_file(f);
    // chiudo il file 
    if(fclose(f)!=0) die("Errore chiusura file");
    
    // scrive coppie sul terminale
    for(int i=0;i<a.size;i++) {
      print_coppia(*(i+a.elementi),stdout);
      puts("");
    }
    // dealloco l'array delle coppie
    free(a.elementi);
    return 0;
}

 
// stampa messaggio d'errore e termina
void die(char *s)
{
  perror(s);
  exit(1);
}    
    
