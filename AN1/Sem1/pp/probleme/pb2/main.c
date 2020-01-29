#include <stdio.h>
#include <stdlib.h>
int v[100],n,x,y,i,j;
int main()
{scanf("%d",&n);
for(i=1;i<=n;i++)
    scanf("%d,v[i]");
scanf("%d%d",&x,&y);
j=n;
for(i=1;i<=n;)
    {
    if (v[i]<x)i++;
    else if((v[i]==x)&&(v[j]<=y))
        printf(" %d",v[i]);
    }
return 0;
}
