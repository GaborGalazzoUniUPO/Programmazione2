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

//dato un array a di n>0 coppie scrive le coppie sul file f in formato binario
bool scrivi_coppie_bin(coppia a[], int n, FILE *fp){
    assert(n>0);
    return fwrite(a,sizeof(coppia), n, fp) == n;
}

int main(int argc, char* argv[]){
    if((argc-2)%2!=0 || argc -2 < 2){
        printf("usage: %s nome_file x0 y0 x1 y1 ... xn yn\n", argv[0]);
        return 1;
    }
    int num_coppie = (argc-1)/2;
    coppia coppie[num_coppie];
    for(int i=0;i<num_coppie;i++) {
      coppie[i] = crea_coppia_str(argv[2*i+2],argv[2*i+3]);
    }
    FILE* fp = NULL;
    if((fp = fopen(argv[1], "wb")) == NULL) die("ERRORE nell'apertura del file");
    if(!scrivi_coppie_bin(coppie, num_coppie, fp)) die("ERRORE nella scrittura del file");
    if(fclose(fp)) die("ERRORE nella chiusura del file");
    

    return 0;
}