#include <stdio.h>
#include <stdlib.h>
int main()
{int n,a,b;
scanf("%d",&n);
printf("n=%d\n",n);
a=n<<3;
b=n<<1;
printf("n*8=%d\nn/4=%d\nn*10=%d\n",n<<3,n>>2,(a+b));

return 0;
}

