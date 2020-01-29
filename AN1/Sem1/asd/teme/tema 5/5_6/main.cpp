/**Spunem ca o imagine digitala binara M este o matrice de m x m elemente
(pixeli) 0 sau 1. Un element a al matricei este adiacent cu b, daca b se afla
deasupra, la dreapta, dedesubtul, sau la stanga lui a in imaginea M. Spunem ca doi
pixeli 1 adiacenti apartin aceleiasi componente. Problema va cere sa etichetati pixelii
imaginii astfel incat doi pixeli primesc aceeasi eticheta daca si numai daca apartin
aceleiasi componente.**/
#include <iostream>
using namespace std;

void vecini(int a[100][100],int i,int j,int k)
{
    a[i][j]=k;
    if(a[i-1][j-1])
        a[i-1][j-1]=k;
    if(a[i-1][j])
        a[i-1][j]=k;
    if(a[i-1][j+1])
        a[i-1][j+1]=k;
    if(a[i][j-1])
        a[i][j-1]=k;
    if(a[i][j+1])
        a[i][j+1]=k;
    if(a[i+1][j-1])
        a[i+1][j-1]=k;
    if(a[i+1][j])
        a[i+1][j]=k;
    if(a[i+1][j+1])
        a[i+1][j+1]=k;
}

int main()
{
    int a[100][100];
    int m,i,j,k=2;
    cout<<"m=";cin>>m;
    for(i=0;i<m;i++)
        for(j=0;j<m;j++)
            cin>>a[i][j];
    for(i=1;i<m;)
    {
        bool ok=0;
        for(j=0;j<m;j++)
            if(a[i][j]==1)
            {
                if(a[i][j+1]==1)
                    j++;
                vecini(a,i,j,k);
                k++;j++;ok=1;
            }
    if(ok)
        i=i+2;
    else
        i++;
    }
    cout<<'\n';
    for(i=0;i<m;i++)
    {
        for(j=0;j<m;j++)
            cout<<a[i][j]<<' ';
        cout<<'\n';
    }
    return 0;
}
