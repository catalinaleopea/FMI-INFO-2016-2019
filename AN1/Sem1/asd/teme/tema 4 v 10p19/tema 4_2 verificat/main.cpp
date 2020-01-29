#include <iostream>
using namespace std;

int n,m;
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
    /*int i,x;
    cout<<"Scrieti numarul de elemente din lista A: ";
    cin>>n;
    cout<<"Dati cele "<<n<<" elemente,in ordine crescatoare:"<<endl;

    for (i=1; i<=n; i++){
        int x;
        cin>>x;
        inserareFinal(a,x);
    }
    cout<<"Scrieti numarul de elemente din lista B: ";
    cin>>m;
    cout<<"Dati cele "<<m<<" elemente, in ordine crescatoare:"<<endl;
    for (i=1; i<=m; i++){
        cin>>x;
        inserareFinal(b,x);
    }*/
    inserareFinal(a,1);
    inserareFinal(a,3);
    inserareFinal(a,5);
    inserareFinal(b,2);
    inserareFinal(b,4);
    inserareFinal(b,6);
    nod *t;
    while (a!=NULL && b!=NULL){
        if (c==NULL){
            if (a->info <= b->info){
                c=a;
                a=a->next;
                t=c;
            }
            else {
                c=b;
                b=b->next;
                t=c;
            }
        }
        else{
            if(a->info <= b->info){
                t->next=a;
                a=a->next;
            }
            else{
                t->next=b;
                b=b->next;
            }
            t=t->next;
        }
    }
    while (a){
        t->next=a;
        a=a->next;
        t=t->next;
    }
    while (b){
        t->next=b;
        b=b->next;
        t=t->next;
    }
    cout<<"lista C (contine elementele din A si din B in ordine crescatoare):"<<endl;
    while (c!=NULL){
        cout<<c->info<<" ";
        c=c->next;
    }
    return 0;
}
