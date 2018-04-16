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

    coppia max = max_peso(coppie, num_coppie);
    print_coppia(max, stdout);
    puts("");
    

    return 0;
}