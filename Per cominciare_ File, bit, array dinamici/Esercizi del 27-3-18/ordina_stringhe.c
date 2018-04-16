#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <stdlib.h>

typedef char* string;

int inded_max(string s[], int n){
    assert(n>0);
    int max = 0;
    for(int i = 1; i<n; i++)
        if(strcmp(s[max], s[i])<0)
            max = i;
    return max;
}

void sposta_stringa_massima(string s[], int n){
    assert(n>0);
    int max = inded_max(s, n);
    string temp = s[n-1];
    s[n-1] = s[max];
    s[max] = temp;
}

void ordina_stringhe(string s[], int n){
    assert(n>0);
    for(int i = 0; i<n; i++)
        sposta_stringa_massima(s, n-i);
}

int main(int argc, char* argv[]){
    if(argc<2)
    {
        printf("usage: %s stringa1 ... stringaN\n", argv[0]);
        return 1;
    }
    string s[argc-1];
    for(int i = 0; i<argc-1; i++)
        s[i] = argv[i+1];
    ordina_stringhe(s, argc-1);
    for(int i = 0; i<argc-1; i++)
        printf("%s\n", s[i]);
    return 0;
}