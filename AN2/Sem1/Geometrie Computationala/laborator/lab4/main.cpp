#include <iostream>
#include <cmath>
#define PI 3.14159265
using namespace std;

struct pereche{
    double x,y;
}A[4];

void citire(){
    cout<<"Introduceti coordonatele punctelor: \n";
    for (int i=0; i<4;i++){
        cin>>A[i].x>>A[i].y;
    }
}

void afisare(){
    cout<<"Punctele sunt: \n";
    for (int i=0;i<4;i++){
        cout<<"Punctul "<<i+1<<" are coordonatele ("<<A[i].x<<","<<A[i].y<<")\n";
    }
}

pereche vect(pereche a, pereche b){
    pereche temp;
    temp.x = b.x-a.x;
    temp.y = b.y-a.y;
    return temp;
}

//inmultirea a doi vectori
double inmultire(pereche a , pereche b){
    return (a.x * b.x) + (a.y * b.y);
}

double  norma(pereche a){
    return sqrt((a.x * a.x) + (a.y * a.y));
}

double cos(pereche a, pereche b){
    return inmultire(a, b)/(norma(a) * norma(b));
}

void pozitiaFataDeCerc(){
    double rezultat, m1, m2;
    m1 =cos(vect(A[1],A[2]),vect (A[1],A[0]));
    m2 =cos(vect(A[3],A[2]),vect (A[3],A[0]));
    rezultat= acos(m1)*(180/PI)+acos(m2)*(180/PI);
    if(rezultat>180)
        cout<<"Punctul se afla in interiorul cercului\n";
        else
            if(rezultat<180)
                cout<<"Punctul se afla in afara cercului\n";
            else
                cout<<"Punctul se afla pe cerc\n";
}

double lungime(pereche a, pereche b){
    return sqrt((b.x - a.x) * (b.x - a.x)+(b.y - a.y) * (b.y - a.y));
}

void isCircumscriptibil(){

    double a1a2=lungime(A[0],A[1]);
    double a1a4=lungime(A[0],A[3]);
    double a2a3=lungime(A[1],A[2]);
    double a3a4=lungime(A[2],A[3]);
    if(a1a2+a3a4==a2a3+a1a4)
        cout<<"Patrulaterul este circumscriptibil\n";
        else
            cout<<"Patrulaterul nu este circumscriptibil\n";
}
int main()
{
    citire();
    afisare();
    pozitiaFataDeCerc();
    isCircumscriptibil();
    return 0;
}
