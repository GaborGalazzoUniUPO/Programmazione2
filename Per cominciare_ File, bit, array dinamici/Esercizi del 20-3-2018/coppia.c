#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

typedef struct {
    int x;
    int y;
} coppia;

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

int main(int argc, char* argv[]){
    if((argc-1)%2!=0 || argc - 1 <2){
        printf("usage: %s x0 y0 x1 y1 ... xn yn\n", argv[0]);
        return 1;
    }
    int num_coppie = (argc-1)/2;
    coppia coppie[num_coppie];
    for(int i=0;i<num_coppie;i++) {
      coppie[i] = crea_coppia_str(argv[2*i+1],argv[2*i+2]);
    }
    coppia max = max_peso(coppie, num_coppie);
    print_coppia(max, stdout);
    puts("");

    return 0;
}