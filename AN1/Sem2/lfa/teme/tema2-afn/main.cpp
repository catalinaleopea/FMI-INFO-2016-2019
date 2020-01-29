#include <iostream>
#include <fstream>
using namespace std;
ifstream fin("date.in");

struct afd{
    int nod,lega,legb;
    afd *next;
}*primul;

int inserare(int a,int **afn,int stariF,int *finale)
{
    if(a<1)
        return -1;
    afd *temp=new afd;
    temp->nod=a;
     temp->next=NULL;
    if(a<10)//linia din matricea afn
    {
        temp->lega=afn[a][1];
        temp->legb=afn[a][2];
    }
    else //reuniune
    {
//        temp->lega=afn[a%10][1];
//        temp->legb=afn[a%10][2];
//        int x=a/10;
        while(a)
        {
            if(!temp->lega&&!temp->legb)
            {

            temp->lega=afn[a%10][1];
            temp->legb=afn[a%10][2];
a=a/10;}
          else{  int x=a/10;
          int y,w,ok1=1,ok2=1;
            y=temp->lega;w=temp->legb;
            while(y&&ok1)
            {
                if(x%10==y%10)
                    ok1=0;
                y=y/10;
            }
            while(w&&ok2)
            {
                if(x%10==w%10)
                    ok2=0;
                w=w/10;
            }

            if(ok1)temp->lega=temp->lega*10+afn[x%10][1];
            if(ok2)temp->legb=temp->legb*10+afn[x%10][2];
            a=a/10;
        }}
    }
    if(primul==NULL)
    {
        primul=temp;
        return -1;
    }
    //adaug la final
    afd *p=primul;
    afd *anterior;
    while(p)
    {
        if(p->nod==a)
            return -1;
        anterior=p;
        p=p->next;
    }
    anterior->next=temp;
    //parcurg lista si returnez doar starile finale
    int ok=1;
    for(int i=0;i<stariF&&ok;i++)
    {
        int y=a;
        while(y&&ok)
        {
            if(y%10==finale[i])
                ok=0;
            y=y/10;
        }
    }
    if(ok==0)
        return a;
    else return -1;
}

void afisare()
{
    cout<<"\nAFD\n";
    afd *p=primul;
    while(p)
    {
        if(p->lega)
            cout<<p->nod<<' '<<p->lega<<" a\n";
        if(p->legb)
            cout<<p->nod<<' '<<p->legb<<" b\n";
        p=p->next;
    }
}
void matriceAfn(int **afn,int tranzitii)
{
    ///completez matricea
    for(int i=0;i<tranzitii;i++)
    {
        int x,y,z; char w;
        fin>>x>>y>>w;
        if(w=='a') z=1;
        else z=2;
        if(!afn[x][z])//daca nu exista legatura deja
            afn[x][z]=y;
        else
            afn[x][z]=afn[x][z]*10+y;
    }//daca exista creeaza un nr cu cifrele egale cu nr starilor cu care are legaturi
}

void afisareAfn(int **afn,int stari)
{
    cout<<"Matricea AFN\n";
    for(int i=1;i<=stari;i++)
    {
        for(int j=1;j<=2;j++)
            cout<<afn[i][j]<< ' ';
        cout<<endl;
    }
}

int main()
{
    int stari,tranzitii,stareI,stariF;
    fin>>stari>>tranzitii>>stareI>>stariF;
    int finale[stariF];
///alocare dinamica matrice afn
    int** afn=new int*[stari];
    for(int i=1;i<=stari;i++)
        afn[i]=new int[2];
///initializare cu 0 matrice afn
    for(int i=1;i<=stari;i++)
        for(int j=1;j<=2;j++)
            afn[i][j]=0;
//citeste starile finale
    for(int i=0;i<stariF;i++)
        fin>>finale[i];

    matriceAfn(afn,tranzitii);
    afisareAfn(afn,stari);

///lista afd cu elemente (stare,legaturi cu a,legaturi cu b)
    int finiteAFD[stari]; int k=-1;
    if(inserare(1,afn,stariF,finale)!=-1)finiteAFD[++k]=1;
    afd *p=primul;
    while(p)
    {
        if(inserare(p->lega,afn,stariF,finale)!=-1)finiteAFD[++k]=p->lega;
        if(inserare(p->legb,afn,stariF,finale)!=-1)finiteAFD[++k]=p->legb;
        p=p->next;
    }
    afisare();
    cout<<"\nStarile finite din AFD sunt ";
    for(int i=0;i<=k;i++)
        cout<<finiteAFD[i]<<' ';
   ///dezalocare afn
    for(int i=1;i<=stari;i++)
        delete [] afn[i];
    delete [] afn;
    ///dezalocare afd
    p=primul;
    while(p!=NULL)
    {
        p=p->next;
        delete primul;
        primul=p;
    }
    delete primul;

    return 0;
}
