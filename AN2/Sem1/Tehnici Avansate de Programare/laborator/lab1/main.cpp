#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
using namespace std;
ifstream fin("date.in");
ofstream fout("date.out");
int func(int i,int j)
{
    return (i>j);
}
int main()
{
    int n,n2=0,s=0,s2=0;
    fin>>n;
    vector<int>v;
    vector<int>v2;
    v.resize(n);
    v2.resize(n);
    for(int i=0; i<n; i++)
    {
        int x;fin>>x;
        v.push_back(x);
        v2[i]=0;
    }
    fin>>s;
    sort(v.begin(),v.end(),func);
    while(n2<=n)
    {
        if(v[n2]+s2<=s)
        {
            s2=s2+v[n2];
            v2[n2]++;
        }
        else n2++;
    }
    if(s2!=s)
    {
        int x=-1;
        fout<<x;
    }
    else
        for(int i=0; i<n; i++)
            fout<<v2[i]<<' ';
    return 0;
}
