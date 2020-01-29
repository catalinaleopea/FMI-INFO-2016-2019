#include <iostream>
using namespace std;
class complex
{
    public:
    double re;
    double im;
    void read()
    {
        cout<<"Introduceti partea reala:\n";
        cin>>re;
        cout<<"Introduceti partea imaginara:\n";
        cin>>im;
    }
    void write();
};

void complex::write()
{
    cout<<re<<"+i*"<<im<<endl ;
};

int main()
{
    complex a;
    a.read();
    a.write();
///system("PAUSE");
///return EXIT_SUCCESS;

return 0;}
