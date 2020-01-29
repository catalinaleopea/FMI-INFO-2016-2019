#include <iostream>

using namespace std;

class A
{
    protected:int x;
    public:
        A(int i=14)
        {
            x=i;
        }
};
class B:A
{
public:
    B(B&b)
    {
        x=b.x;
    }
    void afisare()
    {
        cout<<x;
    }
    B(){}
};
int main()
{
    B b1;
    B b2(b1);
    b2.afisare();
    return 0;
}
