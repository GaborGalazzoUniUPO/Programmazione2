#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>

typedef struct {
    int x;
    int y;
} coppia;

// definisce il tipo array di coppie 
typedef struct {
  coppia *elementi;
  int size;
} array_coppie;


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

void print_coppia(coppia c, FILE *f)
{
  fprintf(f,"%d %d\n",c.x,c.y);
}

// stampa messaggio d'errore e termina
void die(char *s)
{
  perror(s);
  exit(1);
}   

//data una coppia restituisce la somma dei moduli delle componenti
int peso(coppia c){
    return abs(c.x)+abs(c.y);
}

//dato un array a di n>0 coppie restituisce la coppia di peso massimo.
coppia max_peso(coppia a[], int n){
    assert(n>0);
    coppia max = a[0];
    for(int i = 1; i<n; i++){
        if(peso(a[i])>peso(max))
            max = a[i];
    }
    return max;
}

//dati i puntatori a due coppie restiuisce -1 se la prima coppia ha un peso minore della seconda, 
//0 se hanno lo stesso peso, 1 se la prima coppia ha un peso maggiore della seconda
int cmp_coppie(coppia *a, coppia *b){
    if(peso(*a)>peso(*b))
        return 1;
    if(peso(*a)<peso(*b))
        return -1;
    return 0;
}

// dato un array arr[ ] di coppie utilizza la funzione cmp_coppie per calcolare e 
//restituire la posizione dell'array arr[] dove si trova la coppia di peso massimo
int posizione_massimo(coppia arr[ ], int n){
    assert(n>0);
    int max = 0;
    for(int i = 1; i<n; i++){
        if(peso(arr[i])>peso(arr[max]))
            max = i;
    }
    return max;
}

// dato un array arr[ ] di almeno n>0 coppie mette
// in fondo all'array (quindi nella posizione n-1) scambiandola 
// con la coppia che si trova in quella posizione
void sposta_coppia_massima(coppia arr[], int n){
    assert(n>0);
    int max = posizione_massimo(arr, n);
    coppia tmp = arr[n-1];
    arr[n-1] = arr[max];
    arr[max] = tmp;
}

// dato un array arr[] di n>0 coppie le ordina per peso crescente.
void ordina_coppie(coppia arr[], int n){
    for(int i = 0; i<n; i++){
        sposta_coppia_massima(arr, n-i);
    }
}

// funzione che prende come input un file (di testo)
// e resituisce l'array delle coppie lette dal file
array_coppie leggi_coppie_da_file(FILE *f) 
{
  // settare a true per avere messaggi di debug
  bool debug = false;
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

int main(int argc, char* argv[]){
     // prova ad prire il file in lettura
    FILE *f = fopen(argv[1],"rt");
    if(f==NULL) die("Impossibile aprire il file");
    // creo array di coppie
    array_coppie a = leggi_coppie_da_file(f);
    // chiudo il file 
    if(fclose(f)!=0) die("Errore chiusura file");
    
    int pos = posizione_massimo(a.elementi, a.size);
    // scrive coppie sul terminale
    printf("POSIZIONE: %d\n", pos);
    // dealloco l'array delle coppie
    free(a.elementi);
    return 0;
}