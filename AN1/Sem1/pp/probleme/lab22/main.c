#include <stdio.h>
#include <stdlib.h>
int main()
{int n,x;
scanf("%d%d",&x,&n);
printf("x=%d\nn=%d\n",x,n);
if((x&(1<<(n-1)))!=0)
    {printf("bitul %d",n);
     printf(" este 1");}
    else {printf("bitul %d",n);
          printf(" este 0");}

return 0;}
