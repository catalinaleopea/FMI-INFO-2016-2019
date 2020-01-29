/**1. Pornind de la codul de mai jos, sa se supraincarce functia scade
pentru a fi posibila executia codului din functia main.*/
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
{
return im;
};
};

complex scade(complex a, complex b)
{complex c;
c.SetRe(a.GetRe() - b.GetRe());
c.SetIm(a.GetIm() - b.GetIm());
return c;
};

complex scade(double a, complex b)
{complex c;
c.SetRe(a - b.GetRe());
c.SetIm(b.GetIm());
return c;
};

complex scade(complex a, double b)
{complex c;
c.SetRe(a.GetRe() - b);
c.SetIm(a.GetIm());
return c;
};

int main()
{
complex a, b, c;
a.SetRe(4);
a.SetIm(5);
b.SetRe(2);
b.SetIm(7);
c = scade(a, b);
cout<<c.GetRe()<<"+i*"<<c.GetIm()<<endl;
double d = 4;
c = scade(a, d);
cout<<c.GetRe()<<"+i*"<<c.GetIm()<<endl;
c = scade(-d, a);
cout<<c.GetRe()<<"+i*"<<c.GetIm()<<endl;
///system("PAUSE");
///return EXIT_SUCCESS;

return 0;}
