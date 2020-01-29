///A.1
#include <iostream>
#include <fstream>
using namespace std;
ifstream f("graf.in");

void construire(int **&matrice,int &noduri)
{
    int muchii;
    f>>noduri;
    f>>muchii;
    int a,b;///muchia
    matrice=new int*[noduri];
    for(int i=1;i<=noduri;i++)
    {
        matrice[i]=new int[noduri];
        for(int j=1;j<=noduri;j++)
            matrice[i][j]=0;
    }
    for(int i=0;i<muchii;i++)
    {
        f>>a>>b;
        matrice[a][b]=1;
        matrice[b][a]=1;
    }
}

void afisare(int **matrice,int noduri)
{
    for(int i=1;i<=noduri;i++)
    {
        for(int j=1;j<=noduri;j++)
            cout<<matrice[i][j]<<' ';
        cout<<'\n';
    }
}

int main()
{
    int **matrice;
    int noduri;
    construire(matrice,noduri);
    afisare(matrice,noduri);
    return 0;
}
