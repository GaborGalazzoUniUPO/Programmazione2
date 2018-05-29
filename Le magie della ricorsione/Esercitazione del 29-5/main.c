#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>
#include <math.h>

// procedura di partizionamento di un array a[0..n-1]
// partiziona l'array in due parti in modo che gli elementi
// della prima parte sono <= degli elementi della seconda parte
// restituisce il numero di elementi nelal prima parte
int partition(int a[], int n)
{
    assert(n > 1);

    // scelgo pivot in posizione random
    int k = random() % n; // genero posizione random del pivot
    int pivot = a[k];     // elemento pivot
    a[k] = a[0];
    a[0] = pivot; // scambia a[k]<->a[0] per mettere il pivot in a[0]

    // procedura di partizionamento
    // l'elemento pivot svolge anche la funzione di sentinella
    int i = -1; // puntatore oltre estremo sinistro
    int j = n;  //puntatore oltre estremo destro
    while (1)
    {
        while (a[--j] > pivot)
            ; // esce se a[j]<=pivot
        while (a[++i] < pivot)
            ; // esce se a[i]>=pivot
        if (i < j)
        {
            // scambia a[i] <-> a[j]
            int t = a[i];
            a[i] = a[j];
            a[j] = t;
        }
        else
            break;
    }
    // la prima meta' e' a[0] .. a[j] quindi ha j+1 elementi
    assert(j + 1 > 0);
    assert(j + 1 < n);
    return j + 1;
}

int my_select(int a[], int n, int k)
{
    if(n == 0)
        return a[0];
    if (n == 1)
        return a[k];
    if (n > 1)
    {
        int q = partition(a, n);
        assert(q > 0 && q < n); // verifica che entrambe le partizioni non siano vuote
        if (k < q)
            return my_select(a, q, k); // chiamata ricorsiva prima parte
        else
            return my_select(a + q, n - q, k -q); // chiamata ricorsiva seconda parte
    }
    return a[k - 1];
}

int main(int argc, char *argv[])
{

    int a[10] = {1, 9, 2, 8, 3, 8, 4, 7, 5, 6};
    for (int i = 0; i<10; i++)
    {
    int r = my_select(a, 10, i);
    printf("\n\n%d\n\n", r);
    }
    return 0;
}
