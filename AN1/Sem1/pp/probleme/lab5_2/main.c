#include <stdio.h>
#include <stdlib.h>
/*
union{
int  x;
char nr [2];
double y;
}t;

int main(){
    int aux;
    scanf("%d",&t.x);
    aux=t.nr[0];
    t.nr[0]=t.nr[1];
    t.nr[1]=aux;
    printf("%d",t.x);

return 0;
}
*/

/* nu merge
union{
    char adresa[100];
    int suprafata;
    char tip[30];
    int camere;
    union{
    int balcon;
    char decomandat;
    char tip_casa;
    };
};

int main(){
    int n,max=0;
    char adresa_cautata;
    scanf("%d",&n);


    if(balcon){
        if(suprafata>max){
            max=suprafata;
            adresa_cautata=adresa;
        }
    }
return 0;}
*/

//1masculin,2feminin

union{
short int varsta;
char nume[30];
char norma[10];
char cnp[14];
}angajat;

int main(){
printf("%d",sizeof(angajat));
return 0;

if (cnp[0]==1)
    if(varsta<31) // cu operatori pe biti

}
