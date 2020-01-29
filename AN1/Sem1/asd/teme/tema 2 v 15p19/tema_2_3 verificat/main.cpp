#include <iostream>
using namespace std;

struct Nod{
    float info;
    Nod *urm;
    };

Nod *prim,*ultim,*p,*q,*media;

void adaugare_final(int x){
    if(prim==NULL)
        {prim=new Nod;
        prim->info=x;
        prim->urm=NULL;
        ultim=prim;
        }
    else{
        Nod *p=new Nod;
        p->info=x;
        p->urm=NULL;
        ultim->urm=p;
        ultim=p;
        }
}

void adaugare_inceput(int x)
    {Nod*p=new Nod;
    p->urm=prim;
    p->info=x;
    prim=p;

}

void adaugare_dupa_valoare(int x,int y){
    p=prim;
    while(p!=NULL&&p->info!=x)
    p=p->urm;
    if(p!=NULL){
        Nod *q=new Nod;
        q->info=y;
        q->urm=p->urm;
        p->urm=q;
        if(p==ultim)
            ultim=q;
        }

}

void afisare(){
    p=prim;
    cout<<endl;
    while(p!=NULL){
        cout<<p->info<<' ';
        p=p->urm;
    }

}

void media_numere(){
    q=prim;
    p=prim->urm;
    float m;
    while(p!=NULL){
        Nod* media=new Nod;
        m=(q->info+p->info)/2;
        media->info=m;
        media->urm=p;
        q->urm=media;
        q=p;
        p=p->urm;

    }
}

int main()
{
    adaugare_final(3);

    adaugare_inceput(4);

    adaugare_final(2);

    adaugare_inceput(6);

    afisare();

    media_numere();

    afisare();

}
