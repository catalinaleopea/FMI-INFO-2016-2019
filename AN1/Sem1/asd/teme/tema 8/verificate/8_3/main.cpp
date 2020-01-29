/**Sa se implementeze algoritmul randomized quick-sort (alegerea pivotului se va face aleator).**/
#include <iostream>
#include <time.h>
#include <stdlib.h>
using namespace std;

void quicksort(int st,int dr,int v[])
{
    int i=st;
    int j=dr;
    srand(time(NULL));
    int pivot=v[st+rand()%(dr-st+1)];
    while(i<=j)
    {
        while(v[i]<pivot)
            i++;
        while(v[j]>pivot)
            j--;
        if(i<=j)
        {
            swap(v[i],v[j]);
            i++;j--;
        }
    }
    if(st<j)
        quicksort(st,j,v);
    if(i<dr)
        quicksort(i,dr,v);
}

int main()
{
    int n;
    cout<<"Dati nr de elemente ";cin>>n;
    int v[n];
    for(int i=0;i<n;i++)
        cin>>v[i];
    quicksort(0,n-1,v);
    for(int i=0;i<n;i++)
        cout<<v[i]<<' ';
    return 0;
}
