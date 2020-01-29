#include "header.h"
///constructor fara parametrii
Harta::Harta()
{
    lungime=latime=0;
    destx=desty=0;
}
///constructor cu parametrii
//aloca dinamic matricea
Harta::Harta(int x,int y,char **mapa)
{
    cout<<"S-a construit harta\n";
    for(int i=0; i<x; i++)
        for(int j=0; j<y; j++)
            mapa[i][j]=' ';
    lungime=x;
    latime=y;
    destx=desty=0;
    cout<<"LEGENDA\nExista 3 tipuri de roboti:MrHandy,Ranger,Doom\n";
    cout<<"R:Robot;X:Comoara\n1:item universal\n2:item pt MrHandy\n";
    cout<<"3:item pt Ranger\n4:item pt Doom\n";
    cout<<"5:groapa;6:lac;7:spini\n";
    cout<<"Capcanele sunt mortale daca nu pot fi evitate cu itemi.\n";
    cout<<"jocul se incarca";
}
///destructor
Harta::~Harta()
{
    cout<<"S-a distrus harta\n";
}
///obtine lungimea hartii
int Harta::getL()
{
    return lungime;
}
///obtine latimea hartii
int Harta::getl()
{
    return latime;
}
///seteaza pozitia comorii
void Harta::setComoara(int x,int y)
{
    destx=x;
    desty=y;
}
///obtine pozitia comorii
int Harta::getXComoara()
{
    return destx;
}
int Harta::getYComoara()
{
    return desty;
}
///afisarea hartii dupa runda curenta
void Harta::afisare(char**mapa)
{
    //elementele sunt delimitate de linii
//verticale si orizontale pentru lizibilitate
    for(int i=0; i<latime*2; i++)
        cout<<'_';
    cout<<endl;
    for(int i=0; i<lungime; i++)
    {
        for(int j=0; j<latime; j++)
            cout<<mapa[i][j]<<'|';
        cout<<endl;
    }
    for(int i=0; i<latime*2; i++)
        cout<<'_';
    cout<<endl;
}
void Robot::moveright()
{
    y++;
}
void Robot::movedown()
{
    x++;
}
void Robot::diag4()
{
    ///dreapta jos
    x++;
    y++;
}
///constructor fara parametrii
//initial e in coltul din stanga sus
//si nu are itemi
Robot::Robot()
{
    x=y=bag=0;
}
///destructor
Robot::~Robot()
{
    cout<<"GAME OVER\n";
}
///in urma unei capcane
//se revine la pozitia initiala
void Robot::died()
{
    x=y=bag=0;
    cout<<"Robotul a murit.\n";
}
///insusirea itemului
void Robot::setBag(int i)
{
    bag=i;
}
//returneaza id-ul itemului
int Robot::getBag()
{
    return bag;
}
int Robot::verificare(char** mapa,int i,int j)
{
    char x=mapa[i][j];
    if(x==' '||x=='X')
        return 0;
    if(x=='1'||x=='2'||x=='3'||x=='4')
    {
        cout<<"Am gasit un item!\n";
        if(x=='1'||x==getI()+48)
        {
            setBag(x-48);
            cout<<"L-am luat!\n";
        }
        //adica itemul nu era nici universal,nici bun pt el
        else cout<<"Nu l-am putut lua, voi continua drumul.\n";
        return 0;
    }
    if(x=='5'||x=='6'||x=='7')
    {
        cout<<"Urmeaza o capcana pe aici! Sa imi verific geanta.\n";
        if(getBag()==0)
        {
            cout<<"Nu am nimic care sa ma poata ajuta.\n";
            died();
            return 1;
        }
        else switch(x)
            {
            case '5':
            {
                cout<<"In fata este o groapa, ";
                if(getBag()==1)
                {
                    setBag(0);
                    cout<<"am trecut cu succes.\n";
                }
                else//robotul nu se poate salva
                {
                    died();
                    return 1;
                }
                break;
            }
            case '6':
            {
                cout<<"In fata este un lac, ";
                if(getBag()==1||getBag()==3)
                {
                    setBag(0);
                    cout<<"am trecut cu succes.\n";
                }
                else
                {
                    died();
                    return 1;
                }
                break;
            }
            case '7':
            {
                cout<<"In fata sunt niste spini, ";
                if(getBag()==2||getBag()==4)
                {
                    setBag(0);
                    cout<<"am trecut cu succes.\n";
                }
                else
                {
                    died();
                    return 1;
                }
                break;
            }
            }
    }
}
///functia de deplasare
void Robot::walk(Harta& lume,char **mapa)
{
    //iau coordonatele comorii
    int dx=lume.getXComoara();
    int dy=lume.getYComoara();
    //cu i si j urmaresc pozitia robotului
    int i=0;
    int j=0;
    int x=0;
    char ok;
    do
    {
        if(x)
            break;
        else
        {
            cout<<"Doriti sa continuati?(y/n)\n";
            cin>>ok;
            if(ok=='y')
            {
                //cat timp ambii indici sunt mai mici decat poz comorii
                if(i<dx&&j<dy)//ma deplasez pe diagonala in dreapta jos
                {
                    x=verificare(mapa,i+1,j+1);
                    if(!x)
                    {
                        diag4();
                        mapa[i][j]=' ';
                        //dupa ce se muta actualizez in matrice ' '
                        //locul vechi si R cel nou($ daca a ajuns la comoara)
                        i++;
                        j++;
                        if(i==dx&&j==dy)
                            mapa[i][j]='$';
                        else mapa[i][j]='R';
                        lume.afisare(mapa);
                    }
                }
                else if(i<dx)//cat timp nu sunt pe linia comorii
                {
                    x=verificare(mapa,i+1,j);
                    //ma deplasez in jos catre ea
                    if(!x)
                    {
                        movedown();
                        mapa[i][j]=' ';
                        i++;
                        if(i==dx&&j==dy)
                            mapa[i][j]='$';
                        else mapa[i][j]='R';
                        lume.afisare(mapa);
                    }
                }
                else if(j<dy)//cat timp nu sunt pe coloana comorii
                {
                    x=verificare(mapa,i,j+1);
                    //merg in dreapta catre ea
                    if(!x)
                    {
                        moveright();
                        mapa[i][j]=' ';
                        j++;
                        if(i==dx&&j==dy)
                            mapa[i][j]='$';
                        else mapa[i][j]='R';
                        lume.afisare(mapa);
                    }
                }
            }
        }
    }
    while((i!=dx||j!=dy)&&(ok=='y'));
    if(i==dx&&j==dy)
        cout<<"Am ajuns la comoara!!!\n";
}
///afisarea unui robot
//pozitia curenta,statusul gentii
ostream& operator<<(ostream&i,Robot&ob)
{
    i<<"\nRobotul selectat are pozitia curenta "<<ob.x<<'x'<<ob.y;
    if(ob.bag)
        i<<" si itemul gasit "<<ob.bag<<'\n';
    else
        i<<" si nici un item.\n";
    return i;
}
///constructor cu parametrii
//initializeaza pozitia si id-ul
Item::Item(int x,int y,int cod)
{
    pozx=x;
    pozy=y;
    id=cod;
}
///destructor
Item::~Item()
{
    cout<<".";
}
///obtine id-ul itemului
int Item::getId()
{
    return id;
}
///destructor
Capcana::~Capcana() {}
///obtine id-ul capcanei
int Capcana::getId()
{
    return id;
}
///il seteaza
void Capcana::setId(int i)
{
    id=i;
}
///constructor cu parametrii
Groapa::Groapa(int a,int b)
{
    x=a;
    y=b;
    setId(5);
}
///destructor
Groapa::~Groapa()
{
    cout<<".";
}
///constructor cu parametrii
Lac::Lac(int a,int b)
{
    x=a;
    y=b;
    setId(6);
}
///destructor
Lac::~Lac()
{
    cout<<".";
}
///constructor cu parametrii
Spini::Spini(int a,int b)
{
    x=a;
    y=b;
    setId(7);
}
///destructor
Spini::~Spini()
{
    cout<<".";
}
///destructor
MrHandy::~MrHandy()
{
    cout<<"MrHandy si-a incheiat misiunea\n";
}
///obtine id-ul itemului pe care il poate lua doar el
int MrHandy::getI()
{
    return it;
}
///destructor
Ranger::~Ranger()
{
    cout<<"Ranger si-a incheiat misiunea\n";
}
///obtine id-ul itemului pe care il poate lua doar el
int Ranger::getI()
{
    return it;
}
///destructor
Doom::~Doom()
{
    cout<<"Doom si-a incheiat misiunea\n";
}
///obtine id-ul itemului pe care il poate lua doar el
int Doom::getI()
{
    return it;
}
///plaseaza obiectele randomizat pe harta
void Harta::random(char**mapa)
{
    mapa[0][0]='R';//aici voi plasa robotul
    int a,b;
    int x=getL();//obtin dimensiunile mapei
    int y=getl();
    //generez perechile de numere aleatoriu
    srand(time(0));
    a=rand()%x;
    b=rand()%y;
    //setez comoara(si codificarea in matrice)
    setComoara(a,b);
    mapa[a][b]='X';
    for(int i=1; i<20; i++)
    {
        srand(time(NULL));
        a=rand()%x;
        b=rand()%y;
        while(mapa[a][b]!=' ')
        {
            srand(time(NULL));
            a=rand()%x;
            b=rand()%y;
        }
        if((i%10)<5 &&  (i%10)>0)
        {
            //adun 48 la decimal deoarece,ex (int)1 in ASCII=SOH
            //insa (int)49=(char)'1'
            Item it(a,b,i%10);
            mapa[a][b]=it.getId()+48;
        }
        if(i%10==5)
        {
            Groapa g(a,b);
            mapa[a][b]=g.getId()+48;
        }
        if(i%10==6)
        {
            Lac l(a,b);
            mapa[a][b]=l.getId()+48;
        }
        if(i%10==7)
        {
            Spini s(a,b);
            mapa[a][b]=s.getId()+48;
        }
    }
}

