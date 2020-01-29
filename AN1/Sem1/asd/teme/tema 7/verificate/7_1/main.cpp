/**1. Arbori binari
1. Sã se implementeze o structurã de arbore binar (nu arbori binari de cãutare)
cu cheile numere intregi, inserate pe niveluri. Scrieþi funcþii pentru:
(a) adãugarea unui nod frunzã;
(b) parcurgerea cheilor conform strategiei RSD;
(c) parcurgerea cheilor conform strategiei SRD;
(d) parcurgerea cheilor conform strategiei SDR.
**/
#include <iostream>
using namespace std;

struct arb{
int info;
arb * st;
arb * dr;
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

void RSD(arb*&r)
{
    if(r==NULL)
        return;
    cout<<r->info<<' ';
    RSD(r->st);
    RSD(r->dr);
}

void SRD(arb*&r)
{
    if(r==NULL)
        return;
    SRD(r->st);
    cout<<r->info<<' ';
    SRD(r->dr);
}

void SDR(arb*&r)
{
    if(r==NULL)
        return;
    SDR(r->st);
    SDR(r->dr);
    cout<<r->info<<' ';
}

int main()
{
    inserare(r,5);
    inserare(r,9);
    inserare(r,3);
    inserare(r,4);
    inserare(r,7);
    inserare(r,6);
    inserare(r,8);
    RSD(r);
    cout<<'\n';
    SRD(r);
    cout<<'\n';
    SDR(r);
    return 0;
}
