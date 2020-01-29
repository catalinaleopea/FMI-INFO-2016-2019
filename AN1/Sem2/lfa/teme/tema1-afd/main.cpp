#include <iostream>
#include <fstream>
#include <list>
#include <cstring>

using namespace std;

ifstream fin("date.in");
ofstream fout("date.out");

list< pair<int,char> > *lista;
int nrI, nrF, stariI[20], stariF[20];

void cauta(int nod,char cuvant[50],unsigned int i, int &ok)
{
    fout<<nod<<' ';
    if(i==strlen(cuvant))
    {
        for(int j=0; j<nrF; j++)
            if(nod==stariF[j] && ok==0)
            {
                fout<<"Cuvant acceptat\n";
                ok=1;
            }
    }
    for(pair<int, char> it:lista[nod])
    {
        if(cuvant[i]==it.second && ok==0)
            cauta(it.first, cuvant, i+1, ok);
    }
}

int main()
{
    int noduri,muchii;
    char cuvant[50];
    fin>>  noduri>>  muchii>>  cuvant>>  nrI;
    for(int i=0;i<nrI;i++)
        fin>>stariI[i];
    fin>>nrF;
    for(int i=0;i<nrF;i++)
        fin>>stariF[i];
    lista=new list< pair <int,char> > [noduri+1];
    for(int i=0;i<muchii;i++)
    {
        int x,y;
        char w;
        fin>>x>>y>>w;
        lista[x].push_back(make_pair(y,w));
    }
    int ok=0;
    for(int i=0;i<nrI;i++)
    {

        cauta(i,cuvant,0,ok);
    }
    if(!ok)
        fout<<"Cuvant neacceptat\n";
    return 0;
}
