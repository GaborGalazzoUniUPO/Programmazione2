#include <stdio.h>
#include <stdlib.h>

int max_array(int a[], int n);

int main(int argc, char* argv[]) {
    int a[argc-1];
    for(int i = 1; i<argc; i++)
        a[i-1] = atoi(argv[i]);
    int max = max_array(a, argc-1);
    printf("Massimo: %d\n", max);
    return 0;
}

int max_array(int a[], int n){
    int max = a[0];
    for(int i = 1; i<n; i++)
        if(a[i]>max)
            max = a[i];
    return max;
}