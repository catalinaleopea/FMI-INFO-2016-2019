/**2. Pornind de la codul de mai jos, scrieti o definitie pentru a supraincarca
operatorul = astfel incat sa fie posibila executia codului din functia main.*/
#include <string>
#include <iostream>
#include <math.h>
using namespace std;
class complex
{
double re;
double im;
public :
void SetRe(double value)
{
re = value;
};
void SetIm(double value)
{
im = value;
};
double GetRe()
{
return re;
};
double GetIm()
{return im;
};
complex operator=(double a);
};
complex complex::operator=(double a)
{
   this->SetRe(a);
    this->SetIm(0);
    return *this;
}

//complex complex::operator =(complex a)
//{
//    complex c;
//    c.re=a.GetRe();
//    c.im=a.GetIm();
//    return c;
//}


int main()
{
complex a;
double b = 20;
a = b;
cout<<a.GetRe()<<"+i*"<<a.GetIm()<<endl;
//system("PAUSE");
return 0;//EXIT_SUCCESS;
}
