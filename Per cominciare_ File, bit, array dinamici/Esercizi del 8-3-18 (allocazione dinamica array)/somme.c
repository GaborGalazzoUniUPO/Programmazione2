#include <stdio.h>
#include <stdlib.h>

int *somme_parziali(int a[], int n);
void print_array(int a[], int n);

int main(int argc, char* argv[]) {
    int a[argc-1];
    for(int i = 1; i<argc; i++)
        a[i-1] = atoi(argv[i]);
    int* somme = somme_parziali(a, argc-1);
    print_array(somme, argc-1);
    free(somme);
    return 0;
}

int *somme_parziali(int a[], int n){
    int* sum_array;
    sum_array = malloc(sizeof(int)*n);
    sum_array[0] = a[0];
    for(int i = 1; i<n; i++)
        sum_array[i] = sum_array[i-1]+a[i];
    return sum_array;
}

void print_array(int a[], int n){
    for(int i = 0; i<n; i++)
        printf("%d\n",a[i]);
}