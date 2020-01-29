#include <stdio.h>
#include <stdlib.h>
/* MAXIMUL A DOUA NR
int main()
{int a,b,max;
scanf("%d%d",&a,&b);
max=a>b?a:b;
    printf("%d",max);
    return 0;
}
*/



/* SWITCH
int main()
{int n;
scanf("%d",&n);
switch(n%10)
    {case 0:
        printf("NULL");
        break;
 case 1:
    printf("1");
 default:
    printf("cifra");

 }
    return 0;
}
*/


/*PROBLEMA 1*/
int f1[4000],f2[4000];
int main()
{int n,m,i,x;
scanf("%d%d",&n,&m);
for(i=1;i<=n;i++)
    {scanf("%d",&x);
    f1[x+2000]++;}
for(i=1;i<=m;i++)
{
    scanf("%d",&x);
    f2[x+2000]++;
}
for(i=1;i<=4000;i++)
{if(f1[i]&&f2[i])
printf("%d\n",i-2000);
}
return 0;
}


/*INDICATII PB 5
cu 4 foruri,parcurgem in rama toate cele n/2 sau (n+1)/2 rame */
