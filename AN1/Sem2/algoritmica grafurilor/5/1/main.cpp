#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

ifstream in("graf.in");

void partitie_graf(vector < vector <int> > la, vector <int> &tata,
                    vector <int> &partitie, int nod, int nr, int &ok, int &nod_ciclu_inceput, int &nod_ciclu_final)
{
    if(ok)//Daca ok este 0, inseamna ca avem o muchie cu un nod din aceeasi partitie
    {
        partitie[nod]=nr;
        if(nr==1)
            nr++;
        else
            nr--;
        for(unsigned int i=0; i<la[nod].size(); i++)//DFS
        {
            if(partitie[la[nod][i]]==partitie[nod] and ok)//Daca s-a gasit un nod ce are legatura
            //cu altul din aceeasi partitie, ok devine 0 si memoram cele 2 capete ale ciclului
            {
                ok=0;
                nod_ciclu_inceput=la[nod][i];
                nod_ciclu_final=nod;
            }
            if(!partitie[la[nod][i]] and ok)//Daca nodul nu se afla intr-o partitie si ok e 1
            {
                tata[la[nod][i]]=nod;
                partitie_graf(la, tata, partitie, la[nod][i], nr, ok, nod_ciclu_inceput, nod_ciclu_final);
            }
        }
    }
}

int main()
{
    int n,m;
    in>>n>>m;
    vector < vector <int> > la (n+1);//Lista de adiacenta a grafului
    for(int i=0; i<m; i++)
    {
        int u,v;
        in>>u>>v;
        la[u].push_back(v);
        la[v].push_back(u);
    }
    cout<<"Lista de adiacenta a grafului\n\n";
    for(unsigned int i=1; i<la.size(); i++)//Afisare graf pentru o verificare mai usoara
    {
        cout<<"Nodul "<<i<<" are vecinii: ";
        for(unsigned int j=0; j<la[i].size(); j++)
            cout<<la[i][j]<<' ';
        cout<<'\n';
    }
    vector <int> tata (n+1);//Vectorul de tati
    vector <int> partitie (n+1);//Vectorul de partitii
    int ok=1, nod_ciclu_inceput, nod_ciclu_final;
    partitie_graf(la, tata, partitie, 1, 1, ok, nod_ciclu_inceput, nod_ciclu_final);
    cout<<'\n';
    if(ok)//Graful este bipartit
        for(unsigned int i=1;i<partitie.size();i++)
            cout<<"Nodul "<<i<<" se afla in partitia "<<partitie[i]<<'\n';
    else//Graful nu este bipartit si se afiseaza un ciclu de lungime impara
    {
        cout<<"Un ciclu de lungime impara este: "<<nod_ciclu_final<<' ';
        while(nod_ciclu_inceput!=nod_ciclu_final)
        {
            cout<<tata[nod_ciclu_final]<<' ';
            nod_ciclu_final=tata[nod_ciclu_final];
        }
        cout<<'\n';
    }
    return 0;
}
