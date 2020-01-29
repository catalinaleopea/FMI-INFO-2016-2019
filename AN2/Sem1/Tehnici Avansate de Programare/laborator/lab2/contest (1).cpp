#include <iostream>
#include <fstream>
#include <cstring>
#include <unordered_map>
#include <vector>
using namespace std;

#define MIN_INF -320000;
#define MAX_IDX 1000;
#define MAX_LENGTH 32

struct Round
{
    string name;
    int score;
};

//	ifstream f("date.in");
unordered_map< string, int > M1, M2;
vector <Round> rounds;

int main()
{
    int n, score, max = MIN_INF;
    int idx_min = MAX_IDX;
    string name;
    string max_name;

    //f>>n;
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        //f >> name;
        //f >> score;
        Round R;
        cin >> R.name;
        cin >> R.score;

        score = R.score;
        name = R.name;

        rounds.push_back(R);

        if (M1.find(name) != M1.end())
        {
            M1[name] = M1[name]+ score;
        }
        else
        {
            M1[name] = score;
        }
    }

    for( unordered_map<string, int>::iterator i = M1.begin(); i != M1.end(); i++)
    {
        if (i->second > max )
        {
            max = i->second;
        }
    }


    return 0;
}
