/* Să se implementeze cu alocare dinamică o stivă de numere întregi,cu următoarele operatii:
(a) void push (a, stiva) care adaugă elementul a în vârful stivei;
(b) int pop (stiva) care scoate elementul din vârful stivei şi îl intoarce ca rezultat al funcţiei;
(c) int peek(stiva) care întoarce elementul din vârful stivei, fără a-l scoate;
(d) bool empty(stiva) care verifică dacă stiva este vidă sau nu;
(e) int search(a, stiva) care intoarce -1 daca elementul a nu se află in stiva.
Daca a apare in stiva, atunci functia intoarce distanta de la varful stivei pana la aparitia
cea mai apropiata de varf. Se va considera ca varful se afla la distanta 0.
(f) void afiseaza(stiva) care afiseaza stiva, pornind de la varful ei si continuand spre baza.*/
#include <iostream>
using namespace std;

struct stiva
{
    int info;
    stiva *next;
};

stiva *prim;

void push(int a)
{
    stiva *p=new stiva;
    p->next=prim;
    p->info=a;
    prim=p;
}

int pop()
{
    if(prim==NULL)
        cout<<"\nNu se poate scoate nici un element,stiva este nula.";
    else{
            int x;
            stiva *p=new stiva;
            p=prim;
            x=prim->info;
            prim=prim->next;
            cout<<"\nS-a scos elementul: ";
            return x;
            delete p;
        }
}

int peek()
{
    if(prim==NULL)
        cout<<"\nStiva este nula.";
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
    stiva *p=new stiva;
    for(p=prim;p!=NULL;p=p->next)
        if(p->info==a)
            return distanta;
        else
            distanta++;
    return -1;
}

void afiseaza()
{
    stiva *p=new stiva;
    p=prim;
    if(p==NULL)
        cout<<"\nStiva este nula.";
    else
        cout<<"\nStiva este: ";
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
    push(4);
    push(7);
    afiseaza();
    cout<<pop();///sau pop(); daca nu dorim sa afisam elementul care s-a scos.
    afiseaza();
    cout<<"\nvarful este: "<<peek();
    ///Se va considera ca varful se afla la distanta 0.
    cout<<search(1);
    cout<<pop();
    cout<<pop();
    cout<<"\nStiva este goala? 1=DA/0=NU\n"<<empty();
    cout<<pop();
    cout<<"\nStiva este goala? 1=DA/0=NU\n"<<empty();
    afiseaza();
    return 0;
}
