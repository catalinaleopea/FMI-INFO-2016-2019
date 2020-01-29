#include <iostream>
#include <fstream>
#include <algorithm>
using namespace std;

typedef struct
{
    int latura,culoare;
} cub;

cub v[20];
int L[20], n, p, nrTurnuri[20], inaltimeMax[20];

void citire()
{
    ifstream in("date.in");
    in>>n>>p;
    for(int i = 1; i <= n; i++)
        in>>v[i].latura>>v[i].culoare;
    in.close();
}

bool compara(cub a, cub b)
{
    return (a.latura < b.latura);
}

void determinare()
{
    sort(v, v+n+1, compara); //crescator dupa latura
    int i,j;
    for(i = 1; i <= n; i++)
    {
        inaltimeMax[i] = v[i].latura;
        L[i] = -1;
        nrTurnuri[i] = 0;
    }
    inaltimeMax[0] = 0;
    nrTurnuri[0] = 1;

    for(i = 1; i <= n; i++)
        for(j = i-1; j >= 0; j--)
            if(v[j].latura < v[i].latura && v[i].culoare != v[j].culoare)
            {
                if(v[i].latura + inaltimeMax[j] > inaltimeMax[i])
                {
                    inaltimeMax[i] = inaltimeMax[j] + v[i].latura;
                    L[i] = j;
                    nrTurnuri[i] = nrTurnuri[j];
                }
                else if(v[i].latura + inaltimeMax[j] == inaltimeMax[i])
                {
                    nrTurnuri[i] = nrTurnuri[i] + nrTurnuri[j];
                }
            }
    ofstream out("date.out");
    i = n;
    while (i > 0 && L[i] == -1)
        i--;
    for (j = i; j > 0; j = L[j])
    {
        out << v[j].latura <<" " << v[j].culoare <<"\n";
    }
    out << nrTurnuri[n] <<"\n";
    out.close();
}

int main()
{
    citire();
    determinare();
    return 0;
}
