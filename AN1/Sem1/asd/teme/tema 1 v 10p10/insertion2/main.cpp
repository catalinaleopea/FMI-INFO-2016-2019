#include <iostream>
using namespace std;
int v[100],n,i,j;
int main()
    {cin>>n;
    for(i=1;i<=n;i++)
        cin>>v[i];
    for(i=2;i<=n;i++)
        {j=i;
        while(j>1&&v[j]<v[j-1])
            {swap(v[j],v[j-1]);
            j--;
            }
        }
    for(i=1;i<=n;i++)
        cout<<v[i]<<' ';
    return 0;
    }
