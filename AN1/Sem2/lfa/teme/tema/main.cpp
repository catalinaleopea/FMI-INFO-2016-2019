#include <iostream>
#include <vector>
#include <set>
#include <fstream>

using namespace std;

ifstream in("date.in");

int main()
{
    int n, m, stare_init, nr_fin,i;
    vector < vector < pair <int, char> > > la_afn;///Lista de adiacenta pentru AFN
    vector <int> stare_finala;///Vectorul de stari finale
    in>>n>>m>>stare_init>>nr_fin;
    for(int i=0; i<nr_fin; i++)
    {
        int nod;
        in>>nod;///Enumeram starile finale
        stare_finala.push_back(nod);
    }
    set <char> alfabet;///Memoram alfabetul si il codificam (unei litere ii corespunde un numar)
    set <char>::iterator it;
    la_afn.resize(n+1);
    for(i=0; i<m; i++)
    {
        int u, v;
        char litera;
        in>>u>>v>>litera;
        if(alfabet.count(litera)==0)
            alfabet.insert(litera);///Bagam o litera in alfabet doar daca nu mai apare
        la_afn[u].push_back(make_pair(v,litera));///Cream lista de adiacenta
    }
    cout<<"Lista de adiacenta a grafului AFN este:\n";
    for(i=1; i<n; i++)///Afisare AFN
    {
        cout<<"Nodul "<<i<<" are vecinii: ";
        for(unsigned int j=0; j<la_afn[i].size(); j++)
            if(j==la_afn[i].size()-1)
                cout<<la_afn[i][j].first<<" cu ponderea "<<la_afn[i][j].second;
            else
                cout<<la_afn[i][j].first<<" cu ponderea "<<la_afn[i][j].second<<", ";
        cout<<'\n';
    }
    cout<<'\n';
    vector < pair < vector <int>, vector < vector <int> > > > tabel_afd;///Vectorul pentru tabelul de transformare
    ///Avem o pereche, in primul vector memoram starile simple si compuse
    ///Al doilea membru al perechii este o matrice de int, unde pe linii este codificarea alfabetului,
    ///iar pe coloane memoram
    int nr_stari=1;
    tabel_afd.resize(nr_stari);///Initial, tabelul transformarii are doar stare initiala
    tabel_afd[0].first.push_back(stare_init);
    tabel_afd[0].second.resize(alfabet.size());
    for(i=0; i<la_afn[stare_init].size(); i++)///Completam tabelul pentru starea initiala
    {
        char ceva=la_afn[stare_init][i].second;
        int cnt=0, ok=0;
        for(it=alfabet.begin(); it!=alfabet.end(); it++)
        {
            if(*it==ceva)
                ok=1;
            cnt++;
            if(ok)
                break ;
        }
        tabel_afd[0].second[cnt-1].push_back(la_afn[stare_init][i].first);
    }
    for(unsigned int j=0; j<tabel_afd.size(); j++)
    {
        for(unsigned int k=0; k<tabel_afd[j].second.size(); k++)
        {
            vector <int> nod;///Vectorul cu care memoram starile AFD-ului
            for(unsigned int l=0; l<tabel_afd[j].second[k].size(); l++)
                nod.push_back(tabel_afd[j].second[k][l]);
            int nr2=0;
            for(unsigned int indice1=0; indice1<nod.size(); indice1++)///Verificam daca mai exista starea pe care
                ///vream s-o introducem
            {
                int test3=nod[indice1];
                nr2=nr2*10+nod[indice1];
            }
            int ok=1;
            for(unsigned int indice=0; indice<tabel_afd.size(); indice++)
            {
                int nr1=0;
                for(unsigned int indice1=0; indice1<tabel_afd[indice].first.size(); indice1++)
                {
                    int test2=tabel_afd[indice].first[indice1];
                    nr1=nr1*10+tabel_afd[indice].first[indice1];
                }
                if(nr1==nr2)///Daca exista starea, o ignoram
                    ok=0;
            }
            if(ok and nr2)///Daca starea nu a fost gasita si nr2 are o valoare diferita de 0
                ///Pentru nr2=0 apareau valori dubioase
            {
                nr_stari++;///Crestem numarul de stari
                tabel_afd.resize(nr_stari);
                for(unsigned int indice=0; indice<nod.size(); indice++)
                {
                    int test4=nod[indice];
                    tabel_afd[nr_stari-1].first.push_back(nod[indice]);///Bagam in AFD starile simple/compuse
                }
                tabel_afd[nr_stari-1].second.resize(alfabet.size());///Redimensionam al doilea membru al perechii
                for(unsigned int indice=0; indice<nod.size(); indice++)
                {
                    for(unsigned int indice1=0; indice1<la_afn[nod[indice]].size(); indice1++)
                    {
                        int test=la_afn[nod[indice]][indice1].first, test5=nod[indice];
                        char ceva=la_afn[nod[indice]][indice1].second;
                        int cnt1=0, ok1=0;
                        for(it=alfabet.begin(); it!=alfabet.end(); it++)///Codificam alfabetul
                            ///Fiecare litera va fi un indice in tabel_afd
                        {
                            if(*it==ceva)
                                ok1=1;
                            cnt1++;
                            if(ok1)
                                break ;
                        }
                        int ok2=1;
                        for(unsigned int indice2=0; indice2<tabel_afd[nr_stari-1].second[cnt1-1].size(); indice2++)
                            if(la_afn[nod[indice]][indice1].first==tabel_afd[nr_stari-1].second[cnt1-1][indice2])
                                ok2=0;///Verificam daca starea pe care vrem s-o introducem este memorata
                        if(ok2)///Daca nu, o introducem. Asa evitam aparitia in starile compuse a doua cifre egale
                            tabel_afd[nr_stari-1].second[cnt1-1].push_back(la_afn[nod[indice]][indice1].first);
                    }
                }
            }
        }
    }
    vector < vector <int> > stari_finale_afd;
    int indice=0;
    for(i=0; i<tabel_afd.size(); i++)
    {
        int ok=0;
        for(unsigned int j=0; j<tabel_afd[i].first.size(); j++)
            for(unsigned int k=0; k<stare_finala.size(); k++)
            {
                if(stare_finala[k]==tabel_afd[i].first[j])
                    ok=1;
            }
        if(ok)
        {
            for(unsigned int j=0; j<tabel_afd[i].first.size(); j++)
            {
                stari_finale_afd.resize(indice+1);
                stari_finale_afd[indice].push_back(tabel_afd[i].first[j]);
            }
            indice++;
        }
    }
    cout<<"Lista de adiacenta a grafului AFD este:\n";///Afisarea
    for(i=0; i<tabel_afd.size(); i++)
    {
        cout<<"Vecinii nodului ";
        for(unsigned int j=0; j<tabel_afd[i].first.size(); j++)
            cout<<tabel_afd[i].first[j];
        if(tabel_afd[i].first.size()!=0)
            cout<<" sunt: ";
        for(unsigned int j=0; j<tabel_afd[i].second.size(); j++)
        {
            char litera;
            for(unsigned int k=0; k<tabel_afd[i].second[j].size(); k++)
            {
                cout<<tabel_afd[i].second[j][k];
                int cnt=j, cnt1=0, test=tabel_afd[i].second[j][k];
                for(it=alfabet.begin(); it!=alfabet.end(); it++)
                {
                    if(cnt1==cnt)
                        litera=*it;
                    cnt1++;
                }
            }
            if(tabel_afd[i].second[j].size())
                cout<<" cu ponderea "<<litera<<' ';
        }
        cout<<'\n';
    }
    cout<<'\n';
    cout<<"Starile finale din AFD sunt:\n";
    for(i=0; i<stari_finale_afd.size(); i++)
    {
        for(unsigned int j=0; j<stari_finale_afd[i].size(); j++)
            cout<<stari_finale_afd[i][j];
        cout<<'\n';
    }
    return 0;
}
