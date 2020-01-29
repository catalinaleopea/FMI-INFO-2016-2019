#include <iostream>
using namespace std;

struct triplet
{
    float x,y,z;
};

void citire(triplet &elem)
{
    cout<<"Dati coordonatele punctului: \n";
    cin>>elem.x>>elem.y>>elem.z;
}

void afisare(triplet elem)
{
    cout<<"Coordonatele sunt: \n";
    cout<<elem.x<<' '<<elem.y<<' '<<elem.z<<'\n';
}

triplet inmultire(float a,triplet n)
{
    triplet temp;
    temp.x=a*n.x;
    temp.y=a*n.y;
    temp.z=a*n.z;
    return temp;
}

triplet adunare(triplet a,triplet b)
{
    triplet temp;
    temp.x=a.x+b.x;
    temp.y=a.y+b.y;
    temp.z=a.z+b.z;
    return temp;
}

int egalitate(triplet a,triplet b)
{
    if(a.x==b.x&&a.y==b.y&&a.z==b.z)
        return 1;
    return 0;
}

void relatie1(triplet a,triplet b,triplet c,float x)
{
    if(egalitate(c,adunare(inmultire((1-x),a),inmultire(x,b))))
        cout<<"Relatia A3="<<1-x<<")*A1+"<<x<<"*A2 este indeplinita \n";
    else cout<<" nu este indeplinita \n";
}

int main()
{
    triplet A1,A2,A3;
    int ok=0;
    citire(A1);
    citire(A2);
    citire(A3);
    afisare(A1);
    afisare(A2);
    afisare(A3);
    if(A1.x!=A2.x||A1.y!=A2.y||A1.z!=A2.z)
        ok=1;
    switch(ok)
    {
    case 1:
        cout<<"\nPrimele doua puncte sunt diferite \n";
        cout<<"Calculam vectorul A1A2 \n";
        triplet A1A2;
        A1A2.x=A2.x-A1.x;
        A1A2.y=A2.y-A1.y;
        A1A2.z=A2.z-A1.z;
        afisare(A1A2);
        float a;
        if(A1A2.x==0)
        {
            if(A1A2.y==0)
                a=(A3.z-A1.z)/(A2.z-A1.z);
            else
                a=(A3.y-A1.y)/(A2.y-A1.y);
        }
        else a=(A3.x-A1.x)/(A2.x-A1.x);
        cout<<"a= "<<a<<'\n';
        cout<<"Calculam vectorul A1A3 \n";
        triplet A1A3;
        A1A3=inmultire(a,A1A2);
        afisare(A1A3);
        if((A1A3.x==(A3.x-A1.x))&&(A1A3.y==(A3.y-A1.y))&&(A1A3.z==(A3.z-A1.z)))
        {
            cout<<"Punctele sunt coliniare ";
            relatie1(A1,A2,A3,a);
        }
        else cout<<"Punctele nu sunt coliniare\n";
        break;
    case 0:
        cout<<"Primele doua puncte sunt identice \n";
        cout<<"Punctele sunt coliniare \nA1=1*A2+0*A3\n";
        break;
    }
    return 0;
}
