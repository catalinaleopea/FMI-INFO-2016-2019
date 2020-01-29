#include <iostream>
#include <queue>

using namespace std;

class pPair{

public:
    string val;
    int priority;
    pPair(string val, int priority){
        this->val = val;
        this->priority = priority;
    }
};

bool operator< ( const pPair& x, const pPair& y) {
    return x.priority > y.priority;
}

int main()
{
    priority_queue<pPair> h;
    h.push(pPair("Stiva 1", 2));
    h.push(pPair("Stiva 2", 4));
    h.push(pPair("Stiva 3", 7));
    h.push(pPair("Stiva 4", 8));
    h.push(pPair("Stiva 5", 13));


    cout << h.top().val << " " << h.top().priority << endl;
    h.pop();
    h.push(pPair("Stiva 1", 3));

    cout << h.top().val << " " << h.top().priority << endl;
    h.pop();

    h.push(pPair("Stiva 1", 6));
    cout << h.top().val << " " << h.top().priority << endl;
    h.pop();


    h.push(pPair("Stiva 2", 5));
    cout << h.top().val << " " << h.top().priority << endl;
    h.pop();

    cout << h.top().val << " " << h.top().priority << endl;
    h.pop();

    cout << h.top().val << " " << h.top().priority << endl;
    h.pop();

    h.push(pPair("Stiva 3", 9));
    cout << h.top().val << " " << h.top().priority << endl;
    h.pop();

    h.push(pPair("Stiva 4", 12));
    cout << h.top().val << " " << h.top().priority << endl;
    h.pop();

    h.push(pPair("Stiva 3", 10));
    cout << h.top().val << " " << h.top().priority << endl;
    h.pop();

    cout << h.top().val << " " << h.top().priority << endl;
    h.pop();

    cout << h.top().val << " " << h.top().priority << endl;
    h.pop();

    h.push(pPair("Stiva 5", 14));
    cout << h.top().val << " " << h.top().priority << endl;
    h.pop();

    h.push(pPair("Stiva 5", 15));
    cout << h.top().val << " " << h.top().priority << endl;
    h.pop();
}
