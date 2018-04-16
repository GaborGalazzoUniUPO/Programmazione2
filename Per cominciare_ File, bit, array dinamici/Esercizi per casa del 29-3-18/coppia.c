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
  fprintf(f,"%d %d\n",c.x,c.y);
}

void somma_coppie(coppia *c, coppia *d){
	c->x += d->x;
	c->y += d->y;
}

coppia somma_elementi(coppia a[ ], int n){
	coppia c;
	c.x = c.y = 0;
	for(int i = 0; i<n; i++)
		somma_coppie(&c, &a[i]);
	return c;
}

int main(int argc, char *argv[])
{
    // controlla numero argomenti
    if(argc<3 || (argc-1)%2!=0) {
        printf("Uso: %s x1 y1, ... xN yN\n",argv[0]);
        return 1;
    }
	int dim = (argc-1)/2;
    coppia z[dim];
	for(int i = 0; i<dim; i++){
		z[i].x = atoi(argv[i*2+1]);
		z[i].y = atoi(argv[i*2+2]);
	}
	puts("");
    coppia s = somma_elementi(z, dim);
	print_coppia(s, stdout);
    return 0;
}
 
 
 
// stampa messaggio d'errore e termina
void die(char *s)
{
  perror(s);
  exit(1);
}    
    
