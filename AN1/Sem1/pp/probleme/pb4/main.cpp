#include <iostream>
using namespace std;

struct P{
    int grad,coeficient;
    P* next;
}*prim,*p,*q;

struct Q{
    int grad2,coeficient2;
    Q* next;
}*prim2,*p2,*q2;

struct Suma{
    int grad3,coeficient3;
    Suma* next;
}*prim3,*p3,*q3;

void adaugareFinalP(int grad,int value){
if(value!=0){
    P *p=new P;
    p->grad=grad;
    p->coeficient=value;
    p->next=NULL;
    if(prim==NULL)
        prim=p;
    else{P *q=new P;
        while(q->next!=NULL)
          q=q->next;
        q->next=p;
        p->next=NULL;
    }
}
}

void adaugareFinalQ(int grad,int value){
if(value!=0){
    Q *p2=new Q;
    p2->grad2=grad;
    p2->coeficient2=value;
    p2->next=NULL;
    if(prim2==NULL)
        prim2=p2;
    else{Q *q2=new Q;
        while(q2->next!=NULL)
          q2=q2->next;
        q2->next=p2;
    }
}
}

void adaugareFinalSuma(int grad,int value){
    Suma *p3=new Suma;
    p3->grad3=grad;
    p3->coeficient3=value;
    p3->next=NULL;
    if(prim3==NULL)
        prim3=p3;
    else{Suma *q3=new Suma;
        while(q3->next!=NULL)
          q3=q3->next;
        q3->next=p3;
    }
}

void suma(){
    int valoare=0;
    for(p=prim,p2=prim2;((p->grad)==(p2->grad2))&&p&&p2;p=p->next,p2=p2->next){
        valoare=(p->coeficient)+(p2->coeficient2);
        if(valoare)
            adaugareFinalSuma(p->grad,valoare);
    }
    if(p&&(p2==NULL))
        do{
            valoare=p->coeficient;
            if(valoare)
                adaugareFinalSuma(p->grad,valoare);
            p=p->next;
        }while(p!=NULL);
        else
            if((p==NULL)&&p2)
                do{
                    valoare=p2->coeficient2;
                    if(valoare)
                        adaugareFinalSuma(p2->grad2,valoare);
                    p2=p2->next;
                }while(p2!=NULL);

}

void afisareP(){
    cout<<endl<<"p: ";
    for(p=prim;p->next!=NULL;p=p->next)
        cout<<p->coeficient<<"*x^"<<p->grad<<"+";
    cout<<p->coeficient<<"*x^"<<p->grad;
}

void afisareQ(){
    cout<<endl<<"q: ";
    for(p2=prim2;p2->next!=NULL;p2=p2->next)
        cout<<p2->coeficient2<<"*x^"<<p2->grad2<<"+";
    cout<<p2->coeficient2<<"*x^"<<p2->grad2;
}

void afisareSuma(){
    cout<<endl<<"suma: ";
    for(p3=prim3;p3->next!=NULL;p3=p3->next)
        cout<<p3->coeficient3<<"*x^"<<p3->grad3<<"+";
    cout<<p3->coeficient3<<"x^"<<p3->grad3;
}

int main(){
int n,m,i,j;
    cout<<"n=";cin>>n;
    cout<<"m=";cin>>m;

    cout<<"Scrieti coeficientii polinomului p"<<endl;
    for(i=0;i<=n;i++){
        cin>>j;
        adaugareFinalP(i,j);
    }
    cout<<"Scrieti coeficientii polinomului q "<<endl;
    for(i=0;i<=m;i++){
        cin>>j;
        adaugareFinalQ(i,j);
    }
    afisareP();

    afisareQ();

    /*suma();

    afisareSuma();
*/
return 0;
}
