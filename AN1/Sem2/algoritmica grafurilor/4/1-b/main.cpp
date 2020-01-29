#include <iostream>
#include <algorithm>
#include <fstream>
#include <cstring>
#include <vector>

using namespace std;

struct muchie
{
    pair <int, string> a, b;
    int c;
};

class Clustering
{
    int k, n, nr_m, dist;
    vector<pair<int,string>> cuv;
    vector<muchie> m;
    vector<pair <pair <int, string>, int> > tata;
    vector<vector<string>> cluster_cuv;
    int distanta(string,string);
    int find(int);
    void unire(int,int);
    void APM();

public:
    void citire();
    void afisare();
    void cluster();
};

void Clustering::citire()
{
    ifstream f("cuvinte.in");
    int i = 1;
    string *p = new string, x;
    while (f >> *p)
    {
        cuv.push_back(make_pair(i,*p));
        i++;
        p = new string;
    }
    delete p;
    cout<<"Dati numarul de clase dorit ";
    cin >> k;
    n = cuv.size();
}

void Clustering::afisare()
{
    for (int i = 0; i < k; i++)
    {
        cout << i + 1 << ". ";
        for (auto j : cluster_cuv[i]) cout << j << " ";
        cout << endl;
    }
    cout << dist<< endl;
}

int Clustering::distanta(string cuv1, string cuv2)
{
    //calculeaza distanta dintre doua cuvinte
    const char *s1 = cuv1.data(), *s2 = cuv2.data();
    int n1 = strlen(s1);
    int n2 = strlen(s2);
    int *ci1 = new int[n2 + 1];
    int *ci = new int[n2 + 1];
    for (int j = 0; j <= n2; j++) ci1[j] = j;
    for (int i = 1; i <= n1; i++)
    {
        ci[0] = i;
        for (int j = 1; j <= n2; j++)
            if (s1[i - 1] == s2[j - 1]) ci[j] = ci1[j - 1];
            else ci[j] = 1 + min(min(ci1[j], ci[j - 1]), ci1[j - 1]);
        for (int j = 0; j <= n2; j++) ci1[j] = ci[j];
    }
    return ci[n2];
}

int Clustering::find(int x)
{
    //gasirea "tatalui" unui nod, pentru Kruskal
    if (tata[x].first.first == x) return x;
    else return find(tata[x].first.first);
}

void Clustering::unire(int x, int y)
{
    //functie de uniune pentru Kruskal
    if (tata[x].second > tata[y].second)
        tata[y].first.first = x;
    else if (tata[x].second < tata[y].second)
        tata[x].first.first = y;
    else
    {
        tata[y].first.first = x;
        tata[x].second++;
    }
}

void Clustering::APM()
{
    //calcularea unui arborelui partial minim pentru
    //n-k muchii, salvat in vectorul de tati din clasa
    tata.resize(n + 1);
    for (int i = 0; i < n; i++)
    {
        tata[cuv[i].first].first.first = cuv[i].first;
        tata[cuv[i].first].first.second = cuv[i].second;
    }
    int i = 0, h = 0;
    while (h < n - k)
    {
        int r1 = find(m[i].a.first);
        int r2 = find(m[i].b.first);
        if (r1 != r2)
        {
            //daca fac parte din arbori diferiti
            h++;
            //unim cei doi arbori partiali
            unire(r1, r2);
        }
        //si trecem la muchia urmatoare
        i++;
    }
}

int cmp(muchie &i, muchie &j)
{
    //sortarea muchiilor
    return i.c < j.c;
}

void Clustering::cluster()
{
    //crearea clusterului
    int n = cuv.size(), i, j;
    //creeaza muchiile unui graf complet pentru toate cuvintele cu
    //distantele dintre ele si le pune in vectorul m
    for(i=0; i<n-1; i++)
        for (j = i+1; j < n; j++)
            if (i != j)
            {
                m.push_back(muchie());
                m.back().a.first = cuv[i].first;
                m.back().a.second = cuv[i].second;
                m.back().b.first = cuv[j].first;
                m.back().b.second = cuv[j].second;
                m.back().c = distanta(cuv[i].second, cuv[j].second);
            }
    nr_m = m.size();
    sort(m.begin(), m.end(), cmp);
    //se face kruskal-ul pentru n-k muchii
    APM();
    //se pune in vectorul copie, pentru fiecare nod, radacina lui
    vector<pair<int, string>> copy(tata.size());
    for (int i = 1; i <= n; i++)
    {
        copy[i].first = find(tata[i].first.first);
        copy[i].second = tata[i].first.second;
    }
    //se calculeaza distanta minima parcurgand lista de muchii pana la gasirea
    //a doua extremitati din arbori diferiti, iar acea distanta este minima
    int ok = 1;
    i = 0;
    while (ok)
    {
        if (copy[m[i].a.first].first != copy[m[i].b.first].first)
        {
            dist = m[i].c;
            ok = 0;
        }
        i++;
    }
    //se pun cuvintele rezultate, fiecare la clasa lui in vectorul cluster_cuv
    cluster_cuv.resize(k);
    i = 0;
    int nn = n;
    //pentru fiecare clasa
    while (i < k)
    {
        //se ia prima radacina din vectorul copy
        int j = 1;
        int x = copy[j].first;
        //se adauga cuvantul la clasa lui
        cluster_cuv[i].push_back(copy[j].second);
        //se sterge din vector
        copy.erase(copy.begin());
        nn--;
        //si se cauta in continuarea vectorului toate nodurile care au aceeasi radacina
        while (j <= nn)
        {
            while (j <= nn&&copy[j].first != x) j++;
            if (j <= nn)
            {
                cluster_cuv[i].push_back(copy[j].second);
                copy.erase(copy.begin() + j);
                nn--;
            }
        }
        i++;
    }
}

int main()
{
    Clustering c;
    c.citire();
    c.cluster();
    c.afisare();
}
