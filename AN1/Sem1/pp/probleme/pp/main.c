#include <stdio.h>
#include <stdlib.h>
#include <math.h>
/*
int main()
{   int x=17248390;
    char *y=&x;
    printf("%x %x ",y,&x);
    printf(" %x ",y+1);
    printf("%d ",*y);
    return 0;
}
*/

/*
float rad(float x){
    return sqrt(x);
}

float inv(float x){
    return 1/x;
}

float sinus(float x){
    return sin(x);
}

int main(){
    float x;
    int i;
    float (*v[3])(float);
    v[0]=rad;
    v[1]=inv;
    v[2]=sinus;
    scanf("%f",&x);
    for(i=0;i<=2;i++)
        printf("%f",(*v[i])(x));
    return 0;
}
*/

int a[20][20];
