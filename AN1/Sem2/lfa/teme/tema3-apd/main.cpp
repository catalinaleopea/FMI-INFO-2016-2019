///Acceptarea unui cuvant intr-un APD prin stari finale si vidarea stivei

#include <iostream>
#include <vector>
#include <stack>
#include <string>
#include <fstream>

using namespace std;

ifstream fin("date.in");
ofstream fout("date.out");

void DFS(vector < vector < pair < pair <int, char>, pair <char, vector < char > > > > > lista,
         vector <int> &vizitat, stack <char> stiva, vector <int> stariF,
         string cuvant, int nod, unsigned int poz, int &ok, int n)
{
//nod=nod curent din lista                     poz=pozitia curenta din cuvant
//ok=pt a se opri la sfarsitul cuvantului      n=nr de stari

    if(poz==cuvant.size() && stiva.empty())//Daca s-a ajuns la sfarsitul cuvantului si stiva e vida
        for(unsigned int i=0; i<stariF.size(); i++)//parcurg starile finale
            if(stariF[i]==nod)
            {
                ok=1;
                return;
            }
    for(unsigned int i=0; i<lista[nod].size(); i++)
    {
        if(!stiva.empty()&&!ok&& (lista[nod][i].second.first==stiva.top() || lista[nod][i].second.first=='l'))
        {
            //Daca stiva nu e vida, nu s-a ajuns la final si daca avem o lambda tranzitie sau
            //elementul din varful stivei trebuie scos
            if(lista[nod][i].first.second==cuvant[poz] && lista[nod][i].first.second!='l')
            {
                //Daca s-a ajuns la o litera care duce intr-o alta stare si nu e lambda
                vizitat.assign(n+1,0);//Vectorul de vizitat devine 0
                stiva.pop();
                for(int j=lista[nod][i].second.second.size()-1; j>=0; j--)
                    if(lista[nod][i].second.second[j]!='l')
                        stiva.push(lista[nod][i].second.second[j]);//pun elementele in stiva
                DFS(lista, vizitat, stiva, stariF, cuvant, lista[nod][i].first.first, poz+1, ok, n);
            }
            else if(lista[nod][i].first.second=='l' && !vizitat[lista[nod][i].first.first])
            {
                //Daca avem o lambda tranzitie si nodul e nevizitat
                vizitat[lista[nod][i].first.first]=1;
                stiva.pop();
                for(int j=lista[nod][i].second.second.size()-1; j>=0; j--)
                    if(lista[nod][i].second.second[j]!='l')
                        stiva.push(lista[nod][i].second.second[j]);//pun elementele in stiva
                DFS(lista, vizitat, stiva, stariF, cuvant, lista[nod][i].first.first, poz, ok, n);
            }
        }
    }
}

int main()
{
    int n, m;
    fin>>n>>m;
    string cuvant;
    vector <int> stariF;//Vectorul de stari finale
    vector <int> vizitat (n+1);//Vectorul de vizitat va fi folosit doar la lambda tranzitii
    vector < vector < pair < pair <int, char>, pair <char, vector < char > > > > > lista(n+1);
    //Lista de adiacenta
    //in .first este nodul in care duce arcul si litera mica
    //in .second varful stivei si pun in stiva-litere mari
    for(int i=0; i<m; i++)
    {
        int u, v, lungime;//uv arc
        char litera, litera_S;//litera mica si litera mare
        fin>>u>>v>>litera>>litera_S>>lungime;
        vector <char> sir;
        for(int j=0; j<lungime; j++)
        {
            char c;
            fin>>c;
            sir.push_back(c);
        }
        lista[u].push_back(make_pair(make_pair(v, litera), make_pair(litera_S, sir)));
    }
    int intiala, nr_stariF;
    fin>>intiala>>nr_stariF;
    for(int i=0; i<nr_stariF; i++)//citim starile finale
    {
        int nod;
        fin>>nod;
        stariF.push_back(nod);
    }
    fin>>cuvant;
    //Afisare
    fout<<"APD-ul este:\n";
    for(int i=1; i<=n; i++)
    {
        fout<<"Nodul "<<i<<" are vecinii: ";
        for(unsigned int j=0; j<lista[i].size(); j++)
        {
            fout<<lista[i][j].first.first<<' '<<lista[i][j].first.second<<','<<lista[i][j].second.first<<"/";
            for(unsigned int k=0; k<lista[i][j].second.second.size(); k++)
                fout<<lista[i][j].second.second[k];
            fout<<' ';
        }
        fout<<'\n';;
    }
    fout<<'\n';
    fout<<"Starea initiala este: "<<intiala<<'\n';
    fout<<"Starile finale sunt: ";
    for(unsigned int i=0; i<stariF.size(); i++)
        fout<<stariF[i]<<' ';
    fout<<'\n';
    int ok=0, poz=0;
    stack <char> stiva;
    stiva.push('Z');//Initial, stiva contine caracterul Z
    DFS(lista, vizitat, stiva, stariF, cuvant, intiala, poz, ok, n);
    fout<<'\n';
    if(ok)
        fout<<"Cuvantul este acceptat\n";
    else
        fout<<"Cuvantul nu este acceptat\n";
}
