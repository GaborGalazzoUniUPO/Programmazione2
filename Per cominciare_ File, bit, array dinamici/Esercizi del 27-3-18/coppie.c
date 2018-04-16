#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>

typedef struct {
    int x;
    int y;
} coppia;

coppia crea_coppia(int x, int y){
    coppia c;
    c.x = x;
    c.y = y;
    return c;
}

coppia crea_coppia_str(char* x, char* y){
    coppia c;
    c.x = atoi(x);
    c.y = atoi(y);
    return c;
}

void print_coppia(coppia c, FILE *f)
{
  fprintf(f,"%d %d",c.x,c.y);
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

int file_dim(FILE* fp){
    int old = ftell(fp);
    fseek(fp, 0, SEEK_END);
    int dim = ftell(fp);
    fseek(fp, old, SEEK_SET);
    return dim;
}

int main(int argc, char* argv[]){
     if(argc!=2){
        printf("usage: %s nome_file\n", argv[0]);
        return 1;
    }
   
    FILE* fp = NULL;
    if((fp = fopen(argv[1], "rb")) == NULL) die("ERRORE nell'apertura del file");
    
    int num_coppie = file_dim(fp)/sizeof(coppia);
    coppia coppie[num_coppie];

    fread(coppie, sizeof(coppia), num_coppie, fp);

    if(fclose(fp)) die("ERRORE nella chiusura del file");

    int max = posizione_massimo(coppie, num_coppie);
    print_coppia(coppie[max], stdout);
    printf("\nPOSIZIONE %d\n", max);
    

    return 0;
}