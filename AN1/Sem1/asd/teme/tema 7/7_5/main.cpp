/**Sã se scrie un algoritm pentru afiºarea elementului de pe poziþia k(în ordinea
crescãtoare a elementelor dintr-un ºir) folosid un arbore binar de cãutare indexat.**/

#include <iostream>
using namespace std;

struct arb
{
    arb *st,*dr;
    int info,index;
}*r;

void inserare(arb*&r,int x)
{
    if(r==NULL)
    {
        r=new arb;
        r->info=x;
        r->dr=NULL;
        r->st=NULL;
        return;
    }
    if(x<r->info)
        inserare(r->st,x);
    else
        inserare(r->dr,x);
}

void afisareSRD(arb*&r)
{
    if(r==NULL)
        return;
    afisareSRD(r->st);
        cout<<r->info<<' ';
    afisareSRD(r->dr);
}


arb* cautare(arb*&r,int index)
{
    if(r==NULL||r->index==index)
        return r;
    if(index<r->index)
        cautare(r->st,index);
    else
        cautare(r->dr,index);
}

int main()
{
    int k;
    cout<<"Dati pozitia ";cin>>k;
    inserare(r,5);
    inserare(r,9);
    inserare(r,3);
    inserare(r,4);
    inserare(r,7);
    inserare(r,6);
    inserare(r,8);
    afisareSRD(r);
    arb* poz=cautare(r,k);
    if(poz==NULL)
        cout<<"\nnu exista";
    else
        cout<<"\ns-a gasit,elementul de pe pozitia "<<k<<" are valoarea "<<poz->info;
    return 0;
}
