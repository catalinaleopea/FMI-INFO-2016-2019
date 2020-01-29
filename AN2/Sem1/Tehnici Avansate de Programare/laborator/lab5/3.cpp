#include <iostream>
#include <vector>
#include <fstream>
#include <string>
using namespace std;

int main()
{
    ifstream f("date.in");
    ifstream f2("cod.in");
    vector<string> coduri;
    string cod;
    int n, m;
    f>>m;
    for(int i = 0; i < m; i++)
    {
        string cod;
        f>>cod;
        coduri.push_back(cod);
    }
    string w1 = "0";
    string w2 = "1";
    coduri.push_back(w1);
    coduri.push_back(w2);
    f2>>cod;
    int i = 0, j = 1;
    while(i < cod.size())
    {
        j = i+1;
        while(j < cod.size() + 1)
        {
            string subcod = cod.substr(i, j - i);
            string subcod2 = subcod;
            if(j < cod.size())
                subcod2 = cod.substr(i, j - i + 1);
            else subcod2 = "-1";
            int ok = 1, ok2 = 0;
            for(int k = 0; k < m + 2; k++)
            {
                if(subcod2 == coduri[k])
                    ok = 0;
                if(subcod == coduri[k])
                    ok2 = 1;
            }
            if(ok && ok2)
            {
                cout<<subcod<<"+";
                i = j - 1;
                break;
            }
            j++;
        }
        i++;
    }
    return 0;
}
