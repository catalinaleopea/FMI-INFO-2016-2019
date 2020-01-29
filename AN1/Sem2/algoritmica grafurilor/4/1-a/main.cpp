//Kruskal
/**Implementaţi algoritmul lui Kruskal pentru
determinarea unui arbore parţial de cost minim
al unui graf conex ponderat cu n vârfuri și m muchii.*/
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

ifstream fin("grafpond.in");
ofstream fout("grafpond.out");

struct triplet
{
    int a,b,c;
    bool ex=0;
};

bool cmp(triplet a, triplet b)
{
    return a.c < b.c;
}

int gasesteTata(int nod, vector < pair <int, int> > &tata)
{
    if(tata[nod].first==nod)
        return nod;
    else
        return gasesteTata(tata[nod].first, tata);
}

void unireArbori(int v, int u, vector< pair <int, int> > &tata)
{
    if(tata[v].second>tata[u].second)
        tata[u].first=v;
    else if(tata[v].second<tata[u].second)
        tata[v].first=u;
    else
    {
        tata[u].first=v;
        tata[v].second++;
    }
}

int main()
{
    int n, m, cost=0;
    vector <triplet> muchii;
    vector < pair <int, int> > tata;
    fin>>n>>m;
    for(int i=0; i<m; i++)
    {
        int v, u, w;
        fin>>v>>u>>w;
        muchii.push_back(triplet());
        muchii[i].a=v;
        muchii[i].b=u;
        muchii[i].c=w;
    }
    sort(muchii.begin(), muchii.end(), cmp);
    tata.resize(n+1);
    for(int i=1; i<=n; i++)
        tata[i].first=i;
    int i=0, k=0;
    while(k<n-1)
    {
        int ta, tb;
        ta = gasesteTata(muchii[i].a, tata);
        tb = gasesteTata(muchii[i].b, tata);
        if(ta!=tb)
        {
            muchii[i].ex = 1;
            cost+=muchii[i].c;
            unireArbori(ta, tb, tata);
            k++;
        }
        i++;
    }
    fout<<"Costul total este "<<cost;
    fout<<" dupa parcurgerea a "<<n-1<<" muchii,respectiv:\n";
    for(int i=0; i<m; i++)
        if(muchii[i].ex)
            fout<<muchii[i].a<<' '<<muchii[i].b<<'\n';
    return 0;
}
