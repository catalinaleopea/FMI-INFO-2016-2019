#include <iostream>
using namespace std;
int v[100],i,j,n,k,ok=0;
int main()
    {cin>>n;
    for(i=1;i<=n;i++)
        cin>>v[i];
    cin>>k;
        {for(i=1;i<=n/2&&ok==0;i++)
            for(j=n;j>=n/2;j--)
                if(k==v[i]||k==v[j])
                    ok=1;
        }
    if(ok)
        cout<<"s-a gasit";
        else cout<<"nu s-a gasit";
    return 0;
    }
