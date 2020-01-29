#ifndef COD_H_INCLUDED
#define COD_H_INCLUDED
#include <iostream>
using namespace std;

template <class T> class Polinom
{
    struct Lista        //lista simplu inlantuita pt polinoame
    {
        T grad, coeficient;
        Lista *leg;
    }*prim;
    void adaugareInceput(T,T);//insereaza la inceput
    void inserare(T,T); //insereaza termenii in polinom in ordine
    //descrescatoare dupa grad
public:
    Polinom();          //constructor
    Polinom(T gr,T coef);//constructor cu parametrii
    Polinom(const Polinom &ob2);//copy constructor
    ~Polinom();         //destructor
    void calcul(T x);   //calculul intr-un punct
    T gradul();         //maxim
    void operator=(const Polinom &ob2);   //copierea unui polinom
    Polinom operator+(const Polinom &ob2);//adunarea
    Polinom operator*(const Polinom &ob2);//inmultirea
    void operator/(const Polinom &ob2);//impartirea
    void operator[](T i);//obtine coeficientul termenului cu gradul dat
    template <class newT> friend istream &operator>> (istream&i,Polinom<newT> &);     //citirea
    friend ostream &operator<<(ostream&i,const Polinom<T> &ob)//afisarea
    {
        if(ob.prim==NULL)
        {
            i<<"Polinom nul.\n";
            return i;
        }
        i<<"p: ";
        Polinom<T>::Lista *p;
        for(p=ob.prim; p->leg!=NULL; p=p->leg)
        {
            if(p->coeficient!=1)
                i<<p->coeficient<<"*x^"<<p->grad;
            else
                i<<"x^"<<p->grad;
            if(p->leg->coeficient>=0)
                i<<'+';
        }
        if(p->grad!=0)
        {
            if(p->coeficient!=1)
                i<<p->coeficient<<"*x^"<<p->grad<<"\n";
            else
                i<<"x^"<<p->grad<<"\n";
        }
        else
            i<<p->coeficient<<"\n";
        return i;
    }
};
#endif // COD_H_INCLUDED
