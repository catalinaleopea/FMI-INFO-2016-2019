/**3. Sa se foloseasca un arbore binar de cautare pentru a sorta n numere.**/
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

void SRD(arb*&r)
{
    if(r==NULL)
        return;
    SRD(r->st);
    cout<<r->info<<' ';
    SRD(r->dr);
}

int main()
{
    int n;
    cout<<"Dati numarul de elemente ";cin>>n;
    cout<<"Scrieti cele "<<n<<" elemente";
    for(int i=0;i<n;i++)
    {
        int x;
        cin>>x;
        inserare(r,x);
    }
    SRD(r);
    return 0;
}
