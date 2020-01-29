#include <stdio.h>
#include <stdlib.h>

matrice(int n)
{
    int **a;
    a=malloc(n*sizeof(int));
    int i;
    for(i=0;i<n;i++)
        a[i]=malloc(n*sizeof(int));
}

int main()
{
    int n;
    scanf("%d",&n);
    matrice(n);
    return 0;
}
