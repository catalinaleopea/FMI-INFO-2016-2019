#include <iostream>
using namespace std;

//pentru puncte
struct pereche
{
    float x,y;
    char nume[2];
} puncte[4];

//pentru a,b si c din ecuatia dreptei
struct triplet
{
    float a,b,c;
};

pereche citire()
{
    cout<<"Dati coordonatele punctului ";
    pereche temp;
    cin>>temp.x>>temp.y;
    temp.nume[0]='A';
    return temp;
}

void afisare(pereche nr)
{
    cout<<nr.nume<<" ("<<nr.x<<','<<nr.y<<")\n";
}

triplet ecuatia_dreptei(pereche p1,pereche p2)
{
    float a=p1.y-p2.y;
    float b=p2.x-p1.x;
    float c=p1.x*p2.y-p2.x*p1.y;
    cout<<a<<"*x"<<'+'<<b<<"*y"<<"+"<<c<<endl;
    triplet temp;
    temp.a=a;
    temp.b=b;
    temp.c=c;
    return temp;
}

float det(triplet m,triplet n)
{
    return m.a*n.b-m.b*n.a;
}

int rang_a_bar(triplet m,triplet n)
{
    if((m.a*n.b-m.b*n.a)!=0||(m.a*n.c-n.a*m.c)!=0||(m.b*n.c-m.c*n.b)!=0)
        return 2;
    if((m.a||m.b||m.c||n.a||n.b||n.c)!=0)
        return 1;
}

void sortare()
{
//sortez dupa y
    for(int i=0; i<4; i++)
        for(int j=i; j<4; j++)
            if((puncte[i].y>puncte[j].y))
                swap(puncte[i],puncte[j]);
//sortez dupa x
    for(int i=0; i<4; i++)
        for(int j=i; j<4; j++)
            if((puncte[i].x>puncte[j].x))
                swap(puncte[i],puncte[j]);
}

void intersectie(triplet m,triplet n)
{
    int rez=det(m,n);
    switch(rez)
    {
    case 0:
    {
        int rang=rang_a_bar(m,n);
        switch(rang)
        {
        case 1:
        {
            cout<<"Punctele sunt coliniare\n";
            sortare();
            int s1=(puncte[0].nume[1]-'0')+(puncte[1].nume[1]-'0');
            int s2=(puncte[2].nume[1]-'0')+(puncte[3].nume[1]-'0');
            //primul segment se termina inainte de inceperea celuilalt
            if((s1==3&&s2==7)||(s1==7&&s2==3))
                cout<<"Intersectia segmentelor este multimea vida\n";
            else
            {
                if((puncte[1].x<puncte[2].x)||(puncte[1].y<puncte[2].y)){
                    cout<<"Segmentele se intersecteaza\n";
                    cout<<"intersectia este ["<<puncte[1].nume<<puncte[2].nume<<"]\n";
                }
                else
                    cout<<"Intersectia segmentelor este multimea vida\n";
            }
            break;
        }
        case 2:
        {
            cout<<"Intersectia dreptelor este multimea vida\n";
            cout<<"Intersectia segmentelor este multimea vida\n";
            break;
        }
        }
        break;
    }
    default:
    {
        int x=((-1)*m.c*n.b+m.b*n.c)/rez;
        int y=((-1)*m.a*n.c+m.c*n.a)/rez;
        ///verific daca x apartine segmentelor
        cout<<x<<' '<<y<<'\n';
        if(
           ((x>=puncte[0].x&&x<=puncte[1].x)||(x<=puncte[0].x&&x>=puncte[1].x))
           &&
           ((x>=puncte[2].x&&x<=puncte[3].x)||(x<=puncte[2].x&&x>=puncte[3].x))
           )
            cout<<"Segmentele se intersecteaza in punctul ("<<x<<','<<y<<")\n";
        else
            cout<<"Intersectia segmentelor este multimea vida\n";
        break;
    }
    }
}

int main()
{
    for(int i=0; i<4; i++)
    {
        puncte[i]=citire();
        puncte[i].nume[1]=(i+1)+'0';
    }

    intersectie(ecuatia_dreptei(puncte[0],puncte[1]),ecuatia_dreptei(puncte[2],puncte[3]));

    return 0;
}
