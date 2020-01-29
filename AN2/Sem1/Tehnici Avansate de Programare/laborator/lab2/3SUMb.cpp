#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include <algorithm>
using namespace std;

ifstream f("date.in");
int n, a, b, c;
vector<int> v;
set<int> s;

int main()
{
    f >> n;

    for(int i =  0; i < n; i++){
            f >> a;
            v.push_back(a);
            s.insert(a);
    }

    v.resize(n);

    for (vector<int>::iterator x = v.begin(); x < v.end(); x++)
        for(vector<int>::iterator y = x + 1; y < v.end(); y++){
            if ( s.find(-(*x+*y))!= s.end())
                cout << "DA" << " " << *x << " " << *y << " " << -(*x+*y) << endl;
            if ( find(s.begin(),s.end(), -(*x+*y))!= s.end())
                cout << "DA" << " " << *x << " " << *y << " " << -(*x+*y) << endl;
    }

    return 0;
}
