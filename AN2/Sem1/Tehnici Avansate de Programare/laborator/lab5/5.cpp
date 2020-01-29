#include <iostream>
#include <fstream>
#include <algorithm>

using namespace std;

struct job{
    int id, profit, termenLimita, durata;
};

job jb[40];
int d[100][100];
int profit;

bool compara(const job &A, const job &B)
{
    return A.termenLimita < B.termenLimita;
}

void afisare(int i, int t)
{
    if(i == 0)
        return;
    if(d[i][t] == d[i - 1][t])
        afisare(i - 1, t);
    else{
        int t1 = min(t, jb[i].termenLimita) - jb[i].durata;
        afisare(i - 1, t1);
        cout<<jb[i].id<<" ";
        profit += jb[i].profit;
    }
}

int main(){
    ifstream in("date.in");
    int n;
    in>>n;
    int i = 1, j;
    while(i <= n){
        in>>jb[i].profit>>jb[i].termenLimita>>jb[i].durata;
        jb[i].id = i;
        i++;
    }
    sort(jb + 1, jb + n + 1, compara);
    for(i = 0; i <= jb[n].termenLimita; i++)
        d[0][i] = 0;
    int t1;
    for(i = 1; i <= n; i++){
        for(j = 0; j <= jb[n].termenLimita; j++){
            t1 = min(j, jb[i].termenLimita) - jb[i].durata;
            if(t1 < 0)
                d[i][j] = d[i - 1][j];
            else
                d[i][j] = max(d[i - 1][j], jb[i].profit + d[i - 1][t1]);
        }
    }
    afisare(n, jb[n].termenLimita);
    cout<<"\nProfit: "<<profit<<"\n";
    return 0;
}
