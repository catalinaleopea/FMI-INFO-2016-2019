#include <iostream>
#include <fstream>
#include <string.h>
using namespace std;

//ifstream in("date.in");

int scor[3][3], f[20][20];

int S(char s1,char s2)
{
    int si, sj;
    switch(s1)
    {
    case 'A':
    {
        si = 0;
        break;
    }
    case 'C':
    {
        si = 1;
        break;
    }
    case 'G':
    {
        si = 2;
        break;
    }
    default :
    {
        si = 3;
    }
    }

    switch(s2)
    {
    case 'A':
    {
        sj = 0;
        break;
    }
    case 'C':
    {
        sj = 1;
        break;
    }
    case 'G':
    {
        sj = 2;
        break;
    }
    default :
    {
        sj = 3;
    }
    }
    return scor[si][sj];
}

int main()
{
    int i, j;
    char s1[] = "GATC";//"GAATTCAGTTA";
    char s2[] = "TCAG";//"GGATCGA";
    for(i = 0; i <= 3; i++){
        for(j = 0; j <= 3; j++){
            if(i == j)
                scor[i][j] = 1;
            else
                scor[i][j] = 0;
        }
    }
    int spatiu = -1;
    for(i = 0; i <= strlen(s1); i++)
        f[i][0] = spatiu * i;
    for(j = 0; j <= strlen(s2); j++)
        f[0][j] = spatiu * j;
    for(i = 1; i <= strlen(s1); i++)
        for(j = 1; j <= strlen(s2); j++){
            int Match = f[i - 1][j - 1] + S(s1[i - 1], s2[j - 1]);
            int Delete = f[i - 1][j] + spatiu;
            int max1 = max(Match, Delete);
            int Insert = f[i][j - 1] + spatiu;
            f[i][j] = max(max1, Insert);
        }
    string aranjare1 = "";
    string aranjare2 = "";
    i = strlen(s1);
    j = strlen(s2);
    while (i > 0 || j > 0){
        if (i > 0 && j > 0 && (f[i][j] == f[i - 1][j - 1] + S(s1[i - 1], s2[j - 1]))){
            aranjare1 = s1[i - 1] + aranjare1;
            aranjare2 = s2[j - 1] + aranjare2;
            i--; j--;
        }
        else if (i > 0 && f[i][j] == f[i-1][j] + spatiu){
            aranjare1 = s1[i - 1] + aranjare1;
            aranjare2 = "-" + aranjare2;
            i--;
            }
            else{
                aranjare1 = "-" + aranjare1;
                aranjare2 = s2[j - 1] + aranjare2;
                j--;
            }
    }
    cout<<aranjare1<<"\n"<<aranjare2<<"\n";
    cout<<"Scor: "<<f[strlen(s1)][strlen(s2)];
    return 0;
}