void Meniu()
{
    cout<<"Dati dimensiunile hartii ";
    int x,y;
    cin>>x>>y;
    while(x<15||y<15)//ca sa am dimensiunea minim 15x15
        cin>>x>>y;
    //aloc dinamic matrice de caractere in care voi
    //codifica prezenta itemilor/capcanelor/robotului/comorii
    //si o voi actualiza la fiecare runda
    //initial o voi completa cu spatii
    char** mapa=new char*[x];
    for(int i=0; i<x; i++)
        mapa[i]=new char[y];
    //obiect in care retin matricea de caractere
    //dimensiunea,comoara
    //si desfasurarea rundelor
    Harta lume(x,y,mapa);
    lume.random(mapa);
    cout<<"\nHarta arata initial\n";
    lume.afisare(mapa);
    int selectie;
    do
    {
        cout<<"Cu ce robot doriti sa jucati?\n";
        cout<<"Apasati 1 pentru MrHandy\n";
        cout<<"Apasati 2 pentru Ranger\n";
        cout<<"Apasati 3 pentru Doom\n";
        cin>>selectie;
    }
    while (selectie<1||selectie>3);
    switch (selectie)
    {
    case 1:
    {
        MrHandy mrHandy;
        mrHandy.walk(lume,mapa);
        cout<<mrHandy;
        break;
    }
    case 2:
    {
        Ranger ranger;
        ranger.walk(lume,mapa);
        cout<<ranger;
        break;
    }
    case 3:
    {
        Doom doom;
        doom.walk(lume,mapa);
        cout<<doom;
        break;
    }
    }
    //dezaloc matricea
    for(int i=0; i<=x; i++)
        delete [] mapa[i];
    delete [] mapa;
}
