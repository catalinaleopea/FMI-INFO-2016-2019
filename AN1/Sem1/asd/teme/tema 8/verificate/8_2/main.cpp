/**Sã se implementeze metoda de ordonare Merge – Sort.**/
#include <iostream>
using namespace std;

void interclasare(int st,int dr,int v[])
{
    int mij=(st+dr)/2;
    int i=st;
    int j=mij+1;
    int temp[dr-st+1];
    int index=0;
    while(i<=mij&&j<=dr)
    {
        if(v[i]<v[j])
            temp[index++]=v[i++];
        else
            temp[index++]=v[j++];
    }
    while(i<=mij)
        temp[index++]=v[i++];
    while(j<=dr)
        temp[index++]=v[j++];
    for(i=0;i<index;i++)
        v[st+i]=temp[i];
}

void mergeSort(int st,int dr,int v[])
{
    if(st<dr)
    {
        int mij=(st+dr)/2;
        mergeSort(st,mij,v);
        mergeSort(mij+1,dr,v);
        interclasare(st,dr,v);
    }
}

int main()
{
    int n;
    cout<<"Dati nr de elemente ";cin>>n;
    int v[n];
    for(int i=0;i<n;i++)
        cin>>v[i];
    mergeSort(0,n-1,v);
    for(int i=0;i<n;i++)
        cout<<v[i]<<' ';
    return 0;
}
