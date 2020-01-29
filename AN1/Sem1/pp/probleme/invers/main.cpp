#include <iostream>

using namespace std;

struct nod {int info;
 nod *leg;
 };
nod *prim;

void adaugs(nod *&prim,int x)
{if(prim)
 {nod *u=prim;
 while(u->leg) u=u->leg;
 nod *nou=new nod;
 nou->info=x;
 nou->leg=0;
 u->leg=nou;
 }
 else {prim=new nod;
 prim->info=x;
 prim->leg=0;
 }
}

void creare()
{int x=6,i;
for(i=1;i<=x;i++) adaugs(prim,i);
}
void afis(nod *prim)
{nod *p;
 p=prim;
 while(p)
 {cout<<p->info<<" ";
 p=p->leg;
 }
cout<<endl;
}
void invers(nod *&prim)
{nod *r,*p,*q;
 r=prim;
 p=prim->leg;
 q=prim->leg->leg;
 while(q) {
        p->leg-r;
 r=p;
 p=q;
 q=q->leg;
 }
 prim=p;
}
int main()
{creare();
 afis(prim);
 invers(prim);
 afis(prim);
 return 0;
}
