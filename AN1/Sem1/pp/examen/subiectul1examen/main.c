#include <stdio.h>
#include <stdlib.h>

void citire(int **v,int *n)
{
    int i;
    printf("nr de elemente este ");
    scanf("%d",n);
    *v=malloc((*n)*sizeof(int));
    for(i=0;i<*n;i++)
        scanf("%d",&((*v)[i]));
}

void afisare(int *v,int n)
{
    int i;
    for(i=0;i<n;i++)
        printf("%d ",*(v+i));
}

int minim(int *v,int n,int i,int j)
{
    int k=0,poz,min;
    while(k<i)
        k++;
    min=*(v+k);
    poz=k;
    k++;
    for(;k<=j&&k<n;k++)
        if(min>*(v+k))
        {
            min=*(v+k);
            poz=k;
        }
    return poz;
}

int main()
{
    int *v,n,k;//,i,j;
    citire(&v,&n);
    //afisare(v,n);
   // printf("\nDati limitele pentru cautare minimului\n");
  //  scanf("%d%d",&i,&j);
  //  int poz=minim(v,n,i,j);
   // printf("\npozitia minimul este %d",poz);

    for(k=0;k<n;k++)
    {
        int aux=v[k];
        int poz=minim(v,n,k,n);
        v[k]=v[poz];
        v[poz]=aux;
    }
    printf("\n");
    afisare(v,n);
    return 0;
}
