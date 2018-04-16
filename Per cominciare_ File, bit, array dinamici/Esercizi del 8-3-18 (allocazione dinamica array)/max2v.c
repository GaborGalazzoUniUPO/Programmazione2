#include <stdio.h>
#include <stdlib.h>

int max_array(int a[], int n);
int *doppi(int a[], int n, int *m);
void print_array(int a[], int n);

int main(int argc, char* argv[]) {
    int a[argc-1];
    for(int i = 1; i<argc; i++)
        a[i-1] = atoi(argv[i]);
    int m;
    int* doppi_array = doppi(a, argc-1, &m);
    int max = max_array(doppi_array, m);
    printf("Massimo: %d\n", max);
    free(doppi_array);
    return 0;
}

int max_array(int a[], int n){
    int max = a[0];
    for(int i = 1; i<n; i++)
        if(a[i]>max)
            max = a[i];
    return max;
}

int *doppi(int a[], int n, int *m){
    int* doppi;
    int k = 0;
    doppi = malloc(n*sizeof(int));
    for(int i = 0; i<n-1; i++){
        for(int j = i+1; j<n; j++){
            if(a[j] == a[i])
                doppi[k++] = a[i];
        }
    }
    if(k == 0){
        puts("Errore: l'array non contiene doppi");
        free(doppi);
        exit(1);
    }
    *m = k;
    doppi = realloc(doppi, (k)*sizeof(int));      
    return doppi;
}