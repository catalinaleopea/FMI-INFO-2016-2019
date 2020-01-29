#include <stdio.h>
#include <stdlib.h>

/*
union alfa
{
    char ch[3];
    int y;
} beta;
int main(){
     printf("Memoria ocupata de beta este de %d octeti", sizeof(beta));
    return 0;
}

int main() {
 union alfa gamma;
   gamma.y = 3;
     strcpy(gamma.ch,"Da");
       printf("gamma.y: %d", gamma.y); //ce observati?
 printf("gamma.ch: %s", gamma.ch);  return 0; }
*/
 int main(){
      enum saptamana {    Luni,  Marti,  Miercuri,  Joi,  Vineri,  Sambata,  Duminica }zi;

     for(zi = Luni; zi <= Duminica; zi++)
        {   printf("%d ", zi);  }  return 0; }
