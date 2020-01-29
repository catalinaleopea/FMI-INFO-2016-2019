#include <iostream>
#include <fstream>

using namespace std;

ifstream fin("date.in");
ofstream fout("date.out");

struct lista
{
	int id,colegi;
	lista *next;
}*prim,*ultim;

void inserare(int i,int x)
{
	if(prim==NULL)
	{
		prim=new lista;
		prim->id=i;
		prim->colegi=x;
		prim->next=NULL;
		ultim=prim;
	}
	else
	{
		lista *p=new lista;
		p->id=i;
		p->colegi=x;
		p->next=NULL;
		ultim->next=p;
		ultim=p;
	}
}

int main()
{
	int n,suma=0;
	fin>>n;
	for(int i=1;i<=n;i++)
	{
		int x;
		fin>>x;
		inserare(i,x);
		suma=suma+x;
	}
	if(suma%2==1)
		fout<<"Nu se poate forma";
	else//daca suma gradelor e para exista graf
        if(suma!=2*n-2) //verificam sa nu fie arbore
        {
            lista *p=prim;
            for(;p!=NULL;p=p->next)
            {
                lista *q=p->next;
                for(;(p->colegi)&&(q!=NULL);q=q->next)
                {
                    fout<<p->id<<' '<<q->id<<'\n';
                    (p->colegi)--;
                    (q->colegi)--;
                }
            }
        }
    return 0;
}
