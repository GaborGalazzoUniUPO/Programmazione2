#define _GNU_SOURCE  // permette di usare estensioni GNU
#include <stdio.h>   // permette di usare scanf printf
#include <stdlib.h>  // conversioni stringa/numero rand() abs() exit() etc ...
#include <stdbool.h> // gestisce tipo bool (per variabili booleane)
#include <assert.h>  // permette di usare la funzione assert
#include <string.h>  // permette di usare le funzioni per le stringhe strlen, strcmp

// prototipo funzione per terminazione con stampa messaggio d'errore
void die(const char *s);

// stampa tutte le parole che si ottengono
// permutado i primi n caratteri della stringa s[]
int anagrammi(char *s[], int n)
{
    if (n == 1)
    {
        printf("%s %s %s\n", s[0], s[1], s[2]);
        return 1;
    }
    int tot = anagrammi(s, n - 1);
    for (int i = n - 2; i >= 0; i--)
    {
        if (strcmp(s[n - 1], s[i]))
        {
            char *tmp = s[n - 1];
            s[n - 1] = s[i];
            s[i] = tmp;
            tot += anagrammi(s, n - 1);
            tmp = s[n - 1];
            s[n - 1] = s[i];
            s[i] = tmp;
        }
    }
    return tot;
}

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        printf("Uso: %s [parole]\n", argv[0]);
        return 1;
    }
    printf("\n\n");
    int tot = anagrammi(argv + 1, argc - 1);
    printf("Ho stampato %d anagrammi\n", tot);
    return 0;
}

// stampa messaggio d'errore e termina
void die(const char *s)
{
    perror(s);
    exit(1);
}
