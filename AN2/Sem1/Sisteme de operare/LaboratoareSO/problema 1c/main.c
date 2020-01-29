#include <stdio.h>
#include <stdlib.h>
int main(int argc, char **argv)
///int main()
{
    ///char *w,*e;
    ///w = (char*)malloc(1000*sizeof(char));
    ///e = (char*)malloc(1000*sizeof(char));
    ///scanf("%s",w);
    ///scanf("%s",e);
    printf("%s",argv[1]);
    printf("%s",argv[2]);
    FILE *input, *output;
    input = fopen(argv[1],"r");
    output = fopen(argv[2],"w");
    input = fopen(argv[1],"r");
    output = fopen(argv[2],"w");
    if(argc != 3)
    {
        printf("Invalid input/n");
        return 0;
    }
    if(input == NULL)
    {
        printf("Fisierul de input nu s-a putut deschide/n");
        return 0;
    }
    if(output == NULL)
    {
        printf("Fisierul de output nu s-a putut deschide/n");
        return 0;
    }
    char *q;
    q = (char*)malloc(10001*sizeof(char));
    while(fgets(q,10000,input) != NULL)
    {
        fprintf(output,"%s",q);
    }
    printf("Fisier copiat cu succes");
    return 0;
}
