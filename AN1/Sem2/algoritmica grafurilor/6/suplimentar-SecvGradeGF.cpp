#include <iostream>
#include <fstream>
#include <vector>
#include <list>

using namespace std;

class Flux
{
    int n, m, fl;
    vector<list<int>> listad;
    vector<list<int>> adjlist;
    vector<vector<pair<int, int>>> mat;
    vector<int> st, dr;
    list<int> path;
    vector<pair<int, int>> tai;
    vector<list<int>> path_list;
    vector<int> tata, viz, coada;
    int BFS();
    int max(int i, int j)
    {
        if (i > j) return i;
        return j;
    }
    vector<int> in, ex;
public:
    Flux()
    {
        n = m = fl = 0;
    }
    void citire();
    void afisare();
    void bipartitie(int);
    void set_Flux();
    void afisare_mat();
    void get_Flux();
    void af_Flux();
};


void Flux::citire()
{
    ifstream f("date.in");
    f >> n;
    int a;
    for (int i = 1; i <= n; i++)
    {
        f >> a;
        ex.push_back(a);
    }
    for (int i = 1; i <= n; i++)
    {
        f >> a;
        in.push_back(a);
    }
    m = n;
}

void Flux::afisare()
{
    cout << endl << "Grade externe: ";
    for (auto i : ex) cout << i << " ";
    cout << endl << "Grade interne: ";
    for (auto i : in) cout << i << " ";
    cout << endl;
}

void Flux::set_Flux()
{
    int a = n + m;
    listad.resize(a + 2);
    adjlist.resize(a + 2);
    mat.resize(a + 2);
    for (int i = 0; i <= a+1; i++)
        mat[i].resize(a + 2);
    for (int i = 0; i < n; i++)
    {
        mat[0][i + 1].first = ex[i];
        mat[i + 1][0].second = -1;
        listad[0].push_back(i + 1);
        adjlist[i + 1].push_back(0);
    }
    int ind = n + 1;
    for (unsigned int i = 0; i < in.size(); i++)
    {
        mat[ind][a + 1].first = in[i];
        mat[a + 1][ind].second = -1;
        listad[ind].push_back(a + 1);
        adjlist[a + 1].push_back(ind);
        ind++;
    }
    for (unsigned int i = 1; i <= ex.size(); i++)
    {
        for (int j = n + 1; j < ind; j++)
            if (i + n != j)
            {
                mat[i][j].first = 1;
                mat[j][i].second = -1;
                listad[i].push_back(j);
                adjlist[j].push_back(i);
            }
    }
    n = n + m;
}

void Flux::afisare_mat()
{
    cout << endl;
    for (int i = 0; i <= n; i++)
    {
        cout << i << ". ";
        for (int j = 0; j <= n; j++) cout << mat[i][j].first << "-" << mat[i][j].second << " ";
        cout << endl;
    }
    cout << endl;
}

int Flux::BFS()
{
    viz.assign(n + 2, 0);
    tata.assign(n + 2, 0);
    coada.clear();
    int li, ls;
    li = ls = 0;
    coada.push_back(0);
    viz[0] = 1;
    int pathh = 0;
    while (li <= ls)
    {
        int x = coada[li];
        for (auto i : listad[x])
        {
            if (viz[i] == 0)
                if ((mat[x][i].first - mat[x][i].second) != 0)
                {
                    viz[i] = 1;
                    tata[i] = x;
                    coada.push_back(i);
                    ls++;
                    if (i == n + 1)
                    {
                        pathh = 1;
                        break;
                    }
                }
        }
        for (auto i : adjlist[x])
        {
            if (viz[i] == 0)
                if (mat[x][i].first != 0)
                {
                    viz[i] = 1;
                    tata[i] = x;
                    coada.push_back(i);
                    ls++;
                    if (i == n + 1)
                    {
                        pathh = 1;
                        break;
                    }
                }
        }
        li++;
    }
    return pathh;
}

void Flux::get_Flux()
{
    while (BFS())
    {
        path.clear();
        int min = INT_MAX;
        int v = n + 1;
        while (v != 0)
        {
            path.push_back(v);
            int a;
            if (mat[tata[v]][v].second == -1) a = 0;
            else a = mat[tata[v]][v].second;
            if (min > (mat[tata[v]][v].first - a)) min = mat[tata[v]][v].first - a;
            v = tata[v];
        }
        path.push_back(0);
        path.reverse();
        list<int> *p = new list<int>;
        *p = path;
        path_list.push_back(*p);
        fl += min;
        v = n + 1;
        while (v != 0)
        {
            if (mat[tata[v]][v].second != -1)
            {
                mat[tata[v]][v].second += min;
                mat[v][tata[v]].first += min;
            }
            else
            {
                mat[tata[v]][v].first -= min;
                mat[v][tata[v]].second -= min;
            }
            v = tata[v];
        }
        cout << "Path cu minimul " << min << ": ";
        for (auto i : path)  cout << i << " ";
        cout << endl;
    }
}

void Flux::af_Flux()
{
    int s = 0;
    for (auto i : ex) s += i;
    if (fl < s) cout << endl << "Nu exista graf cu secventa de grade data!" << endl;
    else
    {
        cout << endl << "Exista graf!" << endl;
        for (int i = 1; i <= m; i++)
        {

            for (int j = m+1; j <= n; j++)
                if (mat[i][j].first != 0 && mat[i][j].second != -1)
                    if (mat[i][j].second != 0) cout << i << " " << j-m << endl;
        }
    }
}

int main()
{
    Flux ob1;
    ob1.citire();
    ob1.afisare();
    ob1.set_Flux();
    ob1.afisare_mat();
    ob1.get_Flux();
    ob1.af_Flux();
    return 0;
}
