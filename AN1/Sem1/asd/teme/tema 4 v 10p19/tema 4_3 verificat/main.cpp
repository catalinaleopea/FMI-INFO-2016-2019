/*Fie lista simplu inlantuita C. Sa se distribuie elementele din C in doua liste
simplu inlatuite A si B, astfel: A contine elementele de pe pozitiile impare din C, iar B
contine elementele din C de pe pozitiile pare. Nu se va folosi memorie
suplimentara*/
#include <iostream>
using namespace std;

struct nod
{   int info;
    nod *next;
}*a, *b, *c;

void inserareFinal(nod *&p, int val){
    if (p==NULL){
        p=new nod;
        p->info=val;
        p->next=NULL;
    }
    else{
        nod *t=p;
        while (t->next!=NULL)
            t=t->next;
        nod *q=new nod;
        q->info=val;
        q->next=NULL;
        t->next=q;
    }
}
int main(){

    inserareFinal(c,1);
    inserareFinal(c,2);
    inserareFinal(c,3);
    inserareFinal(c,4);
  //  inserareFinal(c,5);
   // inserareFinal(c,6);

    nod *x,*y;

    for(int j=1;c!=NULL;c=c->next,j++){
        if(j%2==1){
            if(a==NULL){
                a=c;
                x=a;
            }
            else{
            x->next=c;
            x=x->next;}
        }
        else{
            if(b==NULL){
                b=c;
                y=b;
            }
            else{
            y->next=c;
            y=y->next;
            }
        }
    }
    x->next=NULL;
    y->next=NULL;

    cout<<"A:";
    while (a!=NULL){
        cout<<a->info<<" ";
        a=a->next;
    }

    cout<<"B:";
    while (b!=NULL){
        cout<<b->info<<" ";
        b=b->next;
     }
    return 0;
}
