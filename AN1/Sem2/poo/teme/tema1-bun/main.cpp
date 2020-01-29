#include <iostream>
#include "cod.h"

using namespace std;

int main()
{
    Polinom ob1(4,5),ob2;
    cin>>ob1;
    cout<<ob1;
    cin>>ob2;
    cout<<ob2;
    ob1.calcul(3);
    ob1.gradul();
    ob1[2];
    Polinom ob3(ob2);
    cout<<ob3;
    Polinom ob4=ob1+ob2;
    cout<<"\nRezultatul adunarii: "<<ob4;
    Polinom ob5=ob1*ob2;
    cout<<"\nRezultatul inmultirii: "<<ob5;
    Polinom ob6=ob1/ob2;
    return 0;

    ///introduceti de la tastatura
    ///ex1: constructor cu param(4,5)
    ///4/ 3 2 2 -3 1 2 0 1 (5x^4+2x^3-3x^2+2x+1)
    ///3/ 2 1 1 3 0 3 (x^2+3x+3)
    ///ex2:constructor cu param(4,1)
    ///4/3 -1 2 2 1 -1 0 3 (x^4-x^3+2x^2-x+3)
    ///2/1 1 0 -1(x-1)
}
