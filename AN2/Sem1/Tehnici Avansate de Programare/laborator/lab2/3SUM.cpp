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

    sort(v.begin(),v.end());

    for (vector<int>::iterator x = v.begin(); x < v.end(); x++)
        for(vector<int>::iterator y = x + 1; y < v.end(); y++){
            if ( binary_search(y + 1,v.end(), -(*x+*y)))
                cout << "DA" << " " << *x << " " << *y << " " << -(*x+*y) << endl;
    }

    return 0;
}
