#ifndef COD_H_INCLUDED
#define COD_H_INCLUDED
#include <iostream>

using namespace std;

template <class T>
class Polinom
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
    friend istream &operator>>(istream&i,Polinom &ob)//citirea
    {
        T nr,gr;
        T coef;
        cout<<"Dati numarul de elemente dorite: ";
        i>>nr;
        cout<<"\nDati gradele si coeficientii ca un sir de ";
        cout<<2*nr<<" numere, separate prin spatii:\n";
        for(T j=1; j<=nr; j++)
        {
            i>>gr>>coef;
            ob.inserare(gr,coef);
        }
        return i;
    }
    friend ostream &operator<<(ostream&i,const Polinom&ob)//afisarea
    {

        if(ob.prim==NULL)
            i<<"Polinom nul.\n";
        else
        {
            i<<"p: ";
            Polinom::Lista *p;
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
        }
        return i;
    }
};

///--citire--
//template <class T>   istream &operator>>(istream&i,Polinom<T> &ob)
//{
//    T nr,gr;
//    T coef;
//    cout<<"Dati numarul de elemente dorite: ";
//    i>>nr;
//    cout<<"\nDati gradele si coeficientii ca un sir de ";
//    cout<<2*nr<<" numere, separate prin spatii:\n";
//    for(T j=1; j<=nr; j++)
//    {
//        i>>gr>>coef;
//        ob.inserare(gr,coef);
//    }
//    return i;
//}

///--afisare--
//template <class T> ostream &operator<<(ostream&i,Polinom<T> &ob)
//{
//
//    if(ob.prim==NULL)
//        i<<"Polinom nul.\n";
//    else
//    {
//        i<<"p: ";
//        Polinom<T>::Lista *p;
//        for(p=ob.prim; p->leg!=NULL; p=p->leg)
//        {
//            if(p->coeficient!=1)
//                i<<p->coeficient<<"*x^"<<p->grad;
//            else
//                i<<"x^"<<p->grad;
//            if(p->leg->coeficient>=0)
//                i<<'+';
//        }
//        if(p->grad!=0)
//        {
//            if(p->coeficient!=1)
//                i<<p->coeficient<<"*x^"<<p->grad<<"\n";
//            else
//                i<<"x^"<<p->grad<<"\n";
//        }
//        else
//            i<<p->coeficient<<"\n";
//    }
//    return i;
//}
#endif // COD_H_INCLUDED
