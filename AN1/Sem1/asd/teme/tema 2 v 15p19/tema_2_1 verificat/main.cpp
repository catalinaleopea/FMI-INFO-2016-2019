#include <iostream>
using namespace std;

struct Nod{
    int info;
    Nod *urm;
    };

Nod *prim,*ultim,*p,*q;

void adaugare_final(int x){
    if(prim==NULL){
        prim=new Nod;
        prim->info=x;
        prim->urm=NULL;
        ultim=prim;
    }
    else{Nod *ultim=new Nod;
        Nod *p=new Nod;
        p->info=x;

        ultim->urm=p;
        p->urm=NULL;
        ultim=p;
    }
}

void adaugare_inceput(int x){
    Nod *p=new Nod;
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
        p->urm=q;}
    if(p==ultim)
        ultim=q;
}

void afisare(){
    Nod *p;
    p=prim;
    cout<<endl;
    while(p!=NULL){
        cout<<p->info<<' ';
        p=p->urm;
    }
}

void cautare_valoare(int x){
    p=prim;
    int OK=0;
    while(p!=NULL)
        {if(p->info==x)
            OK=1;
        p=p->urm;}
    if(OK)
        cout<<endl<<"s-a gasit";
        else
            cout<<endl<<"nu s-a gasit";

}

void cautare_dupa_pozitie(int x){
    int i=0;
    for(p=prim;p!=NULL&&i<x;i++,p=p->urm){}

    if(i==x)
        cout<<endl<<"elementul de pe pozitia "<<x<<" este "<<p->info;
        else
            cout<<endl<<"nu s-a gasit pozitia";

}

void stergere_de_pe_pozitie(int x){
    int i=0;
    if(prim==NULL)
        cout<<endl<<"lista este deja goala";
    else{
        if(x==1){
            p=prim;
            prim=prim->urm;
            delete p;
        }
        else{
            for(p=prim;p!=NULL&&i<x-2;i++,p=p->urm){}

            q=p;
            p=p->urm;
            q->urm=p->urm;
            delete p;
        }
    }
}

void stergere_valoare(int x){
    Nod *prev;
    p=prim;
    if(prim==NULL)
        cout<<endl<<"lista este deja goala";
    while(p->urm!=NULL&&p->info!=x){
        prev=p;
        p=p->urm;
    }
    if(p==NULL){
            cout<<endl<<"nu s-a gasit\n";
            return;
    }
    if(p==prim){
        if(prim->urm==NULL)
            prim=NULL;
        else
            prim=prim->urm;
        delete p;
        return;
    }
    if(p==ultim){
        ultim=prev;
    }
    prev->urm=p->urm;
    delete p;
}

void stergere_totala(){
    p=prim;
    while(p!=NULL){
        p=p->urm;
        delete prim;
        prim=p;
    }
    delete prim;
    cout<<endl<<"lista vida";
}

int main(){
   adaugare_inceput(2);
   adaugare_inceput(1);
   adaugare_dupa_valoare(2,3);
   afisare();
   stergere_valoare(2);
   stergere_valoare(3);
   adaugare_final(4);
   afisare();
    return 0;

}
