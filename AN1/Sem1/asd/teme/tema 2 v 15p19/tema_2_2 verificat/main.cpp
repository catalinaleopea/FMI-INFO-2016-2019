#include <iostream>
using namespace std;

struct Nod{
    int info;
    Nod *urm;
    };

Nod *prim,*ultim,*p,*q;

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
    Nod *p;
    p=prim;
    cout<<endl;
    while(p!=NULL){
        cout<<p->info<<' ';
        p=p->urm;
    }

}

void numere_pare(){
    p=prim;
    int nr=0;
    while(p!=NULL){
        if((p->info)%2==0)
            nr++;
        p=p->urm;
    }
    cout<<endl<<"numarul de numere pare este "<<nr;
}

void media_numere_impare(){
     p=prim;int nr=0,s=0;float media=0;
    while(p!=NULL){
        if((p->info)%2!=0){
           nr++;
           s=s+p->info;
        }
        p=p->urm;
    }
    media=s/nr;
    cout<<endl<<"media numerelor impare este "<<media;

}

int main(){

    adaugare_final(1);

    adaugare_inceput(2);

    adaugare_inceput(3);

    adaugare_final(4);

    adaugare_final(5);

    afisare();

    numere_pare();

    media_numere_impare();

    return 0;

}
