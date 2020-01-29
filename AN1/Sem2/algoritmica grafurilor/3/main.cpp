#include <iostream>
#include <fstream>
#include <vector>
#include <list>
#include <algorithm>
using namespace std;


struct muchie
{//datele despre o muchie
	int a, b, c;
};

void citire(vector<muchie> &much, int &n, int &m)
{
	ifstream f("grafpond.in");
	f >> n;
	int x, y, z;
	while (f >> x >> y >> z)
	{
		much.push_back(muchie());
		much.back().a = x;
		much.back().b = y;
		much.back().c = z;
		m++;
	}
	f.close();
}
//functia de comparare pentru sortarea muchiilor
int cmp(muchie i, muchie j) { return i.c < j.c; }
//functie recursiva care returneaza tatal unui nod
int find(int x, vector<pair<int, int>> &tata)
{
	if (tata[x].first == x) return x;
	else return find(tata[x].first, tata);
}
//uneste tatii a doi arbori partiali
void uni(int x, int y, vector<pair<int,int>> &tata)
{
	if (tata[x].second > tata[y].second)
		tata[y].first = x;
	else if (tata[x].second < tata[y].second)
		tata[x].first = y;
	else
	{
		tata[y].first = x;
		tata[x].second++;
	}
}
//algoritmul lui Kruskal
int APM(vector<muchie> &apm, int n, int m, vector<muchie> much, vector<muchie> &nemuch, vector<list<pair<int, int>>> &listad)
{
	//sortam muchiile
	sort(much.begin(), much.end(), cmp);
	int s = 0, k = 0, i = 0, j;
	//vector de tati
	vector<pair<int,int>> tata(n + 1);
	//prima oara fiecare nod e initializat cu el insusi, adica
	//fiecare e radacina lui
	for (j = 1; j <= n; j++) tata[j].first = j;
	//de i ori (ca sa salvam si muchiile nefolosite)
	while (i < m)
	{
		//r1 radacina primei extremitati iar r2 rad celei de a doua
		int r1 = find(much[i].a, tata);
		int r2 = find(much[i].b, tata);
		//daca fac parte din arbori diferiti si k<n-1
		if (r1 != r2&&k < n - 1)
		{
			//adaugam muchia la APM
			apm.push_back(muchie());
			apm.back().a = much[i].a;
			apm.back().b = much[i].b;
			apm.back().c = much[i].c;
			//punem muchia si in list ade adiacenta (pentru SAPM)
			listad[much[i].a].push_back(make_pair(much[i].b, much[i].c));
			listad[much[i].b].push_back(make_pair(much[i].a, much[i].c));
			//crestem suma
			s = s + much[i].c;
			//crestem nr. de muchii alese
			k++;
			//unim cei doi arbori partiali
			uni(r1, r2, tata);
		}
		//altfel, e muchie care poate fi folosita in SAPM si o punem in vector
		else
		{
			nemuch.push_back(muchie());
			nemuch.back().a = much[i].a;
			nemuch.back().b = much[i].b;
			nemuch.back().c = much[i].c;
		}
		//trecem la muchia urmatoare
		i++;
	}
	return s;
}

//un DFS care creeaza vector de tati cu radacina in nodul 1
void arb(int i, vector<list<pair<int, int>>> listad, vector<pair<int, int>> &tata)
{
	static vector<int> viz(listad.size() + 1);
	//for (auto i : viz) cout << i << " "; cout << endl;
	viz[i] = 1;
	for (auto j : listad[i])
	{
		if (viz[j.first] == 0)
		{
			tata[j.first].first = i;
			tata[j.first].second = j.second;
			arb(j.first, listad, tata);
		}
	}
}

//functie care parcurge tatii de la nodul a pana la radacina si noteaza fiecare nod prin care treze
//cu 1 in vectorul vizi si in vectorul d se salveaza maximul gasit la fiecare pas
//apoi de la b plecam in sus pana dam de primul nod cu vizi 1 (gasit de a) si asta inseamna ca s-a
//incheiat ciclul si se calculeaza maximul dintre cele 2 ramuri parcurse
void caut(int a, int b, vector<list<pair<int, int>>> listad, vector<muchie> d, vector<int> vizi, muchie &max, vector<pair<int, int>> tata)
{
	vizi[a] = 1;
	//d[a].c = 1;
	muchie maxx = { 0,0,0 };
	while (tata[a].first != 0)
	{
		vizi[tata[a].first] = 1;
		if (tata[a].second > max.c)
		{
			max.c = tata[a].second;
			max.a = a;
			max.b = tata[a].first;
		}
		d[tata[a].first].c = max.c;
		d[tata[a].first].a = a;
		d[tata[a].first].b = tata[a].first;
		a = tata[a].first;
	}
	while (vizi[b] == 0)
	{
		if (tata[b].second > maxx.c)
		{
			maxx.c = tata[b].second;
			maxx.a = b;
			maxx.b = tata[b].first;
		}
		b = tata[b].first;
	}
	if (d[b].c < maxx.c) max = maxx;
}

//functie care parcurge muchiile nepuse in APM si pentru fiecare cauta maximul din ciclul format prin
//unirea celor doua capete. Din costul muchiei nefolosite se scade acest maxim si rezutatul se compara
//cu un minim. La starsit in minim se va afla muchia care ar aduce cea mai mica schimbare APM-ului
//iar in maxi se va afla muchia care trebuie scoasa
void SAPM(vector<list<pair<int, int>>> listad, vector<muchie> nemuch, muchie &min, muchie &maxi, int n)
{
	int i, k = nemuch.size(), m, mini = INT_MAX;
	muchie max;
	vector<pair<int,int>> tata(n + 1);
	//cream vectorul de tati
	arb(1, listad, tata);
	i = 0;
	while (i < k)
	{
		max.a = max.b = max.c = 0;
		vector<muchie> d(n + 1);
		vector<int> vizi(n + 1);
		caut(nemuch[i].a, nemuch[i].b, listad, d, vizi, max, tata);
		m = nemuch[i].c - max.c;
		if (m < mini)
		{
			mini = m;
			min.c = nemuch[i].c;
			min.a = nemuch[i].a;
			min.b = nemuch[i].b;
			maxi.c = max.c;
			maxi.a = max.a;
			maxi.b = max.b;
		}
		i++;
	}
}
int main()
{
	vector<muchie> much;
	int n, m = 0;
	citire(much, n, m);
	vector<muchie> apm;
	vector<list<pair<int, int>>> listad(n + 1);
	vector<muchie> nemuch;
	int s = APM(apm, n, m, much, nemuch, listad);
	cout << "Suma APM: " << s << endl << "APM: ";
	for (auto i : apm)
		cout << i.a << "-" << i.b << "-" << i.c << " ";
	cout << endl << endl << "Lista de adiacenta:" << endl;
	for (int i = 1; i <= n; i++)
	{
		cout << i << ". ";
		for (pair<int, int> j : listad[i])
			cout << j.first << "-" << j.second << " ";
		cout << endl;
	}
	muchie min, maxi = { 0,0,0 };
	SAPM(listad, nemuch, min, maxi, n);
	s = s - maxi.c; s = s + min.c;
	cout << endl << "Suma SBAPM: " << s << endl << "Second Best APM: ";
	for (auto i : apm)
		if (i.a == maxi.a&&i.b == maxi.b) cout << min.a << "-" << min.b << " ";
		else cout << i.a << "-" << i.b << " ";
		cout << endl << endl;
	//cout << min.a << " " << min.b << " " << min.c << endl;
	//cout << maxi.a << " " << maxi.b << " " << maxi.c << endl;
}
