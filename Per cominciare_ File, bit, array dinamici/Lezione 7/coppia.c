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

// funzione che restituisce una nuova coppia con elementi doppi 
// rispetto alla coppia passata
coppia raddoppia(coppia c)
{
  coppia d;
  
  d.x = 2*c.x;
  d.y = 2*c.y;
  return d;
}

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

int main(int argc, char *argv[])
{
    // controlla numero argomenti
    if(argc!=3) {
        printf("Uso: %s x y\n",argv[0]);
        return 1;
    }
    coppia z;
    z.x = atoi(argv[1]);
    z.y = atoi(argv[2]);
    coppia w = raddoppia(z);
    int p = peso(z);
    printf("Coppia doppia: ");
    print_coppia(w,stdout);
    printf("\n");
    printf("Peso: %d\n",p);
    return 0;
}
 
 
 
// stampa messaggio d'errore e termina
void die(char *s)
{
  perror(s);
  exit(1);
}    
    
