/**4. Dat un arbore binar de cautare si doi intregi k1 si k2,sa se afiseze
toate cheile x din arbore cu proprietatea k1<=x<=k2 .**/
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

void RSD(arb*&r,int k1,int k2)
{
    if(r==NULL)
        return;
    if(r->info>=k1&&r->info<=k2)
        cout<<r->info<<' ';
    RSD(r->st,k1,k2);
    RSD(r->dr,k1,k2);
}
int main()
{
    int k1,k2;
    cin>>k1>>k2;
    inserare(r,5);
    inserare(r,9);
    inserare(r,3);
    inserare(r,4);
    inserare(r,7);
    inserare(r,6);
    inserare(r,8);
    RSD(r,k1,k2);
    return 0;
}
