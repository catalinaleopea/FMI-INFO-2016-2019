#include <stdio.h>
#include <stdlib.h>
int main(){
    int **m1,**m2,n,i;
    int *p;
    p=(int*)malloc(23*sizeof(int));
    scanf("%d",n);
    m1=(int**)malloc(n*sizeof(int *));
    for(i=0;i<n;i++)
        {//alocam
        m1[i]=(int*)malloc((n-i)*sizeof(int));
        scanf("%d",m1[i]);
        }
    for(i=0;i<n;i++)
        printf("%d",*m1[i]);
    return 0;
}
