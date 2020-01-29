#include <iostream>
#include <list>
#include <queue>
#include <fstream>

using namespace std;

ifstream fin("date.in");

int main()
{
    int n,suma=0;
    fin>>n;
    list <int> *secventaGrade;
    list <int> *listaAdj;
    secventaGrade=new list <int> [n+1];
    listaAdj=new list <int> [n+1];
    for(int i=1; i<=n; i++)
    {//creez o lista cu gradele nodurilor
        int grad;
        fin>>grad;
        secventaGrade[grad].push_back(i);
        suma=suma+grad;
    }
    list <int>::iterator it;
    for(int i=1; i<n; i++)
    {
        cout<<"Nodurile cu gradul "<<i<<" sunt: ";
        for(it=secventaGrade[i].begin(); it!=secventaGrade[i].end(); it++)
            cout<<*it<<' ';
        cout<<'\n';
    }
    if(suma==2*n-2)
    {//daca se poate forma un arbore
     //creez o coada pt terminale si una pt neterminale
        queue <int> terminale;
        queue <int> neterminale;
        for(int i=n; i>0; i--)
            for(it=secventaGrade[i].begin(); it!=secventaGrade[i].end(); it++)
            {
                int nod=*it;
                if(i==1)//daca gradul e 1,nodul e terminal
                    terminale.push(nod);
                else
                {//altfel e neterminal,adaugam in coada gradul si nodul
                    neterminale.push(i);
                    neterminale.push(nod);
                }
            }
        while(!neterminale.empty())//Cat timp exista neterminale
        {
            int grad=neterminale.front();
            neterminale.pop();
            int nod_n=neterminale.front();
            neterminale.pop();
            while(grad>1)//Cat timp nu a ajuns terminal
            {
                grad--;
                int nod_t=terminale.front();
                terminale.pop();//Luam un terminal si il eliminam din coada
                listaAdj[nod_n].push_back(nod_t);
                listaAdj[nod_t].push_back(nod_n);
            }
            terminale.push(nod_n);//Neterminalul a devenit terminal
        }
        while(!terminale.empty())//Cat timp avem terminale
        {
            int nod_t1=terminale.front();
            terminale.pop();
            int nod_t2=terminale.front();
            terminale.pop();///Luam 2 terminale si le unim
            listaAdj[nod_t1].push_back(nod_t2);
            listaAdj[nod_t2].push_back(nod_t1);
        }
    }
    for(int i=1; i<=n; i++)
    {
        cout<<"Nodul "<<i<<" are vecinii: ";
        for(list<int>::iterator it=listaAdj[i].begin(); it!=listaAdj[i].end(); it++)
            cout<<*it<<' ';
        cout<<'\n';
    }
    return 0;
}
