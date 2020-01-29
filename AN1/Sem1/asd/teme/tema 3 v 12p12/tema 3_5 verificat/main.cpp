/*
a: 2|3|->1|2|->0|2->NULL
b: 1|1->0|2->NULL

//inmultim primul element din lista b cu toate elementele listei a
//rezultatul se va salva progresiv intr-o noua lista
//adunam elementele din grad si inmultim elementele din coeficient
3|3->2|2->1|2
//cand inmultim al doilea element din b cu toate din lista a
//avem grija sa inseram nodurile dupa grad unde trebuie,si la grade egale sa adunam coeficientii
3|3->2|3+2->1|2+2->0|4->NULL
3|3->2|5->1|4->0|4->NULL
//parcurgem toate elementele din b
//afisam c
functii pt citire a,b
afisare a,b,c
inmultire
inserare c(dupa insertion sort)
*/
#include <iostream>
using namespace std;


struct P{
int grad,coeficient;
P* next;}*prim,*ultim,*p;

struct Q{
int grad2,coeficient2;
Q* next;}*prim2,*ultim2,*p2;

struct Produs{
int grad3,coeficient3;
Produs* next;}*prim3,*ultim3,*p3;

void adaugareFinalP(int grad,int value){
if(value){
    P *p=new P;
    p->grad=grad;
    p->coeficient=value;
    p->next=NULL;
    if(prim==NULL){
        prim=ultim=p;
        return;}
    ultim->next=p;
    ultim=p;
    }
}

void adaugareFinalQ(int grad,int value){
if(value){
    Q *p2=new Q;
    p2->grad2=grad;
    p2->coeficient2=value;
    p2->next=NULL;
    if(prim2==NULL){
        prim2=ultim2=p2;
        return;}

   ultim2->next=p2;
   ultim2=p2;
}
}
void adaugareFinalProdus(int grad,int value){
if(value){
    Produs *p3=new Produs;
    p3->grad3=grad;
    p3->coeficient3=value;
    p3->next=NULL;
    if(prim3==NULL){
        prim3=ultim3=p3;
        return;}

   ultim3->next=p3;
   ultim3=p3;
}
}
void adaugareInceputProdus(int grad,int value){
    Produs* p3=new Produs;
    if(value){
        p3->coeficient3=value;
        p3->grad3=grad;
    }
    if(prim3==NULL){
        p3->next=NULL;
        prim3=ultim3=p3;
        return;
    }
    p3->next=prim3;
    prim3=p3;
}

void adaugareInsertieProdus(int grad,int value){
    p3=prim3;
    if(prim3==NULL||p3->grad3<grad){
        adaugareInceputProdus(grad,value);
        return;
    }
    if(p3->grad3==grad){
        p3->coeficient3=p3->coeficient3+value;
        return;
    }
    while(p3->next!=NULL&&p3->next->grad3>=grad)
        p3=p3->next;
    if(p3->grad3==grad){
        p3->coeficient3=p3->coeficient3+value;
        return;
    }
    Produs *q3=new Produs;
    q3->coeficient3=value;
    q3->grad3=grad;
    q3->next=p3->next;
    p3->next=q3;
}

void afisareP(){
    cout<<endl<<"p: ";
    for(p=prim;p->next!=NULL;p=p->next){
        if(p->coeficient!=1)
            cout<<p->coeficient<<"*x^"<<p->grad<<"+";
        else
            cout<<"x^"<<p->grad<<"+";}
    if(p->grad!=0){
        if(p->coeficient!=1)
            cout<<p->coeficient<<"*x^"<<p->grad<<"=0";
        else
            cout<<"x^"<<p->grad<<"=0";}
    else
        cout<<p->coeficient<<"=0";
}

void afisareQ(){
    cout<<endl<<"q: ";
    for(p2=prim2;p2->next!=NULL;p2=p2->next){
       if(p2->coeficient2!=1)
            cout<<p2->coeficient2<<"*x^"<<p2->grad2<<"+";
        else
            cout<<"x^"<<p2->grad2<<"+";}
    if(p2->grad2!=0){
        if(p2->coeficient2!=1)
            cout<<p2->coeficient2<<"*x^"<<p2->grad2<<"=0";
        else
            cout<<"x^"<<p2->grad2<<"=0";}
    else
        cout<<p2->coeficient2<<"=0";
}

void afisareProdus(){
    cout<<endl<<"produs: ";
    for(p3=prim3;p3->next!=NULL;p3=p3->next){
        if(p3->coeficient3!=1)
            cout<<p3->coeficient3<<"*x^"<<p3->grad3<<"+";
        else
            cout<<"x^"<<p3->grad3<<"+";}
    if(p3->grad3!=0){
        if(p3->coeficient3!=1)
            cout<<p3->coeficient3<<"*x^"<<p3->grad3<<"=0";
        else
            cout<<"x^"<<p3->grad3<<"=0";}
    else
        cout<<p3->coeficient3<<"=0";
}

void inmultire(){
    int x,y;
    for(p=prim;p!=NULL;p=p->next)
        for(p2=prim2;p2!=NULL;p2=p2->next){
            Produs *q3=new Produs;
            q3->grad3=(p->grad)+(p2->grad2);
            q3->coeficient3=p->coeficient*p2->coeficient2;
            x=q3->grad3;
            y=q3->coeficient3;
            adaugareInsertieProdus(x,y);
        }
}

int main(){

    adaugareFinalP(2,1);
    adaugareFinalP(1,1);
    adaugareFinalQ(1,1);
    adaugareFinalQ(0,2);
    afisareP();
    afisareQ();
    inmultire();
    afisareProdus();

    return 0;
}
