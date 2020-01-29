#include <stdio.h>
#include <stdlib.h>
#include "cod.h"
int main()
{char c;
scanf("%c",&c);
if(c>='A'&&c<='Z')
    {c=c+32;
    printf("%c",c);}
    else
        printf("%c",c);
return 0;
}
