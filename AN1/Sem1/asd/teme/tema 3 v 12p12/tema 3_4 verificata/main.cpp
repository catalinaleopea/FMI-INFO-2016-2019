#include <iostream>
using namespace std;

struct P{
int grad,coeficient;
P* next;}*prim,*ultim,*p,*q;

struct Q{
int grad2,coeficient2;
Q* next;}*prim2,*ultim2,*p2,*q2;

struct Suma{
int grad3,coeficient3;
Suma* next;}*prim3,*ultim3,*p3,*q3;

void adaugareFinalP(int grad,int value){
if(value!=0){
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
if(value!=0){
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
void adaugareFinalS(int grad,int value){
if(value!=0){
    Suma *p3=new Suma;
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
void gradeEgale(P *&p,Q*&p2){
    int x,y;
    while(p&&p2&&(p->grad==p2->grad2)){
            x=p->grad;
            y=(p->coeficient)+(p2->coeficient2);
            adaugareFinalS(x,y);
            p=p->next;
            p2=p2->next;
        }
}
void gradMare(P *&p,Q*&p2){
    int x,y;
    while(p&&p2&&(p->grad>p2->grad2)){
            x=p->grad;
            y=p->coeficient;
            adaugareFinalS(x,y);
            p=p->next;
        }}
void gradMic(P *&p,Q*&p2){
    int x,y;
    while(p&&p2&&(p->grad<p2->grad2)){
            x=p2->grad2;
            y=p2->coeficient2;
            adaugareFinalS(x,y);
            p2=p2->next;
        }}
void suma(){
p=prim;p2=prim2;
int x,y;
while(p!=NULL&&p2!=NULL){
    gradeEgale(p,p2);
    gradMare(p,p2);
    gradMic(p,p2);

}
    while(p){
        x=p->grad;
        y=p->coeficient;
        adaugareFinalS(x,y);
        p=p->next;
    }
    while(p2){
        x=p2->grad2;
        y=p2->coeficient2;
        adaugareFinalS(x,y);
        p2=p2->next;
    }
}

void afisareP(){
    cout<<endl<<"p: ";
    for(p=prim;p->next!=NULL;p=p->next)
        cout<<p->coeficient<<"*x^"<<p->grad<<"+";
    cout<<p->coeficient<<"*x^"<<p->grad<<"=0";
}

void afisareQ(){
    cout<<endl<<"q: ";
    for(p2=prim2;p2->next!=NULL;p2=p2->next)
        cout<<p2->coeficient2<<"*x^"<<p2->grad2<<"+";
    cout<<p2->coeficient2<<"*x^"<<p2->grad2<<"=0";
}

void afisareSuma(){
    cout<<endl<<"suma: ";
    for(p3=prim3;p3->next!=NULL;p3=p3->next)
        cout<<p3->coeficient3<<"*x^"<<p3->grad3<<"+";
    cout<<p3->coeficient3<<"*x^"<<p3->grad3<<"=0";
}

int main(){
adaugareFinalP(2,1);
adaugareFinalP(1,1);
adaugareFinalQ(1,1);
adaugareFinalQ(0,2);
afisareP();
afisareQ();
suma();
afisareSuma();
return 0;
}
