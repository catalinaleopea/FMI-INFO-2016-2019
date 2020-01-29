/**Se numeşte DEQUE (de la Double Ended Queue) o structură liniară în care
inserările şi ştergerile se pot face la oricare din cele două capete, dar în nici un alt
loc din coadă.
Considerând structura DEQUE implementată cu ajutorul unei liste liniare cu
dublă înlănţuire, să se scrie procedurile de inserare şi ştergere la ambele capete ale ei;
să se utilizeze aceste proceduri într-un program care afişază un meniu în
vederea selectării procedurii dorite din cele patru posibile.**/
#include <iostream>
using namespace std;

struct coadaDubla
{
    int info;
    coadaDubla *next;
    coadaDubla *prev;
};

coadaDubla *prim,*ultim;


void inserareInceput(int x)
{
    if(prim==NULL)
    {
        prim=new coadaDubla;
        ultim=new coadaDubla;
        prim->info=x;
        prim->next=NULL;
        prim->prev=NULL;
        ultim=prim;
    }
    else
    {
        coadaDubla *p=new coadaDubla;
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
        prim=new coadaDubla;
        ultim=new coadaDubla;
        prim->info=x;
        prim->next=NULL;
        prim->prev=NULL;
        ultim=prim;
    }
    else
    {
        coadaDubla *p=new coadaDubla;
        p->info=x;
        p->next=NULL;
        p->prev=ultim;
        ultim->next=p;
        ultim=p;
    }
}

void stergereInceput()
{
    if(prim==NULL)
        cout<<"\nNu se poate scoate nici un element,coada este nula.";
    else
    {
        cout<<"\nS-a scos elementul "<<prim->info;
        if(prim==ultim)
        {
            cout<<"\nS-a scos elementul "<<prim->info;
            delete prim;
            prim=ultim=NULL;
        }
        else
        {
            coadaDubla *p=new coadaDubla;
            p=prim;
            prim=prim->next;
            delete p;
        }
    }
}

void stergereSfarsit()
{
    if(ultim==NULL)
        cout<<"\nNu se poate scoate nici un element,coada este nula.";
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
            coadaDubla *p=new coadaDubla;
            p=ultim->prev;
            delete ultim;
            ultim=p;
            ultim->next=NULL;
        }
    }
}

void afisareInceput()
{
    cout<<'\n';
    if(prim==NULL)
        cout<<"Coada este nula.";
    else
    {
        coadaDubla *p=new coadaDubla;
        for(p=prim;p!=NULL;p=p->next)
            cout<<p->info<<' ';
    }
}

void afisareInversa()
{
    cout<<'\n';
    if(ultim==NULL)
        cout<<"Coada este nula.";
    else
    {
        coadaDubla *p=new coadaDubla;
        for(p=ultim;p!=NULL;p=p->prev)
            cout<<p->info<<' ';
    }
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
            cout<<"1)Inserare la inceput\n";
            cout<<"2)Inserare la sfarsit\n";
            cout<<"3)Stergerea primului element\n";
            cout<<"4)Stergerea ultimului element\n";
            cout<<"5)Afisare de la inceput\n";
            cout<<"6)Afisare inversa\n";
            cin>>selectie;
        }while (selectie!=1&&selectie!=2&&selectie!=3&&selectie!=4&&selectie!=5&&selectie!=6);
        switch (selectie)
        {
            case 1:
            {
                int x;
                cout<<"Dati elementul ";
                cin>>x;
                inserareInceput(x);
                break;
            }
            case 2:
            {
                int x;
                cout<<"Dati elementul ";
                cin>>x;
                inserareSfarsit(x);
                break;
            }
            case 3:
            {
                stergereInceput();
                break;
            }
            case 4:
            {
                stergereSfarsit();
                break;
            }
            case 5:
            {
                afisareInceput();
                break;
            }
            case 6:
            {
                afisareInversa();
                break;
            }
        }
        cout<<"\nDoriti sa continuati?(Y/N): ";
        cin>>x;
        }while(x!='N');
}

int main()
{
    Meniu();
    return 0;
}
