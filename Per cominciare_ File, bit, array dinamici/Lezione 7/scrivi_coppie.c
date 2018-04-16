#include <stdio.h>    // permette di usare scanf printf
#include <stdlib.h>   // conversioni stringa/numero rand() abs() exit() etc ...
#include <stdbool.h>  // gestisce tipo bool (per variabili booleane)
#include <assert.h>   // permette di usare la funzione assert


void die(char *s);

// definisce il tipo coppia composto dalle componenti x e y entrambe intere
typedef struct {
  int x;
  int y;
} coppia;


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


int main(int argc, char *argv[])
{
    // controlla numero argomenti
    if((argc-2)%2!=0 || (argc-2)<2 ) {
        printf("Uso: %s nomefile x0 y0 x1 y1 ... xk yk\n",argv[0]);
        return 1;
    }
    int n = (argc-2)/2;
    assert(n>0);
    // creo array di n coppie
    coppia a[n]; // oppure: coppia *a = malloc(n*sizeof(coppia));
    // legge coppie da linea di comando
    for(int i=0;i<n;i++) {
      a[i] = crea_coppia_str(argv[2*i+2],argv[2*i+3]);
    }
    // apro il file dove scrivere le coppie
    FILE *f = fopen(argv[1],"at");
    if(f==NULL) die("Impossibile aprire il file");
    
    // scrive coppie nel file 
    for(int i=0;i<n;i++) {
      print_coppia(a[i],f);
      fputs("\n",f);
    }
    if(fclose(f)!=0) die("Errore chiusura file");
    return 0;
}
 
 
 
// stampa messaggio d'errore e termina
void die(char *s)
{
  perror(s);
  exit(1);
}    
    
