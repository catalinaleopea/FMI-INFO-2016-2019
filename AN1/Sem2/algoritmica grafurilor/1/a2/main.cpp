///A2
#include <iostream>
#include <fstream>
using namespace std;
ifstream f("graf.in");

struct lista{
int valoare;
lista *urm;
};

void construire(int *&vect,int &noduri)
{
    f>>noduri;
    int muchii;
    f>>muchii;
    lista *vect[noduri]=new lista;
    for(int i=0;i<muchii;i++)
    {
        int a,b;
        f>>a>>b;
        vect[a]=//adaug b la lista;
    }
}

void afisare(int vect,int noduri)
{
    for(int i=1;i<=noduri;i++)
        cout<<v[i]<<'\n';
}

int main()
{
    lista *vect;
    int noduri;
    construire(vect,noduri);
    afisare(vect,noduri);
    return 0;
}
