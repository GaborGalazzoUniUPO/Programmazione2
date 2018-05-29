#include <stdio.h>
#include <stdlib.h>

int** tartaglia(int n){
    int** triangolo = malloc(sizeof(int*));
    for(int i = 0; i<n; i++){
        triangolo[i] = malloc(sizeof(int)*(i+1));
        triangolo[i][0] = 1;
        for(int j = 1; j<=i; j++){
            triangolo[i][j] = triangolo[i-1][j-1] + triangolo[i-1][j];
        }
    }
    return triangolo;
}

void stampa_tartaglia(int** tartaglia, int n){
    for(int i = 0; i<n; i++)
    {
        for(int j = 0; j<=i; j++)
            printf("%d\t", tartaglia[i][j]);
        puts("");
    }
}

void free_tartaglia(int** tartaglia, int n){
    for(int i = 0; i<n; i++)
        free(tartaglia[i]);
    free(tartaglia);
}

int main(int argc, char* argv[]){
    if(argc != 2)
    {
        printf("USAGE: %s numero", argv[0]);
        return 1;
    }
    int num = atoi(argv[1]);
    int** t = tartaglia(num);
    stampa_tartaglia(t, num);
    free_tartaglia(t, num);
    
    return 0;
}