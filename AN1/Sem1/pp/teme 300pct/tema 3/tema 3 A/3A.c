/**A. Scrieți un program C ce rezolvă 2 dintre problemele următoare, la alegere. 40p.
Se citesc fraze din fisierul “date.in” (pot fi incluse si numere) iar in fisierul “date.out”
se va scrie fișierul prelucrat astfel încât:
 să apară numai cuvintele, cu litere mici, separate printr-un singur spatiu
(fara semne de punctuatie sau spatii multiple). Fisierul “date.in” poate contine pana la 3.000.000.000 de caractere;
 să apară numai numerele;
 să apară toate cuvintele care conțin numai vocale;
 să apară cuvintele care conțin cratimă;
 să se înlocuiască un cuvânt cu altul (ambele citite de la tastatură);
 să se șteargă toate cuvintele ce încep cu majusculă.
**/
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

void Meniu(FILE *fin)
{
    FILE *fout;
    char *numeFisier2="date out.txt";
    fout=fopen(numeFisier2,"w");
    //Verificam daca fisierul "date out.txt" a fost deschis cu succes
    if(fout==NULL)
    {
        printf("Eroare la deschiderea fisierului");
        exit(0);
    }
    else
    {
        printf("Am deschis fisierul %s \n",numeFisier2);
        char x='Y';
    do{
        int selectie;
        do
        {
            printf("Alegeti functia dorita:\n");
            printf("1)Sa apara numai cuvintele, cu litere mici, separate printr-un singur spatiu.\n");
            printf("2)Sa apara numai numerele.\n");
            scanf("%d",&selectie);
        }while (selectie!=1&&selectie!=2);
        switch (selectie)
        {
            case 1:
            {
                ///freopen(numeFisier2,"w",fout);
                //inchide daca a fost deschis anterior si deschide gol fisierul pentru output
                rewind(fin);
                fprintf(fout,"\n1)Numai cuvintele, cu litere mici, separate printr-un singur spatiu.\n");
                char c;//parcurgem caracter cu caracter fisierul,in variabila c
                char anterior;//memoram in caracterul anterior ce am scris ultima data in fisier
                            // pentru a evita scrierea mai multor spatii
                while(c!= EOF)
                {
                    c=fgetc(fin);
                    if(c>='A'&&c<='Z')
                    //daca gasim un cuvant cu prima litera mare,nu il scriem ci trecem peste el
                    //pana la intalnirea caracterului ' '
                        while(c!=EOF&&c!=' ')
                            c=fgetc(fin);
                    if((c>='a'&&c<='z')||(c==' '&&anterior!=' '))
                    //verificam daca este litera mica sau spatiu
                    {
                        fputc(c,fout);
                        anterior=c;
                    }
                }
                break;
            }
            case 2:
            {
                ///freopen(numeFisier2,"w",fout);
                rewind(fin);
                fprintf(fout,"\n2)Numai numerele.\n");
                char c;
                int x;
                while(c!=EOF)
                {
                    c=fgetc(fin);
                    x=c-'0';//convertim la int caracterul citit
                    if(x>=0&&x<=9)//si verificam daca este cifra
                        fprintf(fout,"%d",x);
                }
                break;
            }
        }
        printf("\nDoriti sa continuati?(Y/N): ");
        scanf("%s",&x);
        }while(x!='N');
    fclose(fout);//inchidem fisierul "date out.txt"
    }
}

int main()
{
    FILE *fin;
    char *numeFisier="date in.txt";
    fin=fopen(numeFisier,"r");
    //verificam daca fisierul "date in.txt" a fost deschis cu succes
    if(fin==NULL)
    {
        printf("Eroare la deschiderea fisierului");
        exit(0);
    }
    else
    {
        printf("Am deschis fisierul %s \n",numeFisier);
        Meniu(fin);
        fclose(fin);// inchidem fisierul "date in.txt"
    }
    return 0;
}
