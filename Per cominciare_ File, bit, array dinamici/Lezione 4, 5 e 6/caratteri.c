#include <stdio.h>    // permette di usare scanf printf
#include <stdlib.h>   // conversioni stringa/numero rand() abs() exit() etc ...
#include <stdbool.h>  // gestisce tipo bool (per variabili booleane)
#include <assert.h>   // permette di usare la funzione assert




int main(int argc, char *argv[])
{
    // controlla numero argomenti
    if(argc!=2) {
        printf("Uso: %s numero_positivo_minore_di_128\n",argv[0]);
        return 1;
    }
    // converto in intero
    int i = atoi(argv[1]);
    printf("Inserito il valore %d\n",i);
    if(i<0 || i>=128) {
      printf("Valore non valido\n");
      exit(1);
    }
    char c = i;
    printf("Come intero: %d, come carattere: %c\n",c,c);
    // gia che ci siamo verifichiamo quanto sono grandi le variabili
    printf("Un char: %d bytes\n",sizeof(char));
    printf("Un int: %d bytes\n",sizeof(int));
    printf("Un puntatore a char: %d bytes\n",sizeof(char *));
    printf("Un puntatore a int: %d bytes\n",sizeof(int *));
    return 0;
    
}

