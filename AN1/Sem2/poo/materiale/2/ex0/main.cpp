#include <iostream>
#include <string>
using namespace std;

class MyClass
{
public:
    string MyString;
};

int main()
{
    MyClass MyObject;
    MyObject.MyString="Hello World!";
    cout<<MyObject.MyString<<'\n';
//    system("PAUSE");
//    return EXIT_SUCCES;
return 0;
}
