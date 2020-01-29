//decodificare Prufer
#include <iostream>
#include <list>
#include <vector>
#include <queue>
#include <fstream>

using namespace std;

ifstream fin("rezultat.out");
ofstream fout("conexiuni.out");

int main()
{
    int noduri,x;
    deque <int> codPrufer;
    while(fin>>x)
        codPrufer.push_back(x);//Codificarea Prufer
    noduri=codPrufer.size()+2;
    vector <int> grade;
    grade.assign(noduri+1,1);//Gradul nodurilor este numarul de aparitii+1
    for(unsigned int i=0;i<codPrufer.size();i++)//calculez suma gradelor
        grade[codPrufer[i]]++;
    list <int> *lista_adj;
    lista_adj=new list <int> [noduri+1];
    int ind=1,gasit=0;//Parcurg cu doi indici
    while(!codPrufer.empty())//Cat timp mai avem noduri in codificare
    {
        int nod=codPrufer.front();
        codPrufer.pop_front();
        if(!gasit)//Daca nu exista valori de 1 inainte de indice
        {//Parcurg pana gasim un nod cu gradul 1
            while(grade[ind]!=1 && ind<=noduri)
                ind++;
            lista_adj[nod].push_back(ind);
            lista_adj[ind].push_back(nod);
            grade[nod]--;
            grade[ind]--;//Scad gradele
            if(grade[nod]==1 && ind>nod)//Daca s-a format un 1,gasit ia valoarea nodului,
                gasit=nod;            //si programul revine la pozitia respectiva
        }
        else//Am o valoare de 1 inainte de indice
        {
            lista_adj[nod].push_back(gasit);
            lista_adj[gasit].push_back(nod);
            grade[nod]--;
            grade[gasit]--;//Scad gradele
            if(grade[nod]==1 and gasit<ind)
                gasit=nod;
            else//Daca nu s-a format un 1,programul continua de pe pozitia ind
                gasit=0;
        }
    }
    int nod1=0,nod2=0;//Unim cele doua noduri ramase
    for(unsigned int i=1;i<grade.size();i++)
        if(grade[i] and !nod1)
            nod1=i;
        else
            if(grade[i])
                nod2=i;
    lista_adj[nod1].push_back(nod2);
    lista_adj[nod2].push_back(nod1);
    for(int i=1;i<=noduri;i++)
    {
        fout<<"Nodul "<<i<<" are vecinii: ";
        for(list<int>::iterator it=lista_adj[i].begin();it!=lista_adj[i].end();it++)
            fout<<*it<<' ';
        fout<<'\n';
    }
    return 0;
}
