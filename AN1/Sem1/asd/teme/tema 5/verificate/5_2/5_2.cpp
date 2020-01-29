/**2. Dati un sir w = w1w2 .... wn (n par) de caractere 'a' si 'b',
să se decidă dacă in sirul w numarul de caractere 'a' este acelasi
cu numarul de caractere 'b'.Sirul de intrare se poate parcurge o
singura data,iar pentru a decide rezultatul se va folosi o stiva.
Nu se permite numărarea aparitiilor caracterelor 'a', 'b'.
Notă : încercaţi o rezolvare care să implice folosirea conceptului de stivă**/
#include <iostream>
using namespace std;

struct stiva
{
    char info;
    stiva *next;
};

stiva *prim;

void push(char x)
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


int search(char a)
{
    stiva *p=new stiva;
    for(p=prim;p!=NULL;p=p->next)
        if(p->info==a)
            return 1;
    return 0;
}

void empty()
{
    if(prim==NULL)
        cout<<"\nStiva este nula,deci nr de 'a' este egal cu nr de 'b'";
    else
        cout<<"\nNumerele de caractere 'a' si 'b' sunt diferite.";
}

int main()
{

    int n,i;
    cout<<"n=";cin>>n;
    char s;
    for(i=0;i<n;i++)
    {
        cin>>s;
        if(s=='a')
            if(prim==NULL)
                push(s);
            else
                if(search('b'))
                    pop();
                else
                    push(s);
        else
            if(s=='b')
                if(prim==NULL)
                    push(s);
            else
                if(search('a'))
                    pop();
                else
                    push(s);
    }
    empty();
    return 0;
}
