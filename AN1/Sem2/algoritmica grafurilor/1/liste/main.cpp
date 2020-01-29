#include <iostream>
#include <list>
using namespace std;
///vezi cplusplus.com
int main()
{
    int x;
    list<int>l;
    do
    {
        cin>>x;
        l.push_back(x);
    }while(x);
    for(int p:l)//fiecare intreg p care apartine de l
        cout<<p<<' ';
    ///for(list<int>::interator it=l.begin();it!=l.end;it++)
    ///     cout<<*it<<' ';
    return 0;
}
