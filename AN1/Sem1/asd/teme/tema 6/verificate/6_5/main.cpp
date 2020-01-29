/**5. Să se scrie procedurile de inserare şi ştergere nod într-o, respectiv, dintr-o listă circulară
cu dublă înlănţuire şi nod marcaj, care implementează următoarea strategie: se inserează la dreapta
nodului marcaj şi se şterge de la stânga sa; cum se poate interpreta această modalitate de modificare a listei
R:FIFO,TIP COADA  **/
#include <iostream>
using namespace std;

struct lista
{
    int info;
    lista *next;
    lista *prev;
};

lista *start,*prim;

void inserareInceput(int x)
{
    if(prim==NULL)
    {
        prim=new lista;
        start=new lista;
        prim->info=x;
        prim->next=start;
        prim->prev=start;
        start->next=prim;
        start->prev=prim;
    }
    else
    {
        lista *p=new lista;
        p->info=x;
        p->prev=start;
        p->next=prim;
        prim->prev=p;
        prim=p;
    }
}

void stergereSfarsit()
{
    if(prim==NULL)
        cout<<"\nLista este deja nula.";
    else
    {
        cout<<"\nS-a scos elementul "<<start->prev->info;
        if(prim==start->prev)
        {
            delete prim;
            prim=start=NULL;
        }
        else
        {
            lista *penultim=start->prev->prev;
            lista *ultim=start->prev;
            penultim->next=start;
            start->prev=penultim;
            delete ultim;
            ultim=penultim;
        }
    }
}

void afisareInceput()
{
    cout<<'\n';
    if(prim==NULL)
        cout<<"Lista este nula.";
    else
    {
        lista *p=new lista;
        for(p=prim;p!=start;p=p->next)
            cout<<p->info<<' ';
    }
}

void afisareInversa()
{
    cout<<'\n';
    if(prim==NULL)
        cout<<"Lista este nula.";
    else
    {
        lista *p=new lista;
        for(p=start->prev;p!=start;p=p->prev)
            cout<<p->info<<' ';
    }
}

int main()
{
    inserareInceput(1);
    inserareInceput(2);
    inserareInceput(3);
    afisareInceput();
    afisareInversa();
    stergereSfarsit();
    afisareInceput();
    afisareInversa();
    stergereSfarsit();
    stergereSfarsit();
    afisareInceput();
    afisareInversa();

    return 0;
}
