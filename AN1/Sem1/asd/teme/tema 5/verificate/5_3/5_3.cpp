/** 3.Dat un sir w = w1w2 ... wn de caractere '(' si ')', sa se foloseasca o stiva
pentru a decide daca acest sir este corect parantezat (pentru orice subsir
w1...wi, cu i=1,n avem ca numarul de caractere '(' >= cu numarul de caractere ')').
In caz ca w nu este parantezat corect,se va indica pozitia primei paranteze ')'
care nu are corespondent.

##am tinut cont de faptul ca nu este de ajuns ca '('>=')'
de exemplu "))(((" ar fi fost corect,deci am considerat conditia:sa existe paranteza deschisa
inainte sa fie inchisa,indiferent de pozitia in sir

si prima pozitie din sir este 0.
##
**/

#include <iostream>
using namespace std;

struct stiva
{
    char info;
    int indice;
    stiva *next;
};

stiva *prim;

void push(char x,int i)
{
    stiva *p=new stiva;
    p->next=prim;
    p->info=x;
    p->indice=i;
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

int search2(char a)
{
    stiva *p=new stiva;
    for(p=prim;p!=NULL;p=p->next)
        if(p->info==a)
            return p->indice;
    return -1;
}

void afiseaza()
{
    if(prim==NULL)
        cout<<"\nCorect parantezat.";
    else
    {
        int x=search2(')');
        if(x!=-1)
            cout<<"\nIncorect parantezat.\nPozitia:"<<x;
        else
            cout<<"\nCorect parantezat.";
    }
}

int main()
{
    int i,n;
    cout<<"n= ";cin>>n;
    char s[n];
    for(i=0;i<n;i++)
    {
        cin>>s[i];
        if(s[i]=='(')
            if(prim==NULL)
                push(s[i],i);
            else
                if(search(')'))
                    pop();
                else
                    push(s[i],i);
        else
            if(s[i]==')')
                if(prim==NULL)
                    {
                        cout<<"Incorect parantezat.\nPozitia:"<<i;
                        return 0;
                    }
            else
                if(search('('))
                    pop();
                else
                    push(s[i],i);
    }

    afiseaza();

    return 0;
}
