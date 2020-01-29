#include <stdio.h>
#include <stdlib.h>
#define MAX 1001
int a[MAX][MAX],b[MAX][MAX]; //a matricea initiala,b copia sa dupa evolutie
                            //i,j,p contori
                            //n nr de linii,m nr de coloane,k nr de evolutii

void citire(int n,int m,int nr){//citirea configuratiei initiale de la care porneste evolutia
    int i,j;
    for(i=1;i<=n;i++)
        for(j=1;j<=m;j++)
            {scanf("%d",&a[i][j]);
            if(a[i][j])nr++;
        }
}

int vecini(int i,int j){
    return a[i-1][j-1]+a[i-1][j]+a[i-1][j+1]+a[i][j-1]+ //functia returneaza suma vecinilor unei celule
    a[i][j+1]+a[i+1][j-1]+a[i+1][j]+a[i+1][j+1];        //adaugand 1 cand exista un vecin si 0 in caz contrar
}

int veciniToroid(int i,int j){//cautam vecinii celulei parcurgand matricea circular
    /*cand un contor depaseste marginile matricei
    contorul=dimensiune max-contor+1*/
    int n,m;
    if(i==1&&j==1) // celula din coltul din stanga sus
        return a[1][2]+a[2][1]+a[2][2]+a[n][1]+
        a[n][2]+a[1][m]+a[2][m]+a[n][m];
    if(i==1&&j==m) // celula din coltul din dreapta sus
       return a[1][m-1]+a[2][m-1]+a[2][m]+a[n][m-1]+
       a[n][m]+a[1][1]+a[2][1]+a[n][1];
    if(i==n&&j==1) //celula din coltul din stanga jos
        return a[n-1][m]+a[n-1][1]+a[n-1][2]+a[n][m]+
        a[n][2]+a[1][m]+a[1][1]+a[1][2];
    if(i==n&&j==m) //celula din coltul din dreapta jos
        return a[n-1][m-1]+a[n-1][m]+a[n-1][1]+a[n][m-1]+
        a[n][1]+a[1][1]+a[1][m-1]+a[1][m];
    if(i==1&&j!=1&&j!=m) // pe prima linie
        return a[n][j-1]+a[n][j]+a[n][j+1]+a[1][j-1]+
        a[1][j+1]+a[2][j-1]+a[2][j]+a[2][j+1];
    if(i==n&&j!=1&&j!=m) // pe ultima linie
        return a[1][j-1]+a[1][j]+a[1][j+1]+a[n-1][j-1]+
        a[n-1][j]+a[n-1][j+1]+a[n][j-1]+a[n][j+1];
    if(j==1&&i!=1&&i!=n) //pe prima coloana
        return a[i-1][m]+a[i][m]+a[i+1][m]+a[i-1][1]+
        a[i+1][1]+a[i-1][2]+a[i][2]+a[i+1][2];
    if(j==m&&i!=1&&i!=n) // pe ultima coloana
        return a[i-1][1]+a[i][1]+a[i+1][1]+a[i-1][m-1]+
        a[i-1][m]+a[i][m-1]+a[i+1][m-1]+a[i+1][m];
    if(i!=1&&j!=1&&i!=n&&j!=m)//in interior
        vecini(i,j);
}

void copiere(int n,int m,int nr){//folosim o copie a matricei pentru a putea
    int i,j;              //pastra evolutia de la pasul anterior
    for(i=1;i<=n;i++)
        for(j=1;j<=m;j++){
            a[i][j]=b[i][j];
            if(a[i][j])nr++;
        }
}

void afisare(int n,int m){//afisarea evolutiei
    int i,j;
    for(i=1;i<=n;i++){
        printf("\n");
        for(j=1;j<=m;j++){
            printf("%d ",a[i][j]);
        }
    }

}

void joacaJoculPlan(int n,int m,int k,int nr){
    int i,j,p;
    for(p=1;p<=k;p++){
        for(i=1;i<=n;i++)
            for(j=1;j<=m;j++)
                if(a[i][j]){//daca exista vecini
                    if(vecini(i,j)<2)//celula cu mai putin de două
                        b[i][j]=0; //celule vecine moare de singurătate
                    else
                        if(vecini(i,j)<=3)//celula cu două sau trei
                            b[i][j]=1; //celule vecine supravietuieste
                        else b[i][j]=0;//celula cu mai mult de trei celule
                }                    // vecine moare din cauza supraaglomerării
                else  //daca nu exista vecini
                    if(vecini(i,j)==3)//o celulă nouă este creată
                        b[i][j]=1;  //dacă are exact trei celule vecine
                    else b[i][j]=0;//altfel completam cu 0 matricea copie
    copiere(n,m,nr);
    }
}

void joacaJoculToroid(int n,int m,int k,int nr){
    int p,i,j;
    for(p=1;p<=k;p++){
        for(i=1;i<=n;i++)
            for(j=1;j<=m;j++)
                if(a[i][j]){
                    if(veciniToroid(i,j)<2)
                        b[i][j]=0;
                    else
                        if(veciniToroid(i,j)<=3)
                            b[i][j]=1;
                        else b[i][j]=0;
                }
                else
                    if(veciniToroid(i,j)==3)
                        b[i][j]=1;
                    else b[i][j]=0;
        copiere(n,m,nr);
    }
}

int main(){
    int n,m,k,nr;
    float nr2=0;
    char tip;
    scanf("%c%d%d%d",&tip,&n,&m,&k);
    switch(tip){
        case 'P'://plan
            citire(n,m,nr);
            joacaJoculPlan(n,m,k,nr);
            afisare(n,m);
            nr2=(nr*100)/(n*m);
            printf("\n%.3f%%",nr2);//pentru a scrie '%' folosim "%%" sau printf("%c", '%');
            break;

        case 'T': //toroid
            if(n<3||m<3)//o matrice cu <3 linii sau coloane
                    //nu poate fi reprezentata toroidal
                printf("\nnu poate fi reprezentat toroidal");
            else {
                citire(n,m,nr);
                joacaJoculToroid(n,m,k,nr);
                afisare(n,m);
                nr2=(nr*100)/(n*m);
                printf("\n%.3f%%",nr2);//pentru a scrie '%' folosim "%%" sau printf("%c", '%');
            }
            break;
        default:
            printf("\ntipul introdus este gresit");
    }
    return 0;
}
