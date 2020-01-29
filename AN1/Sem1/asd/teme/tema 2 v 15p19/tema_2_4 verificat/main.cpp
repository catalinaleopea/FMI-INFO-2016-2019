#include <iostream>
#include <string.h>
using namespace std;

struct Nod{
    int info;
    Nod *urm;
    };

struct Nod2{
    int info;
    Nod2 *urm;
    };

struct Suma{
    int info;
    Suma *urm;
    };

Nod *prim,*ultim,*p,*q;

Nod2 *prim2,*ultim2,*p2,*q2;

Suma *prim3,*ultim3,*p3,*q3;

int v[100];

void adaugare_final(int x){
    if(prim==NULL){
        prim=new Nod;
        prim->info=x;
        prim->urm=NULL;
        ultim=prim;
    }
    else{Nod *ultim=new Nod;
        Nod *p=new Nod;
        Nod *q=new Nod;
        p->info=x;
        q=prim;
        while(q->urm!=NULL)
            q=q->urm;
        ultim=q;
        ultim->urm=p;
        p->urm=NULL;
        ultim=p;
    }
}

void adaugare_final_2(int x){
    if(prim2==NULL){
        prim2=new Nod2;
        prim2->info=x;
        prim2->urm=NULL;
        ultim2=prim2;
    }
    else{Nod2 *ultim2=new Nod2;
        Nod2 *p2=new Nod2;
        Nod2 *q2=new Nod2;
        p2->info=x;
        q2=prim2;
        while(q2->urm!=NULL)
            q2=q2->urm;
        ultim2=q2;
        ultim2->urm=p2;
        p2->urm=NULL;
        ultim2=p2;
    }
}

void adaugare_final_s(int x){
    if(prim3==NULL){
        prim3=new Suma;
        prim3->info=x;
        prim3->urm=NULL;
        ultim3=prim3;
    }
    else{Suma *ultim3=new Suma;
        Suma *p3=new Suma;
        Suma *q3=new Suma;
        p3->info=x;
        q3=prim3;
        while(q3->urm!=NULL)
            q3=q3->urm;
        ultim3=q3;
        ultim3->urm=p3;
        p3->urm=NULL;
        ultim3=p3;
    }
}

void afisare_x(){
    p=prim;
    int i=0,nr=0;
    cout<<"x este ";
    while(p!=NULL){
        v[++i]=p->info;
        p=p->urm;
        nr++;
    }
    for(i=nr;i>=1;i--){
        cout<<v[i];
    }
    cout<<endl;
}

void afisare_y(){
    p2=prim2;
    int i=0,nr=0;
    cout<<"y este ";
    while(p2!=NULL){
        v[++i]=p2->info;
        p2=p2->urm;
        nr++;
    }
    for(i=nr;i>=1;i--){
        cout<<v[i];
    }
    cout<<endl;
}

void afisare_suma(){
    p3=prim3;
    int i=0,nr=0;
    cout<<"suma este ";
    while(p3!=NULL){
        v[++i]=p3->info;
        p3=p3->urm;
        nr++;
    }
    for(i=nr;i>=1;i--){
        cout<<v[i];
    }
    cout<<endl;
}

void suma(){
    int cifra=0;
    p=prim;
    p2=prim2;
    while((p!=NULL)&&(p2!=NULL)){
        cifra=cifra+(p->info)+(p2->info);
        p=p->urm;
        p2=p2->urm;
        if(cifra>9){
            adaugare_final_s(cifra%10);
            cifra=cifra/10;
        }
        else{
            adaugare_final_s(cifra);
            cifra=0;
        }
    }
    if(p!=NULL){
        while(p!=NULL){
            cifra=cifra+(p->info);
            p=p->urm;
        if(cifra>9){
            adaugare_final_s(cifra%10);
            cifra=cifra/10;
        }
        else{
            adaugare_final_s(cifra);
            cifra=0;
        }
        }
    }
    else {
            if(p2!=NULL){
                while(p2!=NULL){
                    cifra=cifra+(p2->info);
                    p2=p2->urm;
                if(cifra>9){
                    adaugare_final_s(cifra%10);
                    cifra=cifra/10;
                }
                else{
                    adaugare_final_s(cifra);
                    cifra=0;
                }
                }
            }

    }
    if(cifra)adaugare_final_s(cifra);
}

int main(){

    char s[100];

    short int c;
    int i;

    cout<<"Dati doua numere\n";

    cout<<"x= ";cin.getline(s,100);

    for(i=strlen(s)-1;i>=0;i--)
        adaugare_final(s[i]-'0');
    cout<<"y= ";cin.getline(s,100);
        for(i=strlen(s)-1;i>=0;i--)
        adaugare_final_2(s[i]-'0');

    afisare_x();

    afisare_y();

    suma();

    afisare_suma();

    return 0;

}
