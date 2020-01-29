#include <iostream>
using namespace std;
struct listaD
{
    int info;
    listaD *next;
    listaD *prev;
};

listaD *prim,*ultim;

void inserareInceput(int x)
{
    if(prim==NULL)
    {
        prim=new listaD;
        ultim=new listaD;
        prim->info=x;
        prim->next=NULL;
        prim->prev=NULL;
        ultim=prim;
    }
    else
    {
        listaD *p=new listaD;
        p->info=x;
        p->prev=NULL;
        p->next=prim;
        prim->prev=p;
        prim=p;
    }
}

void afisareInceput()
{
    cout<<'\n';
    if(prim==NULL)
        cout<<"Lista este nula.";
    else
    {
        listaD *p=new listaD;
        for(p=prim;p!=NULL;p=p->next)
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
        listaD *p=new listaD;
        for(p=ultim;p!=NULL;p=p->prev)
            cout<<p->info<<' ';
    }
}

void stergereElementInterior(listaD *elem)
{
    elem->prev->next = elem->next;
    elem->next->prev = elem->prev;
    delete elem;
}

listaD* CautarePozitie(int pozitie)
{
    int i=0;
    listaD *p=new listaD;
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
            listaD *p=new listaD;
            p=ultim->prev;
            delete ultim;
            ultim=p;
            ultim->next=NULL;
        }
    }
}

void stergerePozitie(int pozitie)
{
// daca lista e vida nu facem nimic
    if (prim == NULL)
        return;
// daca este primul element, atunci il stergem si mutam capul
    if (pozitie == 0)
    {
        listaD* deSters =new listaD;
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
// daca este in interor, atunci folosim functia de stergere
    listaD* elem = CautarePozitie(pozitie);
    if(elem==ultim)
    {
        stergereSfarsit();
        return;
    }
    stergereElementInterior(elem);
}

listaD* CautareValoare(int val)
{
    listaD *p=new listaD;
    p=prim;
// parcurge lista pana la gasirea elementului sau epuizarea listei
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
        listaD* deSters =prim;
        prim = prim->next;
        prim->prev = NULL;
        delete deSters;
        return;
    }
// cautam elementul
    listaD* elem = CautareValoare(val);
// daca a fost gasit, atunci il stergem
    if(elem==ultim)
        stergereSfarsit();
    else
        stergereElementInterior(elem);
}
int main()
{
    for(int i=5;i>0;i--)
        inserareInceput(i);
    afisareInceput();
    afisareInversa();
    StergereValoare(5);
    afisareInceput();
    afisareInversa();
    StergerePozitie(3);
    afisareInceput();
    afisareInversa();

    return 0;
}
