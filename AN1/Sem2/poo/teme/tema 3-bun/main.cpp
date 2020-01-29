
#include "cod.h"
#include "functii.cpp"
using namespace std;

int main()
{
    Polinom<double> ob1(4,5),ob2;
    cin>>ob1;
    cout<<ob1;
    cin>>ob2;
    cout<<ob2;
    ob1.calcul(3);
    ob1.gradul();
    ob1[2];
    Polinom<double> ob3(ob2);
    cout<<ob3;
    cout<<"Rezultatul adunarii: "<<ob1+ob2;
    cout<<"Rezultatul inmultirii: "<<ob1*ob2;
    ob1/ob2;
    return 0;

    ///introduceti de la tastatura
    ///ex: constructor cu param(4,5)
    ///4/ 3 2 2 -3 1 2 0 1 (5x^4+2x^3-3x^2+2x+1)
    ///3/ 2 1 1 3 0 3 (x^2+3x+3)
}
