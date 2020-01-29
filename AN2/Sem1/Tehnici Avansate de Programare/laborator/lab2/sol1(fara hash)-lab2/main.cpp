#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
using namespace std;

ifstream f("date.in");
int n, a, b, c;
vector<int> v;

int main()
{
    f >> n;
    for(int i =  0; i < n; i++){
            f >> a;
            v.push_back(a);
    }
    v.resize(n);
    sort(v.begin(),v.end());///crescator
    for(vector<int>::iterator x = v.begin(); x <( v.end()-2); x++)
    {

        vector<int>::iterator y=x+1;
        vector<int>::iterator z=v.end();
        int sum=*x+*y+*z;
        while(sum!=0&&(y<z))
        {
            if(sum<0)
            {///crestem stanga
                y++;
                sum=*x+*y+*z;
            }
            if(sum>0)
            {///scadem dreapta
                z--;
                sum=*x+*y+*z;
            }
        }
        if(sum==0)
            cout<<'('<<*x<<','<<*y<<','<<*z<<")\n";
    }

    return 0;
}
