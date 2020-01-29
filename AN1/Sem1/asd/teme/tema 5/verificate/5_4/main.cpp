/**4. Consideram urmatoarea problema: ni se da o suprafata circulara
cu un numar n de pini (tarusi) pe margini (numerotati de la 1 la n),
impreuna cu o lista de perechi de pini ce trebuie conectati cu fire
metalice. Problema cere sa determinati in timp O(n) daca pentru o
configuratie ca mai sus, pinii pereche pot fi conectati, fara ca
acestea sa se intersecteze. La intrare se vor citi:n numarul de pini;
pereche[n] un vector de n componente,unde pereche[i]==pereche[j]
1<=i<=j<=n,daca pinii i si j trebuie conectati. **/
#include <iostream>
using namespace std;

struct stiva
{
    int info;
    stiva *next;
};

stiva *prim;

void push(int x)
{
    stiva *p=new stiva;
    p->next=prim;
    p->info=x;
    prim=p;
}

void pop()
{
    if(prim==NULL)
       cout<<"deja nula";
    else{
            stiva *p=new stiva;
            p=prim;
            prim=prim->next;
            delete p;
        }
}

void empty()
{
    if(prim==NULL)
        cout<<"\nconfiguratie valida";
    else
        cout<<"\nconfiguratie invalida";
}

int main()
{

    int n,i;
    int v[100];
    cout<<"n=";cin>>n;
    for(i=0;i<n;i++)
    {
        cin>>v[i];
            if(prim==NULL)
                push(v[i]);
            else
            {
                if((prim->info)==v[i])
                    pop();
                else
                    push(v[i]);
            }
    }
    empty();
    return 0;
}
