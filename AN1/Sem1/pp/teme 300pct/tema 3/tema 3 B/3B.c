/**B. Scrieți un program C ce conține 4 operații asupra continutului unui fisier fara a memora
intregul sir de caractere si fara a folosi fisiere suplimentare.
Listă orientativă: 60p.
- modificarea unor cuvinte din fisier dupa o anumita regula;
- modificarea unui camp din inregistrarile unei structuri deserializate;
- determinarea numarului de aparitii pentru un cuvant;
- determinarea cuvintelor ce nu contin consoane;
- determinarea sumei numerelor din fisier;
- interschimbarea unor cuvinte de lungimi egale;
- dublarea unor anumite cuvinte/caractere;
**/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

///Modificarea vocalelor din litere mici in litere mari si invers
void resetareVocale(FILE *fin,int sf)
{
    fseek(fin,0,SEEK_SET);//seteaza cursorul la inceputul textului initial
    char c;
    char VOC[6]="AEIOU";
    char voc[6]="aeiou";
    while(ftell(fin)<sf)//verifica pozitia cursorului
    {                   //cat timp nu este finalul textului initial
        c=fgetc(fin);
        if(strchr(voc,c))//verifica daca este vocala mica
        {
            c=c-32;
            fseek(fin, -1, SEEK_CUR);//mutam cursorul inapoi cu un caracter
            fputc(c,fin);           //suprascriem caracterul de modificat
            fseek(fin, 0, SEEK_CUR);//setam cursorul la pozitia curenta
        }
        else
            if(strchr(VOC,c))//sau mare
            {
                c=c+32;     //si o modifica
                fseek(fin, -1, SEEK_CUR);
                fputc(c,fin);
                fseek(fin, 0, SEEK_CUR);
            }
    }
}

///Determinarea numarului de cifre
void nrCifre(FILE *fin,int sf)
{
    fseek(fin,0,SEEK_SET);
    char c;
    int x,nr=0;
    while(ftell(fin)<sf)
    {
        c=fgetc(fin);
        x=c-'0';//convertim la int caracterul citit
        if(x>=0&&x<=9)//si verificam daca este cifra
        nr++;
    }
    freopen("date in.txt","w",fin);
    //inchide daca a fost deschis anterior si deschide gol fisierul pentru output
    //fseek(fin,sf,SEEK_END);
    fprintf(fin," %d",nr);

}

///Modificarea simbolurilor cu '*'
void modificare(FILE *fin,int sf)
{
    fseek(fin,0,SEEK_SET);
    char c;
    char simbol[30]="\n-+='[ ](){}:;,.<>?/&@*^#";
    while(ftell(fin)<sf)
    {
        c=fgetc(fin);
        if(strchr(simbol,c))//verificam daca este simbol
            c='*';          //si modificam
        fseek(fin, -1, SEEK_CUR);//mutam cursorul inapoi cu un caracter
        fputc(c,fin);           //suprascriem caracaterul de modificat
        fseek(fin, 0, SEEK_CUR);//setam cursorul la pozitia curenta
    }
}

///Interschimbarea cuvantului <fisiere> cu <operare>
void interschimbare(FILE *fin,int sf,char cuv1[],char cuv2[])
{
    fseek(fin,0,SEEK_SET);
    char cuvant[30];
    int ok=0;
    while(ftell(fin)<sf&&ok==0)
    {
        fscanf(fin, "%s", cuvant);
        int lg=strlen(cuvant);
        while(!isalpha(cuvant[lg]))//verificam sa nu existe caractere nealfabetice la sfarsitul cuvantului
        {
            cuvant[lg]=NULL;
            lg--;
        }
        if(strcmp(cuvant,cuv1)==0)//cautam de la inceputul fisierului,prima aparitie a cuv1
        {                         //cand il gasim memoram pozitia din fisier si cautam cuv2
            int x=ftell(fin);
            while(ftell(fin)<sf&&ok==0)
            {
                fscanf(fin, "%s", cuvant);
                int lg2=strlen(cuvant);
                while(!isalpha(cuvant[lg2]))
                {
                    cuvant[lg2]=NULL;
                    lg2--;
                }
                if(strcmp(cuvant,cuv2)==0)//am gasit cuv2
                {
                    ok=1;
                    int y=ftell(fin);//memoram pozitia cuv2 din fisier
                    fseek(fin,x,SEEK_SET);//ne intoarcem in fisier la pozitia cuv1 si punem cuv2 in loc
                    fseek(fin, -lg-1, SEEK_CUR);
                    fputs(cuv2, fin);

                    fseek(fin,y,SEEK_SET);//la fel si pentru celalalt
                    fseek(fin, -lg2-1, SEEK_CUR);
                    fputs(cuv1, fin);
                    fseek(fin, 0, SEEK_CUR);
                }
            }
        }
    }
}

void Meniu(FILE *fin)
{
    fseek(fin,0,SEEK_END);  //muta cursorul la sfarsitul textului initial
    int sf=ftell(fin);      //si memoreaza a cata pozitie este fata de inceput
    fseek(fin,0,SEEK_SET);  //seteaza cursorul la inceputul fisierului
    char x='Y';
    do
    {
        int selectie;
        do
        {
             printf("Alegeti functia dorita:\n");
             printf("1)Resetarea vocalelor\n");
             printf("2)Determinarea numarului de cifre\n");
             printf("3)Modificarea simbolurilor cu '*'\n");
             printf("4)Interschimbarea cuvantului <fisiere> cu <operare> \n");
             scanf("%d",&selectie);
        }while(selectie<1&&selectie>4);
        switch(selectie)
        {
            case 1:
            {
                resetareVocale(fin,sf);
                break;
            }
            case 2:
            {
                nrCifre(fin,sf);
                break;
            }
            case 3:
            {
                modificare(fin,sf);
                break;
            }
            case 4:
            {
                char cuv1[]="fisiere";
                char cuv2[]="operare";
                interschimbare(fin,sf,cuv1,cuv2);
                break;
            }
        }
        printf("\nDoriti sa continuati?(Y/N): ");
        scanf("%s",&x);
    }while(x=='Y');
}

int main()
{
    FILE *fin;
    char *numeFisier="date in.txt";
    fin=fopen(numeFisier,"r+");
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
