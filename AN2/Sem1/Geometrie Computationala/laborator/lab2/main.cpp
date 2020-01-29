#include <iostream>
using namespace std;

struct pereche
{
    float x,y;
} puncte[4];

pereche citire()
{
    cout<<"Dati coordonatele punctului ";
    pereche temp;
    cin>>temp.x>>temp.y;
    return temp;
}

void afisare(pereche nr)
{
    cout<<'('<<nr.x<<','<<nr.y<<")\n";
}

float testOrientare(pereche a,pereche b,pereche c)
{
    return a.x*b.y+b.x*c.y+c.x*a.y-c.x*b.y-a.x*c.y-b.x*a.y;
}

int main()
{
    //citim coordonatele punctelor
    for(int i=0; i<4; i++)
        puncte[i]=citire();

    //cautam punctul din stanga jos
    for(int i=0; i<4; i++)
        if(puncte[0].x>puncte[i].x||(puncte[0].y>puncte[i].y&&puncte[0].x>puncte[i].x))
            swap(puncte[0],puncte[i]);

    //sortam dupa testul de orientare
    if(testOrientare(puncte[0],puncte[1],puncte[2]) < 0 ||(testOrientare(puncte[0],puncte[1],puncte[2])==0 && puncte[1].x > puncte[2].x))
        swap(puncte[1],puncte[2]);
    if(testOrientare(puncte[0],puncte[2],puncte[3]) < 0 ||(testOrientare(puncte[0],puncte[2],puncte[3])==0 && puncte[2].x > puncte[3].x))
        swap(puncte[2],puncte[3]);
    if(testOrientare(puncte[0],puncte[1],puncte[2]) < 0 ||(testOrientare(puncte[0],puncte[1],puncte[2])==0 && puncte[1].x > puncte[2].x))
        swap(puncte[1],puncte[2]);

    //afisam punctele
    for(int i=0; i<4; i++)
        afisare(puncte[i]);

    //aflam nr de varfuri care formeaza acoperirea
    pereche acoperire[3];
    int varfuri=0;
    acoperire[0]=puncte[0];
    acoperire[++varfuri]=puncte[1];
    for(int i=2; i<4; i++)
    {
        while(varfuri>0 && testOrientare(acoperire[varfuri-1],acoperire[varfuri],puncte[i]) <= 0)
            varfuri--;
        acoperire[++varfuri]=puncte[i];
    }

    cout<<"acoperirea convexa:\n";
    for(int i=0; i<=varfuri; i++)
        afisare(acoperire[i]);

    switch(varfuri)
    {
    case 3:
    {
        cout<<"patrulater\nI:";
        afisare(puncte[0]);
        afisare(puncte[2]);
        cout<<"J:";
        afisare(puncte[1]);
        afisare(puncte[3]);
        break;
    }
    case 2:
    {
        cout<<"triunghi\nI:";
        afisare(puncte[0]);
        afisare(puncte[1]);
        afisare(puncte[2]);
        cout<<"J:";
        for(int i=0; i<4; i++)
        {
            int ok=1;
            for(int j=0; j<=varfuri; j++)
                if(acoperire[j].x == puncte[i].x && acoperire[j].y == puncte[i].y)
                    ok=0;
            if(ok)
               afisare(puncte[i]);
        }
        break;
    }
    case 1:
    {
        cout<<"dreapta\nI:";
        afisare(puncte[0]);
        afisare(puncte[1]);
        cout<<"J:";
        for(int i=0; i<4; i++)
        {
            int ok=1;
            for(int j=0; j<=varfuri; j++)
                if(acoperire[j].x == puncte[i].x && acoperire[j].y == puncte[i].y)
                    ok=0;
            if(ok)
                afisare(puncte[i]);
        }
        break;
    }
    }
    return 0;
}
