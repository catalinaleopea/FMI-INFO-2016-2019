// Condrea Florin Grupa 135
#include <iostream>
#include <vector>
#include <cstring>
using namespace std;
class Produs;
class Ospatar;
class Comanda;
vector <Produs*> VP;
vector <Comanda*> VC;
vector <Ospatar*> VO;
struct DataCalendar
{
    int zi;
    int luna;
    int an;
};
class Produs
{
private:
    string denProd;
    int PretProd;
public:
    Produs(string den,int pret)
    {
        this->denProd = den;
        this->PretProd = pret;
        VP.push_back(this);
    }
    friend ostream& operator<<(ostream& os,Produs* p)
    {
        os<<" ( " << p->denProd <<" , "<< p->PretProd<<" ) ";
        return os;
    }
    bool ComVal(string den)
    {
        if (den == this->denProd) return true;
        return false;
    }
    string nume()
    {
        return this->denProd;
    }
    float GetPret()
    {
        return this->PretProd;
    }
};
class Comanda
{
protected:
    static int Num;
    int NumCom;
    Produs* Prod;
    int nrPortii;
     int zi;
     int luna;
     int an;
public:
    Comanda(){};
    Comanda(Produs* p,int portii, int zi,int luna,int an)
    {
        this->Num++;
        this->NumCom=this->Num;
        this->nrPortii = portii;
        this->Prod = p;
        this->zi = zi;
        this->luna = luna;
        this->an = an;
        VC.push_back(this);
    }
    void operator++()
    {
        this->nrPortii++;
    }
    void operator+(int x)
    {
        int k;
        this->nrPortii+=x;
    }
    void del()
    {
        delete this;
    }
    friend ostream& operator<<(ostream& os,Comanda* c)
    {
        os<<" ( " << c->NumCom <<" , "<< c->Prod<<" , "<<c->nrPortii<<" , "<<c->zi<<" , "<<c->luna<<" "<<c->an;
        return os;
    }
    bool DataVal()
    {
        if (this->zi==31&&this->luna==5&&this->an==2016) return true;
    }
    int CautareComanda(string x)
    {
        if (this->Prod->nume()==x)
            return this->nrPortii;
        return 0;
    }
    bool mai(int lun)
    {
        if (this->luna==lun) return true;
    }
    virtual float bani()
    {
        return Prod->GetPret()*nrPortii;
    }
    int GetAn()
    {
        return this->an;
    }
};
int Comanda::Num=0;
class ComOnline : public Comanda
{
private:
    string adresa;
    int ComLvr;
public:
    ComOnline(Produs* p,int portii, int zi, int luna, int an, string adresa, int ComLvr):Comanda(p,portii,zi,luna,an)
    {
        this->adresa= adresa;
        this->ComLvr = ComLvr;
    }
    virtual float bani()
    {
        return Prod->GetPret()*nrPortii*ComLvr/100;
    }
    friend ostream& operator<<(ostream& os,ComOnline* c)
    {
        os<<" ( " << c->NumCom <<" , "<< c->Prod<<" , "<<c->nrPortii<<" , "<<c->zi<<" , "<<c->luna<<" "<<c->an<<c->adresa<<" "<<c->ComLvr<<" ";
        return os;
    }
};
class Comspc : public Comanda
{
private:
    float pret_supl;
public:
    Comspc(Comanda* c, string Adaugire,float pret_supl)
    {

    }
};
class Ospatar
{
private:
    string Nume;
    vector<Comanda*> comenzi;
    int nrComenzi;
    char gen;
    int varsta;
public:
    Ospatar(string nm,vector<Comanda*> c,int nrCom,char gen,int vst)
    {
        this->Nume = nm;
        this->gen = gen;
        this->varsta =vst;
        this->comenzi = c;
        VO.push_back(this);
    }
    friend bool operator>(Ospatar& op1,Ospatar& op2)
    {
        return (op1.nrComenzi>op2.nrComenzi);
    }
    friend bool operator==(Ospatar& op1,Ospatar& op2)
    {
        return (op1.nrComenzi==op2.nrComenzi);
    }
    friend ostream& operator<<(ostream& os,Ospatar& o)
    {
        cout<<o.Nume<<" "<<o.nrComenzi<<" "<<o.gen<<" "<<o.varsta<<"\n";
        for (int i=0;i<o.comenzi.size();i++)
        {
            cout<<o.comenzi[i]<<"\n";
        }
    }
    string nume()
    {
        return this->Nume;
    }
    float venit()
    {
        float tot=0;
        for (int i=0;i<comenzi.size();i++)
        {
            tot += comenzi[i]->bani();
        }
        return tot;
    }
};

void citire()
{
    int x=5;
    while (x!=0)
    {
        cout<<" 6. Adaugare produs  \n 7. adaugare comanda. \n 1.luna mai \n 2.papanasi \n 3.procent incasari \n 4. ospatarul anului \n 0.Exit \n";
        cin>>x;
        if (x==6)
        {
            cout<<" Introducer Produs nou \n";
            string den;
            int pret;
            cout<<"denumire \n";
            cin>>den;
            cout<<"pret \n";
            cin>>pret;
            Produs* p = new Produs(den,pret);
            VP.push_back(p);
        }
        else if (x==7)
        {
            int i;
            cout<<"Comanda noua \n";
            int zi,luna,an;
            int portii;
            string den;
            cout<<" nr portii \n";
            cin>>portii;
            cout<<"data comenzii\n";
            cin>>zi>>luna>>an;
            cout<<"nume produs\n";
            cin>>den;
            for ( i=0;i<VP.size();i++)
            {
                if (VP[i]->ComVal(den)) break;
            }
            if (i<VP.size())
            {
                Comanda* c = new Comanda(VP[i],portii,zi,luna,an);//dt);
                VC.push_back(c);
            }
        }
        else if (x==8)
        {
            cout<<"Angajare ospatar \n";
        }
        else if (x==1)
        {
            for (int i=0;i<VC.size();i++)
            {
                if (VC[i]->DataVal()) cout<<VC[i]<<"\n";
            }
        }
        else if (x==2)
        {
            int nr=0;
            for (int i=0;i<VC.size();i++)
            {
                nr += VC[i]->CautareComanda("papnasi");
                nr += VC[i]->CautareComanda("papnasi cu nuca de cocos");
            }
            cout<<"S au vandut atatia papanasi "<<nr<<"\n";
        }
        else if (x==3)
        {
            float tot=0;
            float mai=0;
            for (int i=0;i<VC.size();i++)
            {
                tot += VC[i]->bani();
                if (VC[i]->mai(5)) mai=VC[i]->bani();;
            }
            cout<<"Total "<< tot <<"\n Mai " <<mai<<"\n procent"<<tot/mai*100<<" % \n";
        }
        else if (x==4)
        {
            Ospatar* os;
            int v=0;
            for (int i=0;i<VO.size();i++)
            {
                if (VO[i]->venit()>v)
                {
                    os =VO[i];
                    v = VO[i]->venit();
                }
            }
            cout<<os;
        }
    }
}
int main()
{
   citire();
}
