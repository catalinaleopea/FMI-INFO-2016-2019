#include <iostream>
#include <vector>
#include <stack>
#include <fstream>

using namespace std;

ifstream in("activitati.in");
ofstream out("date.out");

void DFS(vector < vector < pair <int, int> > > la, vector <int> &distanta, vector <int> &tata, int nod)
{
    for(int i=0;i<la[nod].size();i++)
    {
        if(distanta[la[nod][i].first]<=distanta[nod]+la[nod][i].second)
        {
            distanta[la[nod][i].first]=distanta[nod]+la[nod][i].second;
            tata[la[nod][i].first]=nod;
        }
        DFS(la, distanta, tata, la[nod][i].first);
    }
}

int main()
{
    int n,m;
    in>>n;
    vector <int> cost(n+1);
    for(int i=1;i<cost.size();i++)//Vectorul cu costurile fiecarei activitati
    {
        int w;
        in>>w;
        cost[i]=w;
    }
    vector < vector < pair <int, int> > > la(n+2);//Lista de adiacenta
    vector <int> grad_int (n+1);
    vector <int> grad_ext (n+1);//Pentru a determina nodurile de start si de finish
    in>>m;
    for(int i=0;i<m;i++)//Creez lista de adiacenta
    {
        int u,v;
        in>>u>>v;
        la[u].push_back(make_pair(v, cost[u]));//Avem cele 2 noduri si costul activitatiilor
        grad_ext[u]++;
        grad_int[v]++;
    }
    for(int i=1;i<grad_ext.size();i++)
        if(!grad_ext[i])
            la[i].push_back(make_pair(n+1, cost[i]));
    for(int i=1;i<grad_int.size();i++)
        if(!grad_int[i])
            la[0].push_back(make_pair(i, 0));
    out<<"Graful este\n\n";
    for(int i=0;i<la.size();i++)
    {
        out<<i<<": ";
        for(int j=0;j<la[i].size();j++)
            out<<la[i][j].first<<','<<la[i][j].second<<' ';
        out<<'\n';
    }
    out<<'\n';
    vector <int> distanta (n+2);
    vector <int> tata (n+2);
    DFS(la, distanta, tata, 0);
    out<<"Timp minim "<<distanta[n+1]<<'\n';
    int nod=tata[n+1];
    stack <int> drum;
    while(nod)
    {
        drum.push(nod);
        nod=tata[nod];
    }
    out<<"Activitati critice: ";
    while(!drum.empty())
    {
        nod=drum.top();
        drum.pop();
        out<<nod<<' ';
    }
    out<<'\n';
    for(int i=1;i<=n;i++)
        out<<i<<": "<<distanta[i]<<' '<<distanta[i]+cost[i]<<'\n';
    return 0;
}
