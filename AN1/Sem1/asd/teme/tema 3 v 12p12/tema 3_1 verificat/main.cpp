#include <iostream>
using namespace std;

struct Nod{
    int info;
    Nod *urm;
    };

Nod *prim,*ultim,*p,*q;

void adaugare_inceput(int x){
    Nod *p=new Nod;
    p->urm=prim;
    p->info=x;
    prim=p;
}

void afisare(){
    p=prim;
    cout<<endl;
    while(p!=NULL){
        cout<<p->info<<' ';
        p=p->urm;
    }
}
 void adaugare_insertie(int x){
     p=prim;
     if(prim==NULL||p->info>=x)
        adaugare_inceput(x);
     else{
        while(p->urm!=NULL&&p->urm->info<x)
            p=p->urm;
        Nod *q=new Nod;
        q->info=x;
        q->urm=p->urm;
        p->urm=q;
     }

}

 int main(){
     adaugare_insertie(5);
     adaugare_insertie(20);
     adaugare_insertie(4);
     adaugare_insertie(3);
     adaugare_insertie(30);
     afisare();
 return 0;}

