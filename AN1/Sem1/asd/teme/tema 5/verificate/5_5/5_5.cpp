/** Sa se implementeze o coada de numere intregi,cu urmatoarele operatii:
(a) void push(a, coada) care adauga elementul a in coada;
(b) int pop(coada) care scoate primul element din coada,si il intoarce
ca rezultat al functiei;
(c) int peek(coada) care întoarce primul element din coada,fara a-l scoate;
(d) bool empty(coada) care verifica daca coada este vida sau nu;
(e) int search(a, coada) care intoarce -1 daca elementul a nu se afla in
coada. Daca a apare in stiva,atunci functia intoarce distanta de la primul
element al cozii pana la aparitia cea mai apropiata de primul element al cozii.
Se va considera ca primul element se afla la distanta 0.
(f) void afiseaza(coada) care afiseaza coada, pornind de la primul element
si continuând spre ultimul.**/
#include <iostream>
using namespace std;

struct coada
{
    int info;
    coada *next;
};

coada *prim,*ultim;

void push(int a)
{
    coada *p=new coada;
    p->info=a;
    p->next=NULL;
    if(prim==NULL)
        prim=ultim=p;
    else
    {
        ultim->next=p;
        ultim=p;
    }
}

int pop()
{
    if(prim==NULL)
        cout<<"\nNu se poate scoate nici un element,coada este nula.";
    else{
            int x;
            coada *p=new coada;
            p=prim;
            x=prim->info;
            prim=prim->next;
            cout<<"\nS-a scos elementul ";
            return x;
            delete p;
        }
}

int peek()
{
    if(prim==NULL)
        cout<<"\nCoada este nula.";
    else
        return prim->info;
}

bool empty()
{
    return prim==NULL;
}

int search(int a)
{
    cout<<"\nElementul "<<a<<" s-a gasit pe pozitia ";
    int distanta=0;
    coada *p=new coada;
    for(p=prim;p!=NULL;p=p->next)
        if(p->info==a)
            return distanta;
        else
            distanta++;
    return -1;
}

void afiseaza()
{
    coada *p=new coada;
    p=prim;
    cout<<"\nCoada este ";
    if(p==NULL)
        cout<<"nula.";
    else
        while(p!=NULL)
        {
            cout<<p->info<<' ';
            p=p->next;
        }
}

int main()
{
    ///exemplu
    push(1);
    push(2);
    push(3);
    push(4);
    afiseaza();
    cout<<pop();
    afiseaza();
    cout<<"\nvarful este: "<<peek();
    cout<<search(1);
    cout<<search(3);
    cout<<pop();
    cout<<pop();
    cout<<"\nCoada este goala? 1=DA/0=NU\n"<<empty();
    cout<<pop();
    cout<<"\nCoada este goala? 1=DA/0=NU\n"<<empty();
    afiseaza();
    return 0;
}
