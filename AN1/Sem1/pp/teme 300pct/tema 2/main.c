/**Simuleaza o baza de date care sa respecte urmatoarele conditii:
sa contina minim 5 structuri de date;                                                 5x3=15p
sa contina minim o uniune si/sau un camp de structuri pe biti si/sau o enumerare;     5p
valoarea unuia dintre campurile unei structuri sa fie calculata in functie de informatiile
existente intr-o alta structura;                                                      5p
utilizarea a cel putin 5 proceduri ce prelucreaza datele din structuri;               5x3=15p
sa se utilizeze un vector de pointeri la cele 5 proceduri/functii;                    5p
sa se foloseasca qsort din stdlib pentru a ordona un vector de structuri dupa cel putin
un camp ce contine siruri de caractere;                                               5p
tratare eventuale erori de input/cazuri speciale ce pot aparea in cadrul programului  5p

Coerenta in implementare (toate cerintele se imbina in mod logic):                    15p
Formulare cerinta:                                                                    5p
Coding style:                                                                         20p
Originalitate:                                                                        5p

LEOPEA CATALINA
Informatii despre actori,regizori,platou,durata de filmare,rularea in cinematograf
**/
#include <stdio.h>
#include <stdlib.h>

struct actor
{
    char nume[15],prenume[10],rol[30];
    int varsta,credite;
};

struct regizor
{
    char nume[10],prenume[10];
    int varsta;
};

struct platou
{
    char tara[10],oras[10],nume[30];
    int zile;
};

struct durata_film
{
    int zile;
};

struct rularea_in_cinema
{
    char data[11],tara[10];
    union
    {
        char a[5];
    }tip;
};

//SALVEAZA INFORMATIILE DESPRE ACTORI
void getInfo(struct actor a[], int nrActori,FILE *f)
{
    int i;
    for (i=0;i<nrActori;++i)
    {
        fscanf(f,"%s%s%s%d%d",a[i].nume,a[i].prenume,a[i].rol,&a[i].varsta,&a[i].credite);
    }
}

//INFORMATIILE DESPRE REGIZORI
void getInfor(struct regizor b[], int nrRegizori,FILE *f)
{
    int i;
    for (i=0;i<nrRegizori;++i)
    {
        fscanf(f,"%s%s%d",b[i].nume,b[i].prenume,&b[i].varsta);
    }
}

//INFORMATIILE DESPRE PLATOURI
void getInfop(struct platou c[],int nrPlatouri,FILE *f)
{
    int i;
    for(i=0;i<nrPlatouri;++i)
    {
        fscanf(f,"%s%s%s%d",c[i].tara,c[i].oras,c[i].nume,&c[i].zile);
    }
}

//INFORMATIILE DESPRE DIFUZARI
void getInfod(struct rularea_in_cinema d[],int nrDifuzari,FILE *f)
{
    int i;
    for(i=0;i<nrDifuzari;++i)
    {
        fscanf(f,"%s%s%s",d[i].tara,d[i].data,d[i].tip.a);
    }

}

//AFISEAZA ACTORII
void printInfo(struct actor a[],int nrActori)
{
    int i;
    for (i=0;i<nrActori;++i)
        {
            printf("Nume %s\nPrenume %s\nRol %s\nVarsta %d\nCredite %d\n",
                   a[i].nume,a[i].prenume,a[i].rol,a[i].varsta,a[i].credite);
            printf("\n");
        }
}

//AFISEAZA REGIZORII
void printInfor(struct regizor b[],int nrRegizori)
{
    int i;
    for (i=0;i<nrRegizori;++i)
        {
            printf("Nume %s\nPrenume %s\nVarsta %d\n",b[i].nume,
                   b[i].prenume,b[i].varsta);
            printf("\n");
        }
}

//AFISEAZA PLATOURILE
void printInfop(struct platou c[],int nrPlatouri)
{
    int i;
    for(i=0;i<nrPlatouri;++i)
    {
        printf("Tara %s\nOrasul %s\nNumele %s\nZile de filmare%d\n",
               c[i].tara,c[i].oras,c[i].nume,c[i].zile);
        printf("\n");
    }
}

//AFISEAZA DIFUZARILE
void printInfod(struct rularea_in_cinema d[],int nrDifuzari)
{
    int i;
    for(i=0;i<nrDifuzari;++i)
    {
        printf("Tara %s\nData %s\nTip film %s\n",d[i].tara,
               d[i].data,d[i].tip.a);
        printf("\n");
    }
}

