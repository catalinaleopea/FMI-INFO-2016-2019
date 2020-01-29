#include <iostream>
#include <fstream>
#include <vector>
#include <list>

using namespace std;

class Flux
{
	int n, m, fl;
	vector<list<int>> listtad;
	vector<list<int>> listad;
	vector<list<int>> adjlist;
	vector<vector<pair<int, int>>> mat;
	vector<int> st, dr;
	list<int> path;
	vector<pair<int, int>> tai;
	vector<list<int>> path_list;
	vector<int> tata, viz, coada;
	int BFS();
public:
	Flux() { n = m = fl = 0; }
	void citire();
	void afisare();
	void bipartitie(int);
	void set_Flux();
	void afisare_mat();
	void get_Flux();
	void af_Flux();
};


void Flux::citire()
{
	ifstream f("date.in");
	f >> n >> m;
	listad.resize(n + 2);
	listtad.resize(n + 2);
	adjlist.resize(n + 2);
	mat.resize(n + 2);
	for (int i = 0; i <= n+1; i++)
		mat[i].resize(n + 2);
	int a, b;
	for (int i = 0; i < m; i++)
	{
		f >> a >> b;
		listad[a].push_back(b);
		listad[b].push_back(a);
		listtad[a].push_back(b);
		adjlist[b].push_back(a);
	}
}

void Flux::afisare()
{
	for (int i = 1; i <= n; i++)
	{
		cout << i << ". ";
		for (auto j : listad[i]) cout << j << " ";
		cout << endl;
	}
	cout << endl;
}

void Flux::bipartitie(int nod)
{
	for (auto i : listad[nod])
	{
	    if (viz[i] == 0)
		{
			if (viz[nod] == 1) { viz[i] = 2; dr.push_back(i); }
			else { viz[i] = 1; st.push_back(i); }
			bipartitie(i);
		}
	}
}

void Flux::set_Flux()
{
	viz.assign(n + 2, 0);
	viz[1] = 1; st.push_back(1);
	bipartitie(1);
	for (auto i : st)
	{
		mat[0][i].first = 1;
		mat[i][0].second = -1;
		listtad[0].push_back(i);
		adjlist[i].push_back(0);
		for (auto j : listad[i])
		{
			mat[i][j].first = 1;
			mat[j][i].second = -1;
		}
	}
	for (auto i : dr)
	{
		mat[i][n + 1].first = 1;
		mat[n + 1][i].second = -1;
		adjlist[n + 1].push_back(i);
		listtad[i].push_back(n + 1);
	}
}

void Flux::afisare_mat()
{
	cout << endl;
	cout << "Bipartitie stanga: "; for (auto i : st) cout << i << " "; cout << endl;
	cout << "Bipartitie dreapta: "; for (auto i : dr) cout << i << " "; cout << endl;
	for (int i = 0; i <= n + 1; i++)
	{
		cout << i << ". ";
		for (int j = 0; j <= n + 1; j++) cout << mat[i][j].first << "-" << mat[i][j].second << " ";
		cout << endl;
	}
	cout << endl;
}

int Flux::BFS()
{
	viz.assign(n + 2, 0);
	tata.assign(n + 2, 0);
	coada.clear();
	int li, ls; li = ls = 0;
	coada.push_back(0);
	viz[0] = 1;
	int pathh = 0;
	while (li <= ls)
	{
		int x = coada[li];
		for (auto i : listtad[x])
		{
			if (viz[i] == 0)
				if ((mat[x][i].first - mat[x][i].second) != 0)
				{
					viz[i] = 1;
					tata[i] = x;
					coada.push_back(i);
					ls++;
					if (i == n + 1)
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
					if (i == n + 1)
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
		int v = n + 1;
		while (v != 0)
		{
			path.push_back(v);
			int a;
			if (mat[tata[v]][v].second == -1) a = 0;
			else a = mat[tata[v]][v].second;
			if (min > (mat[tata[v]][v].first - a)) min = mat[tata[v]][v].first - a;
			v = tata[v];
		}
		path.push_back(0);
		path.reverse();
		list<int> *p = new list<int>; *p = path;
		path_list.push_back(*p);
		fl += min;
		v = n + 1;
		while (v != 0)
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
	}
}

void Flux::af_Flux()
{
	for (int i = 1; i <= n; i++)
	{
		for (int j = 1; j <= n; j++)
			if (mat[i][j].first != 0 && mat[i][j].second != -1)
				if (mat[i][j].second != 0) cout << i << " " << j << endl;
	}

}

int main()
{
	Flux ob1;
	ob1.citire();
	ob1.afisare();
	ob1.set_Flux();
	ob1.get_Flux();
	ob1.af_Flux();
	return 0;
}
