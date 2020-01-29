#include <iostream>
#include <fstream>
#include <list>
#define MAX 1000
using namespace std;

ifstream f("date.in");
list<int> *lista;
int timp,d[MAX],low[MAX],predecesor[MAX],critic[MAX];

void DFS(int varf)
{
    list<int>::iterator it;
    d[varf]=timp++;
    low[varf]=d[varf];
    for(it=lista[varf].begin();it!=lista[varf].end();it++)
        if(!d[*it])
        {
            predecesor[*it]=varf;
            DFS(*it);
            low[varf]=min(low[varf],low[*it]);
            if((low[*it]>=d[varf])&&d[varf]!=1)
                critic[varf]=1;
            if(low[*it]>d[varf])
                cout<<"("<<varf<<","<<*it<<") este muchie critica.\n";
        }
        else
            if(predecesor[varf]!=*it)
                low[varf]=min(low[varf],d[*it]);
}

int main()
{
    int n,m;
    f>>n>>m;
    lista=new list <int> [n+1];
    for(int i=0;i<m;i++)
    {
        int x,y;
        f>>x>>y;
        lista[x].push_back(y);
        lista[y].push_back(x);
    }
//    for(int i=1;i<=n;i++)
//    {
//        cout<<"Nodul "<<i<<" are vecinii: ";
//        for(list<int>::iterator it=lista[i].begin();it!=lista[i].end();it++)
//            cout<<*it<<' ';
//        cout<<'\n';
//    }
    for(int i=1;i<=n;i++)
        if(!d[i]){
            timp=1;DFS(i);
        }
    for(int i=1;i<=n;i++)
        if(critic[i])
            cout<<i<<" este punct de articulatie.\n";
    return 0;
}
