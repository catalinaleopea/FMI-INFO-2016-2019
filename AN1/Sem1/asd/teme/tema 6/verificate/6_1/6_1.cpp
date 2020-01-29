/** 1. Să se implementeze o listă liniară dublu înlănţuită alocată
dinamic în care se vor reţine numere întregi.
Scrieţi funcţii pentru:
a) Adăugarea unui element la început;
b) Adăugarea unui element la sfârşit;
c) Adăugarea unui element în interiorul listei;
d) Afişarea elementelor listei în ordinea introducerii lor;
e) Afişarea elementelor listei în ordine inversă;
f) Ştergerea unui element din listă ştiind numărul lui de ordine;
g) Ştergerea unui element din listă ştiind valoarea lui.
Să se utilizeze aceste functii într-un program care afişează un meniu
în vederea selectării functiei dorite din cele sapte posibile.**/
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

void inserareSfarsit(int x)
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
        p->next=NULL;
        p->prev=ultim;
        ultim->next=p;
        ultim=p;
    }
}

int cautareValoare(int x)
{
    listaD *p=new listaD;
    int pozitie=0;
    for(p=prim;p!=NULL;p=p->next)
        if(p->info==x)
            return pozitie;
        else
            pozitie++;
    return -1;
}

void inserareDupaValoare(int x,int y)///x dupa y
{
    int a=cautareValoare(y);
    if(a==-1)
        cout<<"nu s-a gasit valoarea "<<y;
    else
    {
        listaD *p=new listaD;
        listaD *q=new listaD;
        p=prim;
        q->info=x;
        int i=0;
        while(i!=a&&p)
        {
            p=p->next;
            i++;
        }
        if(p==prim)
        {
            q->next=prim->next;
            prim->next=q;
            q->prev=prim;
            q->next->prev=q;
        }
        else
        {
            if(p==ultim)
                inserareSfarsit(x);
            else
            {
                q->next=p->next;
                p->next=q;
                q->prev=p;
                q->next->prev=q;
            }
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

void Meniu()
{
    char x='Y';
    do
    {
        int selectie;
        do
        {
            cout<<"Alegeti functia dorita:\n";
            cout<<"1)Adaugarea unui element la inceput\n";
            cout<<"2)Adaugarea unui element la sfarsit\n";
            cout<<"3)Adaugarea unui element in interiorul listei,dupa o anumita valoare\n";
            cout<<"4)Afisarea elementelor listei in ordinea introducerii lor\n";
            cout<<"5)Afisarea elementelor listei in ordine inversa\n";
            cout<<"6)Stergerea unui element din lista stiind numarul lui de ordine\n";
            cout<<"7)Stergerea unui element din lista stiind valoarea lui\n";
            cout<<"8*)Cautarea unui element in lista stiind valoarea lui\n";
            cin>>selectie;
        }while (selectie<1&&selectie>8);
        switch (selectie)
        {
            case 1:
            {
                int x;
                cout<<"\nScrieti numarul:";
                cin>>x;
                inserareInceput(x);
                break;
            }
            case 2:
            {
                int x;
                cout<<"\nScrieti numarul:";
                cin>>x;
                inserareSfarsit(x);
                break;
            }
            case 3:
            {
                int x,y;
                cout<<"\nDati elementul pe care doriti sa il adaugati:";
                cin>>x;
                cout<<"\nCare este valoarea dupa care vreti sa il adaugati?";
                cin>>y;
                inserareDupaValoare(x,y);
                break;
            }

            case 4:
            {
                afisareInceput();
                break;
            }
            case 5:
            {
                afisareInversa();
                break;
            }
            case 6:
            {
                int x;
                cout<<"\nScrieti numarul de ordine al elementului de sters.";
                cin>>x;
                stergerePozitie(x);
                break;
            }
            case 7:
            {
                int x;
                cout<<"Scrieti valoarea elementului de sters.";
                cin>>x;
                stergereValoare(x);
                break;
            }
            case 8:
            {
                int x;
                cout<<"Scrieti valoarea elementului pe care doriti sa-l cautati.";
                cin>>x;
                cout<<"S-a gasit pe pozitia "<<cautareValoare(x);
                break;
            }
        }
        cout<<"\nDoriti sa continuati?(Y/N): ";
        cin>>x;
        }while(x!='N');
}

int main()
{

/** /// EXEMPLU FARA MENIU
    inserareInceput(1);
    inserareSfarsit(2);
    inserareDupaValoare(3,2);
    afisareInceput();
    afisareInversa();

    stergereValoare(2);
    stergereValoare(3);
    inserareSfarsit(4);
    afisareInceput();
    afisareInversa();

    stergerePozitie(1);
    afisareInceput();
    afisareInceput();**/

    Meniu();

    return 0;
}
