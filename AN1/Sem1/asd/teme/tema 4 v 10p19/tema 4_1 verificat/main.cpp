#include <iostream>
using namespace std;

struct A{
    int info;
    A *urm;
}*p,*q,*r,*prim,*ultim;


struct B{
    int info;
    B* urm;
}*p2,*q2,*prim2;

void adaugareFinalA(int x){
    A *p=new A;
    p->info=x;
    p->urm=NULL;
    if(prim==NULL){
        prim=ultim=p;
        return;
    }
    ultim->urm=p;
    ultim=p;
}

void adaugareInceputB(int x){
    B *p2=new B;
    p2->info=x;
    p2->urm=prim2;
    prim2=p2;
}

void afisareA(){
    p=prim;
    cout<<endl<<"A: ";
    while(p!=NULL){
        cout<<p->info<<' ';
        p=p->urm;
    }
}

void afisareB(){
    p2=prim2;
    cout<<endl<<"B: ";
    while(p2!=NULL){
        cout<<p2->info<<' ';
        p2=p2->urm;
    }
}

void inversareA(){
    p=prim;
    ultim->urm=p;
    q=prim->urm;
    p->urm=NULL;
    prim=q;
    while(prim!=ultim){
        q=prim;
        r=prim->urm;
        q->urm=p;
        ultim->urm=q;
        p=q;
        prim=r;
    }
}

int main()
{
    for(int i=1;i<=6;i++)
    adaugareFinalA(i);
    afisareA();
    int x;
    for(p=prim;p!=NULL;p=p->urm){
        x=p->info;
        adaugareInceputB(x);
    }
    afisareB();
    inversareA();
    afisareA();
    return 0;
}
