/**4. Sã se scrie algoritmul pentru sortarea unui ºir de numere folosind metoda Heapsort. Structura de Heap va fi implementatã ca un arbore binar într-una din cele douã forme care urmeazã :
a) max - Heap – arbore binar în care fiecare nod are cheia mai mare decât oricare dintre fiii sãi
b) min - Heap – arbore binar în care fiecare nod are cheia mai micã decât oricare dintre fiii sãi
Scrieþi funcþii pentru crearea heap-ului ºi pentru decapitarea lui.**/
#include <iostream>
using namespace std;

maxHeapifyDown(int);
maxHeapifyUp(int);
pushToHeap(int);
extractMax(int);
extractMin(int);

void maxHeapifyDown(int index)
{
    if(index<1||index>n)
        return;
    int left,right,x=index;
    left=2*index;
    right=2*index+1;
    if(left<=n&&heap[left]>=heap[x])
        x=left;
    if(right<=n&&heap[right]>=heap[x])
        x=right;
    if(x!=index)
    {
        swap(heap[index],heap[x]);
        maxHeapifyDown(x);
    }
}

void buildMax()
{
    for(int i=n/2;i>=1;i--)
        maxHeapifyDown(i);
}

void heapSort()
{
    buildMax();
    for(int i=n;i>=1;i--)
    {
        swap(heap[i],heap[1]);
        maxHeapifyDown(1,i-1);
    }
}

int main()
{
    return 0;
}
