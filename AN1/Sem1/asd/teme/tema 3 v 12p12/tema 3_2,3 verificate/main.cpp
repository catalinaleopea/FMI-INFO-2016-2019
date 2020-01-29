#include <iostream>
#include <cmath>
using namespace std;

struct polinom_p{
    int grad_p,coeficient_p;
    polinom_p *urm;
}*prim,*p,*q;


struct polinom_q{
    int grad_q,coeficient_q;
    polinom_q *urm;
}*prim2,*p2,*q2;

//Subprogramele disponibile

void afisare_p();
void afisare_q();
void adaugare_p(int,int);
void adaugare_q(int,int);
void evaluare_p(int);
void evaluare_q(int);
void inmultire_p(int);
void inmultire_q(int);

void adaugare_p(int x,int y){
    polinom_p *p=new polinom_p;
    p->urm=prim;
    p->grad_p=x;
    p->coeficient_p=y;
    prim=p;
}

void adaugare_q(int x,int y){
    polinom_q *p2=new polinom_q;
    p2->urm=prim2;
    p2->grad_q=x;
    p2->coeficient_q=y;
    prim2=p2;
}


void afisare_p(){
    cout<<endl<<"p: ";
    for(p=prim;p->urm!=NULL;p=p->urm)
        cout<<p->coeficient_p<<"*x^"<<p->grad_p<<"+";
    cout<<p->coeficient_p<<"*x^"<<p->grad_p;
}

void afisare_q(){
    cout<<endl<<"q: ";
    for(p2=prim2;p2->urm!=NULL;p2=p2->urm)
        cout<<p2->coeficient_q<<"*x^"<<p2->grad_q<<"+";
    cout<<p2->coeficient_q<<"*x^"<<p2->grad_q;
}

void inmultire_p(int a){
    for(p=prim;p!=NULL;p=p->urm)
        p->coeficient_p=(p->coeficient_p)*a;
}

void inmultire_q(int a){
    for(p2=prim2;p2!=NULL;p2=p2->urm)
        p2->coeficient_q=(p2->coeficient_q)*a;
}

void evaluare_p(int x){
    int s=0;
    cout<<endl;
    for(p=prim;p!=NULL;p=p->urm)
        s=s+p->coeficient_p*pow(x,p->grad_p);
    cout<<"pentru x="<<x<<" polinomul p este egal cu "<<s;
}

void evaluare_q(int x){
    int s=0;
    cout<<endl;
    for(p2=prim2;p2!=NULL;p2=p2->urm)
        s=s+(p2->coeficient_q)*pow(x,p2->grad_q);
    cout<<"pentru x="<<x<<" polinomul q este egal cu "<<s;
}

int main(){

    int x,y,n,m,i,a;
    cout<<"n=";cin>>n;
    cout<<"m=";cin>>m;

    cout<<"Scrieti coeficientii polinomului p"<<endl;
    for(i=0,x=n;i<=n;i++,x--){
        cin>>y;
        adaugare_p(x,y);
    }
    cout<<"Scrieti coeficientii polinomului q "<<endl;
    for(i=0,x=m;i<=m;i++,x--){
        cin>>y;
        adaugare_q(x,y);
    }

    afisare_p();

    afisare_q();

    /*cout<<endl<<"pentru un scalar a=";
    cin>>a;
    cout<<"polinoamele devin:";

    inmultire_p(a);

    inmultire_q(a);

    afisare_p();

    afisare_q();
*/
/*
    cout<<endl<<"testeaza polinomul p pentru valoarea x=";cin>>a;
    evaluare_p(a);
    cout<<endl<<"testeaza polinomul q pentru valoarea x=";cin>>a;
    evaluare_q(a);

*/
return 0;
}