///sortare dupa credite descendent
void compara(struct actor a[], int length)
{
    int i,j;
    struct actor aux;
    for (i=0;i<length-1;i++)
        for(j=i+1;j<length;j++)
            if ((a[i].credite)<(a[j].credite))
    {
        aux=a[j];
        a[j]=a[i];
        a[i]=aux;
    }
}

int comp(struct actor *a1, struct actor *a2)
{
    return strcmp((*a1).nume,(*a2).nume);
}

///qsort actori dupa nume ascendent
void sortare(struct actor a[], int length)
{
    qsort(a,length,sizeof(struct actor),comp);
}

///media creditelor actorilor
void mediaCredite(struct actor a[],int length)
{
    int i,s=0;
    for (i=0;i<length;++i)
    {
        s=s+a[i].credite;
    }
    printf("media creditelor actorilor este: %d", s/length);
}

///afisarea datei calendaristice de rulare a filmului,
///in functie de tara citita de la tastatura
void cautaTara(char a[20],struct rularea_in_cinema d[],int nrDifuzari)
{
    int i,x,ok=0;
    for(i=0;i<nrDifuzari;++i)
        if(strcmp(a,d[i].tara)==0)
            {
                ok=1;
                x=i;
            }
    if(ok)
        printf("S-a gasit tara, data premierei este %s ",d[x].data);
    else
        printf("Nu s-a gasit");
}

void Meniu(struct actor a[], int length,struct platou c[],int nrPlatouri,
           struct rularea_in_cinema d[],int nrDifuzari)
{
    char x='Y';
    do
    {
        int selectie;
        do
        {
            printf("Alegeti functia dorita:\n");
            printf("1)Afisarea actorilor alfabetic dupa nume\n");
            printf("2)Afisarea actorilor dupa credite descrescator\n");
            printf("3)Aflarea datei premierei filmului pentru o tara\n");
            printf("4)Afisarea mediei creditelor actorilor\n");
            printf("5)Afisarea duratei totale a filmului\n");
            scanf("%d",&selectie);
        }while (selectie!=1&&selectie!=2&&selectie!=3&&selectie!=4&&selectie!=5);
        switch (selectie)
        {
            case 1:
            {
                sortare(a,length);
                printInfo(a,length);
                break;
            }

            case 2:
            {
                compara(a,length);
                printInfo(a,length);
                break;
            }

            case 3:
            {   char a[20];
                printf("Scrieti tara dorita\n");
                scanf("%s",a);
                cautaTara(a,d,nrDifuzari);
                break;
            }

            case 4:
            {
                mediaCredite(a,length);
                break;
            }
            case 5:
            {
                struct durata_film x[1];
                int i,total=0;
                for(i=0;i<nrPlatouri;++i)
                    total=total+c[i].zile;
                x[1].zile=total;
                printf("%d zile\n\n",x[1].zile);
                break;
            }
        }
        printf("\nDoriti sa continuati?(Y/N): ");
        scanf("%s",&x);
        }while(x=='Y');
}

int main()
{
    FILE *f;
    char *numeFisier="f.txt";
    f=fopen(numeFisier,"r");
    if(f==NULL)
    {
        printf("Eroare la deschiderea fisierului");
        exit(0);
    }
    else
    {
        printf("Am deschis fisierul %s \n",numeFisier);
///INCARCAREA DIN FISIER
    int nrActori=fgetc(f)-'0';
    struct actor a[nrActori];
    getInfo(a,nrActori,f);
//  printInfo(a,nrActori);
    int nrRegizori;
    fscanf(f,"%d",&nrRegizori);
    struct regizor b[nrRegizori];
    getInfor(b,nrRegizori,f);
//  printInfor(b,nrRegizori);
    int nrPlatouri;
    fscanf(f,"%d",&nrPlatouri);
    struct platou c[nrPlatouri];
    getInfop(c,nrPlatouri,f);
//  printInfop(c,nrPlatouri);
    int nrDifuzari;
    fscanf(f,"%d",&nrDifuzari);
    struct rularea_in_cinema d[nrDifuzari];
    getInfod(d,nrDifuzari,f);
//  printInfod(d,nrDifuzari);

    Meniu(a,nrActori,c,nrPlatouri,d,nrDifuzari);
    fclose(f);
    }
    return 0;
}
