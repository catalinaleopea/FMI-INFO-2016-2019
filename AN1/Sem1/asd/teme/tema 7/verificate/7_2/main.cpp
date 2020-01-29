/**2. Arbori binari de cãutare
(5 p) 2. Sa se implementeze un arbore binar de cautare cu urmatoarele operatii:
(a) insert (t, x) - insereaza cheia x in arborele de radacina t;
(b) search(t, x) - intoarce 1 daca elementul a se afla in arborele de radacina
t si 0 in caz contrar;
(c) findMax(t) - intoarce elementul maxim din arborele de radacina t, fara a-l
sterge din arbore;
(d) delete(t, x) - sterge in arborele de radacina t nodul cu cheia x (pastrand
proprietatea de arbore binar de cautare);**/
#include <iostream>
using namespace std;

struct arb{
int info;
arb *st;
arb *dr;
}*r;

void inserare(arb*&r,int x)
{
    if(r==NULL)
    {
        r=new arb;
        r->info=x;
        r->st=r->dr=NULL;
        return;
    }
    if(x<r->info)
        inserare(r->st,x);
    else
        inserare(r->dr,x);
}

bool cautare(arb*&r,int x)
{
    if(r==NULL)
        return 0;
    if(r->info==x)
        return 1;
    if(x<r->info)
        cautare(r->st,x);
    else
        cautare(r->dr,x);
}

arb* cautaMax(arb*&r)
{
    if(r->dr!=NULL)
        cautaMax(r->dr);
    else
        return r;
}

arb* sterge(arb*&r,int x)
{
    if(r==NULL)
        return r;
    else
        if(x<r->info)
            r->st=sterge(r->st,x);
        else
            if(x>r->info)
                r->dr=sterge(r->dr,x);
            else //am gasit
            {
            ///caz 1:fara copii
                if(r->st==NULL&&r->dr==NULL)
                {
                    delete r;r=NULL;
                }
            ///caz 2:un copil
                else
                    if(r->st==NULL)
                    {
                        arb *deSters=r;
                        r=r->dr;
                        r->dr=sterge(r->dr,deSters->info);
                    }
                    else
                        if(r->dr==NULL)
                        {
                            arb *deSters=r;
                            r=r->st;
                            r->st=sterge(r->st,deSters->info);
                        }
                        ///caz 3:2 copii
                        else
                        {
                            arb* deSters=cautaMax(r->st);
                            r->info=deSters->info;
                            r->st=sterge(r->st,deSters->info);
                        }
            }
    return r;
}

void RSD(arb*&r)
{
    if(r==NULL)
        return;
    cout<<r->info<<' ';
    RSD(r->st);
    RSD(r->dr);
}

int main()
{
    inserare(r,4);
    inserare(r,1);
    inserare(r,7);
    inserare(r,3);
    inserare(r,5);
    inserare(r,2);
    inserare(r,6);
//    inserare(r,1);
  //  inserare(r,9);
    //inserare(r,19);
   // inserare(r,2);
    //inserare(r,18);
    RSD(r);

    //cout<<"\nMaximul este ";
    //arb* max=cautaMax(r);
    //cout<<max->info;

//    cout<<"\nS-a gasit 15?(1/0)"<<cautare(r,15);

    sterge(r,4);
    cout<<'\n';
    RSD(r);

    return 0;
}
