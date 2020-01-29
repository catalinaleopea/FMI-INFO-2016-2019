#include <iostream>
using namespace std;
int v[100];
int main()
{int n,i,j,pozitia_minimului;
    cin>>n;
    for(i=1;i<=n;i++)
        cin>>v[i];
    for(i=1;i<=n-1;i++)
       {pozitia_minimului=i;
       for (j=i+1;j<=n;j++)
            {if(v[j]<v[pozitia_minimului])
            pozitia_minimului=j;}
        swap(v[pozitia_minimului],v[i]);
        }
for(i=1;i<=n;i++)
    cout<<v[i]<<' ';
return 0;
}
