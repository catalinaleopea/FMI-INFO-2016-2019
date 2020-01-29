#ifndef COD_H_INCLUDED
#define COD_H_INCLUDED
#include <iostream>

using namespace std;

class Polinom
{
    struct Lista//lista simplu inlantuita pt polinoame
    {
        int grad;
        int coeficient;
        Lista *leg;
    }*prim;
    void adaugareInceput(int,int);//insereaza la inceput
    void inserare(int,int); //insereaza termenii in polinom in ordine
    //descrescatoare dupa grad
public:
    Polinom();//constructor
    Polinom(int,int);//constructor cu parametrii
    Polinom(const Polinom &);//copy constructor
    ~Polinom();//destructor

    void operator=(const Polinom &);//copierea unui polinom
    Polinom operator+(const Polinom &);//aduna doua polinoame
    Polinom operator*(const Polinom &);//inmulteste doua polinoame
    Polinom operator/(const Polinom &);//imparte doua polinoame
    void operator[](int);//obtine coeficientul termenului cu gradul dat
    friend istream &operator>>(istream&,Polinom &);//citire
    friend ostream &operator<<(ostream&,const Polinom&);//afisare

    void calcul(int);//calculul intr-un punct
    int gradul();//maxim
};
#endif // COD_H_INCLUDED
