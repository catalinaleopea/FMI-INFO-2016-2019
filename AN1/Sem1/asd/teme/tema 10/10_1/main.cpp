/**1. Fiind dat� matricea de adiacen�� a unui graf neorientat cu n v�rfuri, scrie�i func�iile urm�toare:
- grad(x) care calculeaz� gradul v�rfului x al grafului;
- NumarMuchii() care calculeaz� num�rul de muchii din graf;
- GradMax() care afi�eaz� v�rfurile de grad maxim.
Num�rul de v�rfuri �i matricea de adiacen�� se vor citi dintr-un fi�ier.**/
#include <iostream>
#include <fstream>
#include <string.h>
using namespace std;
ifstream f("fisier.txt");

int grad(int);
int nrMuchii();
void gradMax();

int main()
{
    cout<<grad(4);
    cout<<endl;
    cout<<nrMuchii();
    cout<<endl;
    gradMax();
    f.close();
    return 0;
}

int grad(int x)
{
    f.clear();
    f.seekg(0, ios::beg);
    int n;
    f>>n;
    if(x<0||x>n)
    {
        cout<<"Date incorecte";
        return -1;
    }
    else
    {
        int y;
        int grad=0;
        for(int i=1;i<=x;i++)
            for(int j=1;j<=n;j++)
            {
                f>>y;
                if(i==x&&y==1)
                    grad++;
            }
    return grad;
    }
}

int nrMuchii()
{
    f.clear();
    f.seekg(0, ios::beg);
    int n;
    f>>n;
    int y;
    int nr=0;
    for(int i=1;i<=n;i++)
        for(int j=1;j<=n;j++)
        {
            f>>y;
            if(y==1)
                nr++;
        }
    return nr/2;
}

void gradMax()
{
    f.clear();
    f.seekg(0, ios::beg);
    int n;
    f>>n;
    int max=0;
    int y;
    for(int i=1;i<=n;i++)
    {
        int nr=0;
        for(int j=1;j<=n;j++)
        {
            f>>y;
            if(y)
                nr++;
        }
        if(nr>max)
            max=nr;
    }
    for(int i=1;i<=n;i++)
        if(grad(i)==max)
            cout<<i<<' ';
}
