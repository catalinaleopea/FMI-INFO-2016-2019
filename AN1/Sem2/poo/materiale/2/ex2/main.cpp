///ex3
#include <iostream>
using namespace std;

class Complex{
    double re;
    double im;
public:
    void setRe(double x)
        {re=x;}
    void setIm(double y)
        {im=y;}
    double getRe()
        {return re;}
    double getIm()
        {return im;}
};

void read(Complex& a)
{
    double x,y;
    cout<<"Introduceti partea reala:\n";
    cin>>x;
    a.setRe(x);
    cout<<"Introduceti partea imaginara: ";
    cin>>y;
    a.setIm(y);}
    void write(Complex& a)
    {
        cout<<a.getRe()<<"+i*"<<a.getIm()<<endl;
    }

    Complex aduna(Complex a, double b)
    {
        Complex c;
        c.setIm(a.getIm());
        c.setRe(a.getRe()+b);
        return c;
    }

    Complex aduna(double a, Complex b)
    {
        Complex c;
        c.setIm(b.getIm());
        c.setRe(b.getRe()+a);
        return c;
    }

    Complex aduna(Complex a, Complex b)
    {
         Complex c;
         double x,y;
         x=a.getRe()+b.getRe();
         y=a.getIm()+b.getIm();
         c.setIm(y);
         c.setRe(x);
    return c;
    }

int main()
{
    Complex a,b,d,c;
    double x=3.5;
    read(a);
/// cout<<a.re<<endl; //--- atributul re nu mai este public
    write(a);
    cout<<"Rezultatele adunarii:"<<endl;
    c=aduna(a,x);
    write(c);
    c=aduna(x,a);
    write(c);
    read(b);
    d=aduna(a,b);
    write(d);
    return 0;
}
