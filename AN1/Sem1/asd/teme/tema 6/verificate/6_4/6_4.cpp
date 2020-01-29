/**O listă, Start, cu nod marcaj, va conţine în variabila Start adresa acestui nod, iar lista efectivă, în
care în fiecare nod avem reprezentat un element al mulţimii de date, va fi Start.next.
O listă cu nod marcaj vidă va conţine doar nodul marcaj.
Să se scrie procedurile de inserare, respectiv, ştergere a unui nod cu o cheie
dată într-o, respectiv, dintr-o listă circulară cu dublă înlănţuire şi nod marcaj.
**/
#include <iostream>
using namespace std;

struct lista
{
    int info;
    lista *next;
    lista *prev;
};

lista *start,*prim,*ultim;

void inserareInceput(int x)
{
    if(prim==NULL)
    {
        prim=new lista;
        ultim=new lista;
        start=new lista;
        prim->info=x;
        prim->next=NULL;
        prim->prev=NULL;
        ultim=prim;

        start->next=prim;
        prim->prev=start;
        start->prev=ultim;
        ultim->next=start;
    }
    else
    {
        lista *p=new lista;
        p->info=x;
        p->prev=NULL;
        p->next=prim;
        prim->prev=p;
        prim=p;
        prim->prev=start;
    }
}

void inserareSfarsit(int x)
{
    if(prim==NULL)
    {
        prim=new lista;
        ultim=new lista;
        start=new lista;
        prim->info=x;
        prim->next=NULL;
        prim->prev=NULL;
        ultim=prim;

        start->next=prim;
        prim->prev=start;
        start->prev=ultim;
        ultim->next=start;
    }
    else
    {
        lista *p=new lista;
        p->info=x;
        p->next=NULL;
        p->prev=ultim;
        ultim->next=p;
        ultim=p;
        ultim->next=start;
    }
}

void stergereElementInterior(lista *elem)
{
    elem->prev->next = elem->next;
    elem->next->prev = elem->prev;
    delete elem;
}

lista* CautarePozitie(int pozitie)
{
    int i=0;
    lista *p=new lista;
    p=prim;
    while (p!=NULL && i<pozitie)
    {
        p=p->next;
        i++;
    }
    if (i==pozitie)
        return p;
    else
        return NULL;
}

void stergereSfarsit()
{
    if(ultim==NULL)
        cout<<"\nLista este deja nula.";
    else
    {
        cout<<"\nS-a scos elementul "<<ultim->info;
        if(prim==ultim)
        {
            delete prim;
            prim=ultim=NULL;
        }
        else
        {
            lista *p=new lista;
            p=ultim->prev;
            delete ultim;
            ultim=p;
            ultim->next=NULL;
        }
    }
}

void stergerePozitie(int pozitie)
{
    if (prim == NULL)
        return;
    if (pozitie == 0)
    {
        lista* deSters =new lista;
        deSters= prim;
        if(prim->next==NULL)
            stergereSfarsit();
        else
        {
            prim=prim->next;
            prim->prev= NULL;
        }
        delete deSters;
        return;
    }
    lista* elem = CautarePozitie(pozitie);
    if(elem==ultim)
    {
        stergereSfarsit();
        return;
    }
    stergereElementInterior(elem);
}

lista* CautareValoare(int val)
{
    lista *p=new lista;
    p=prim;
    while (p!=NULL && p->info!=val)
        p=p->next;
    return p;
}

void stergereValoare(int val)
{
    if (prim == NULL)
        return;
    if (prim->info == val)
    {
        lista* deSters =prim;
        prim = prim->next;
        prim->prev = NULL;
        delete deSters;
        return;
    }
    lista* elem = CautareValoare(val);
    if(elem==ultim)
        stergereSfarsit();
    else
        stergereElementInterior(elem);
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
    if(ultim==NULL)
        cout<<"Lista este nula.";
    else
    {
    lista *p=new lista;
    for(p=ultim;p!=start;p=p->prev)
        cout<<p->info<<' ';
    }
}

int main()
{
    inserareInceput(1);
    inserareSfarsit(2);
    inserareSfarsit(3);
    inserareSfarsit(4);
    afisareInceput();
    afisareInversa();
    stergerePozitie(1);
    stergereValoare(3);
    afisareInceput();
    afisareInversa();

    return 0;
}
