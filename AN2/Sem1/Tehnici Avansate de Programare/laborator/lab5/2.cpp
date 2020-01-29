#include <iostream>
#include <vector>
#include <fstream>
#include <limits>
using namespace std;

ifstream f("date.in");

vector< vector <int> > matrice;

void afisare(int i, int j)
{
    if(i == matrice.size() - 1 || j == 0)
        return;
    if(matrice[i + 1][j] >= matrice[i][j - 1])
        afisare(i + 1, j);
    else afisare(i, j - 1);
    cout<<i + 1<<" "<<j<<endl;
}

int main()
{
    int n, m, c;
    f>>n>>m;
    matrice.resize(n + 1);
    for(int i = 0; i < n + 1; i++)
        matrice[i].resize(m + 1);
    for(int i = 0; i < n; i++)
        for(int j = 1; j <= m; j++)
        {
            f>>c;
            matrice[i][j] = c;
        }
    for(int i = 0; i <= n; i++)
        matrice[i][0] = 0;
    for(int j = 0; j <= m; j++)
        matrice[n][j] = 0;
    for(int i = n - 1; i >= 0; i--)
        for(int j = 1; j <= m; j++)
            matrice[i][j] += max(matrice[i + 1][j], matrice[i][j - 1]);
    matrice[n - 1][1] = INT_MAX;
    cout<<matrice[0][m]<<endl;
    int i = 0, j = m;
    afisare(i, j);
    return 0;
}
