#include <iostream>
using namespace std;
int v1[100],v2[100];
struct V1{
int indice,valoare;
V1* next;}*prim,*ultim,*p,*q;

struct V2{
int indice2,valoare2;
V2* next;}*prim2,*ultim2,*p2,*q2;

struct Suma{
int indice3,valoare3;
Suma* next;}*prim3,*ultim3,*p3,*q3;

void adaugareFinalV1(int grad,int value){
if(value!=0){
    V1 *p=new V1;
    p->indice=grad;
    p->valoare=value;
    p->next=NULL;
    if(prim==NULL){
        prim=ultim=p;
        return;}
    ultim->next=p;
    ultim=p;
    }
}

void adaugareFinalV2(int grad,int value){
if(value!=0){
    V2 *p2=new V2;
    p2->indice2=grad;
    p2->valoare2=value;
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
    p3->indice3=grad;
    p3->valoare3=value;
    p3->next=NULL;
    if(prim3==NULL){
        prim3=ultim3=p3;
        return;}

   ultim3->next=p3;
   ultim3=p3;
}
}
void indiciEgali(V1 *&p,V2*&p2){
    int x,y;
    while(p&&p2&&(p->indice==p2->indice2)){
            x=p->indice;
            y=(p->valoare)+(p2->valoare2);
            adaugareFinalS(x,y);
            p=p->next;
            p2=p2->next;
        }
}
void indiceMare(V1 *&p,V2*&p2){
    int x,y;
    while(p&&p2&&(p->indice>p2->indice2)){
            x=p->indice;
            y=p->valoare;
            adaugareFinalS(x,y);
            p=p->next;
        }}
void indiceMic(V1 *&p,V2*&p2){
    int x,y;
    while(p&&p2&&(p->indice<p2->indice2)){
            x=p2->indice2;
            y=p2->valoare2;
            adaugareFinalS(x,y);
            p2=p2->next;
        }}
void suma(){
p=prim;p2=prim2;
int x,y;
while(p!=NULL&&p2!=NULL){
    indiciEgali(p,p2);
    indiceMare(p,p2);
    indiceMic(p,p2);

}
    while(p){
        x=p->indice;
        y=p->valoare;
        adaugareFinalS(x,y);
        p=p->next;
    }
    while(p2){
        x=p2->indice2;
        y=p2->valoare2;
        adaugareFinalS(x,y);
        p2=p2->next;
    }
}

void afisareP(){
    cout<<endl<<"V1: ";
    for(p=prim;p!=NULL;p=p->next)
        cout<<"v1["<<p->indice<<"]="<<p->valoare<<" ";
}

void afisareQ(){
    cout<<endl<<"V2: ";
    for(p2=prim2;p2!=NULL;p2=p2->next)
    cout<<"v2["<<p2->indice2<<"]="<<p2->valoare2<<" ";
}

void afisareSuma(){
    cout<<endl<<"suma: ";
    for(p3=prim3;p3!=NULL;p3=p3->next)
    cout<<"v["<<p3->indice3<<"]="<<p3->valoare3<<" ";
}

int main(){
adaugareFinalV1(5,3);
adaugareFinalV1(3,2);
adaugareFinalV1(1,1);
adaugareFinalV2(7,3);
adaugareFinalV2(5,2);
adaugareFinalV2(3,1);
afisareP();
afisareQ();
suma();
afisareSuma();
return 0;
}
