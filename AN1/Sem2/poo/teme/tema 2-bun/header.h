#ifndef HEADER_H_INCLUDED
#define HEADER_H_INCLUDED
#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

class Harta{
int lungime,latime;          //dimensiunile hartii
int destx,desty;             //adresa comorii
public:
    Harta();                 //constructor fara parametrii
    Harta(int,int,char**);   //constructor
    ~Harta();                //destructor
    int getL();              //obtine lungimea
    int getl();              //obtine latimea
    void setComoara(int,int);//seteaza comoara
    int getXComoara();       //obtine pozitia ei
    int getYComoara();
    void afisare(char**);    //afisarea hartii
    void random(char**);     //plasarea obiectelor pe harta
};

class Item{
int id,pozx,pozy;
public:
    Item(int,int,int);//constructor cu parametrii
    ~Item();          //destructor
    int getId();      //obtine id-ul itemului
};

class Robot{  ///abstracta
void moveright();
void movedown();
void diag4();
protected:
    int x,y,bag;            //pozitia si un item maximum
public:
    Robot();                //constructor fara parametrii
    virtual ~Robot()=0;     ///destructor-fct virtuala pura
    void died();            //reseteaza la pozitia initiala
    void setBag(int);       //seteaza itemul detinut
    int getBag();           //obtine itemul
    void walk(Harta&,char**); //deplasarea
    virtual int getI()=0;   ///obtine itemul specific lui
    int verificare(char**,int,int);//verifica ce se afla la pozitia ij
    friend ostream& operator<<(ostream&,Robot&);//afisare
};
class MrHandy : public Robot{
const int it=2;  //itemul specific doar acestuia
//nu am de gand sa il modific,deci voi folosi const
public:
    MrHandy():Robot(),it(2){} //constructor cu lista de initializare
    ~MrHandy();//destructor
    int getI();//vede ce item are specific
};
class Ranger:public Robot{
const int it=3;
public:
    Ranger():Robot(),it(3){}
    ~Ranger();
    int getI();
};
class Doom:public Robot{
const int it=4;
public:
    Doom():Robot(),it(4){}
    ~Doom();
    int getI();
};

class Capcana{///abstracta
int id;
public:
    Capcana(){}              //constructor
    virtual ~Capcana()=0;    //destructor
    int getId();             //obtine id-ul
    void setId(int i);       //il seteaza
};
class Groapa:public Capcana{
int x,y;                //pozitia
public:
    Groapa(int,int);    //constructor
    ~Groapa();          //destructor
};
class Lac:public Capcana{
int x,y;
public:
    Lac(int,int);
    ~Lac();
};
class Spini:public Capcana{
int x,y;
public:
    Spini(int,int);
    ~Spini();
};

void Meniu(); //jocul
#endif // HEADER_H_INCLUDED
