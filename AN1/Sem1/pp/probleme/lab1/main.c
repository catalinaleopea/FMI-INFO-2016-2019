#include <stdio.h>
#include <stdlib.h>
#include <math.h>
int main()
{int a,b,c,delta;
float x1,x2;
scanf("%d%d%d",&a,&b,&c);
printf("a=%db=%dc=%d",a,b,c);
delta=b*b-4*a*c;
if(delta==0)
    printf("o singura solutie %d",-b/(2*a));
    else if(delta<0)
        printf("nu exista solutii reale");
            else {x1=(-b+delta)/(2*a);
                 x2=(-b-delta)/(2*a);
                printf("exista doua solutii: x1=%d x2=%d",x1,x2);}
return 0;
}
