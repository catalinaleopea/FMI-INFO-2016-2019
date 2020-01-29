#include <iostream>
#include <fstream>
#include <vector>
#include <list>

using namespace std;

class Flux
{
	int n, m, s, t, ok, fl, cap_tai;
	vector< list < int > > listad;
	vector< list < int > > adjlist;
	vector< vector < pair < int, int > > > mat;
	vector< pair < int, int > > conserv;
	list <int> path;
	vector < pair < int, int > > tai;
	vector < list < int > > path_list;
	vector < int > tata, viz, coada;
	int BFS();
public:
	Flux() { n = m = s = t = ok = fl = cap_tai = 0; }
	void citire();
	void afisare();
	void afisare_mat();
	void corect();
	void get_Flux();
	void get_max_Flux();
	void taietura();
};


void Flux::citire()
{
	ifstream f("date.in");
	f >> n >> s >> t >> m;
	listad.resize(n + 1);
	adjlist.resize(n + 1);
	conserv.resize(n + 1);
	mat.resize(n + 1);
	for (int i = 0; i <= n; i++)
		mat[i].resize(n + 1);
	int a, b, c, d;
	for (int i = 0; i < m; i++)
	{
		f >> a >> b >> c >> d;
		if (d<0 || d>c) ok = 1;
		if (a != s)  conserv[a].second = conserv[a].second + d;
		if (b != t) conserv[b].first = conserv[b].first + d;
		listad[a].push_back(b);
		adjlist[b].push_back(a);
		mat[a][b] = make_pair(c, d);
		mat[b][a] = make_pair(d, -1);
	}
}

void Flux::afisare()
{
	cout << endl << "Start: " << s << endl << "Sfarsit: " << t << endl;
	for (int i = 1; i <= n; i++)
	{
		cout << i << ". ";
		for (auto j : listad[i]) cout << j << " ";
		cout << endl;
	}
	cout << endl;
}

void Flux::afisare_mat()
{
	cout << endl;
	for (int i = 1; i <= n; i++)
	{
		cout << i << ". ";
		for (int j = 1; j <= n; j++) cout << mat[i][j].first << "-" << mat[i][j].second << " ";
		cout << endl;
	}
	cout << endl;
}

void Flux::corect()
{
	if (ok) cout << "Fluxul nu este marginit corect" << endl;
	int ok2 = 1;
	for (int i = 1; i <= n; i++) if (i != s && i != t) if (conserv[i].first != conserv[i].second) ok2 = 0;
	if (ok2 == 0) { cout << "Fluxul nu este conservat corect" << endl; ok = 1; }
}

int Flux::BFS()
{
	viz.assign(n + 1, 0);
	tata.assign(n + 1, 0);
	coada.clear();
	int li, ls; li = ls = 0;
	coada.push_back(s);
	viz[s] = 1;
	int pathh = 0;
	while (li <= ls)
	{
		int x = coada[li];
		for (auto i : listad[x])
		{
			if (viz[i] == 0)
				if ((mat[x][i].first - mat[x][i].second) != 0)
				{
					viz[i] = 1;
					tata[i] = x;
					coada.push_back(i);
					ls++;
					if (i == t)
					{
						pathh = 1;
						break;
					}
				}
		}
		for (auto i : adjlist[x])
		{
			if (viz[i] == 0)
				if (mat[x][i].first != 0)
				{
					viz[i] = 1;
					tata[i] = x;
					coada.push_back(i);
					ls++;
					if (i == t)
					{
						pathh = 1;
						break;
					}
				}
		}
		li++;
	}
	return pathh;
}

void Flux::get_Flux()
{
	while (BFS())
	{
		path.clear();
		int min = INT_MAX;
		int v = t;
		while (v != s)
		{
			path.push_back(v);
			int a;
			if (mat[tata[v]][v].second == -1) a = 0;
			else a = mat[tata[v]][v].second;
			if (min > (mat[tata[v]][v].first - a)) min = mat[tata[v]][v].first - a;
			v = tata[v];
		}
		path.push_back(s);
		path.reverse();
		list<int> *p = new list<int>; *p = path;
		path_list.push_back(*p);
		v = t;
		while (v != s)
		{
			if (mat[tata[v]][v].second != -1)
			{
				mat[tata[v]][v].second += min;
				mat[v][tata[v]].first += min;
			}
			else
			{
				mat[tata[v]][v].first -= min;
				mat[v][tata[v]].second -= min;
			}
			v = tata[v];
		}
		cout << "Path cu minimul " << min << ": ";
		for (auto i : path) cout << i << " "; cout << endl;
	}
}

void Flux::get_max_Flux()
{
	for (auto i : listad[s])
		fl += mat[s][i].second;
	cout << "Flux Maxim: " << fl << endl;
}

void Flux::taietura()
{
	for (auto i : coada)
	{
		for (auto j : listad[i])
		{
			if (viz[j] == 0)
			{
				tai.push_back(make_pair(i, j));
				cap_tai += mat[i][j].second;
			}
		}
	}
	for (int i = 1; i <= n; i++)
	{
		for (int j = 1; j <= n; j++)
			if (mat[i][j].first != 0 && mat[i][j].second != -1)
				cout << i << " " << j << " " << mat[i][j].second << endl;
	}
	cout << endl << "Capacitatea taieturii: " << cap_tai;
	cout << endl << "Taietura minima: " << endl;
	for (auto i : tai) cout << i.first << " " << i.second << endl;
}


int main()
{
	Flux ob1;
	ob1.citire();
	ob1.afisare();
	ob1.corect();
	ob1.get_Flux();
	ob1.get_max_Flux();
	ob1.taietura();
	return 0;
}
