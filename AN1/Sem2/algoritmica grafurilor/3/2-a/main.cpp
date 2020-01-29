//Codificare  Prufer
#include <iostream>
#include <vector>
#include <list>
#include <fstream>

using namespace std;

ifstream fin("retea.in");
ofstream fout("rezultat.out");


void DFS(int nod, vector <int> &vizitat, list <int> *listaAdj, vector < pair <int,int> > &listaNod)
{
    vizitat[nod]=1;//Marchez nodul vizitat si il afisez
    cout<<nod<<' ';
    list<int>::iterator it;
    for(it=listaAdj[nod].begin(); it!=listaAdj[nod].end(); it++)
        if(!vizitat[*it])
        {
            listaNod[*it].first+=nod;
            listaNod[nod].first+=*it;//Fac suma nodurilor arborelui partial din DFS
            listaNod[*it].second++;//Cresc gradul
            listaNod[nod].second++;
            DFS(*it,vizitat,listaAdj,listaNod);
        }
}

int main()
{
    int noduri,u,v;
    fin>>noduri;
    list <int> *listaAdj;
    vector < pair <int,int> > listaNod(noduri+1);//<suma nodurilor vecine,grad>
    listaAdj=new list <int> [noduri+1];
    while(fin>>u)
    {//citesc din fisier muchiile si creez graful sub forma unei liste de liste
        fin>>v;
        listaAdj[u].push_back(v);
        listaAdj[v].push_back(u);
    }
    vector <int> vizitat (noduri+1);//creez un vector de noduri vizitate pentru DFS
    cout<<"Am vizitat nodurile \n";
    DFS(1,vizitat,listaAdj,listaNod);
    int i=1,ok=0;//Parcurg cu doi indici
    vector <int> codificare;
    for(int j=0; j<noduri-2; j++)
    {
        if(!ok)//Daca nu exista valori de 1 inainte de indice
        {
            while(listaNod[i].second!=1)//Parcurg pana gasesc un nod cu gradul 1
                i++;
            int nod=listaNod[i].first;
            codificare.push_back(nod);
            listaNod[i].second--;
            listaNod[nod].second--;//Scad gradele
            listaNod[nod].first-=i;//Scad suma
            if(listaNod[nod].second==1 && i>nod)//Daca s-a format un 1,ok ia valoarea nodului,
               ok=nod;                          //si programul revine la pozitia respectiva
        }
        else//Am o valoare de 1 inainte de indice
        {
            int nod=listaNod[ok].first;
            codificare.push_back(nod);//Pun in codificare vecinul frunzei
            listaNod[ok].second--;
            listaNod[nod].second--;//Scad gradele si suma
            listaNod[nod].first-=ok;
            if(listaNod[nod].second==1 && ok<i)
                ok=nod;
            else//Daca nu s-a format un 1, programul continua de pe pozitia i
                ok=0;
        }
    }
    for(unsigned int j=0; j<codificare.size(); j++)
        fout<<codificare[j]<<' ';
    return 0;
}
