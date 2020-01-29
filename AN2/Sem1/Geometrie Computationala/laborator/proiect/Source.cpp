#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;

ifstream f("date.in");
ofstream g("date.out");
ofstream gg("datein.out");

vector<pair<double, double>> poligon;
int n;
pair<double, double> punct;
struct dreapta {
	pair<double, double> st, dr;
	double panta;
	int ind, inf;
};
//vector cu diagonalele si dreptele suport care pornesc din primul punct
vector<dreapta> muchii;

double testOrientare(pair<double, double> A, pair<double, double> B, pair<double, double> C) {
	return B.first*C.second + A.first*B.second + C.first*A.second
		- B.first*A.second - C.first*B.second - A.first*C.second;
}
//sortez dupa pante
bool cmp(dreapta a, dreapta b) {
	if (a.panta < b.panta) return 1;
	return 0;
}
//cautare binara dupa panta, caut intre ce diagonale se afla panta punctului meu cu punctul origine
//functia returneaza -1 daca este in afara, altfel returneaza diagonala inferioara
int caut(double pct) {

	if (testOrientare(muchii[0].st,muchii[0].dr,punct)<0) return -1;
	if (testOrientare(muchii[n-2].st,muchii[n-2].dr,punct)>0) return -2;
	int li = 0, ls = n - 2, m;
	do {
		m = (li + ls) / 2;
		if (muchii[m].panta == pct) {
			if (m == n - 2) return m - 1;
			else return m;
		}
		if (pct < muchii[m].panta) ls = m - 1;
		else li = m + 1;
	} while (li <= ls);
	if (muchii[m].panta > pct) return m - 1;
	else return m;
}
//se verifica daca punctul este in interiorul, pe sau in exteriorul triunghiului format de cele 3 diagonale intre care este situat
double test_interior(dreapta a, dreapta b, dreapta c, pair<double, double> pct) {
	pair<double, double> A = a.st, B = c.st, C = b.dr;
	cout << A.first << " " << A.second << endl << B.first << " " << B.second << endl << C.first << " " << C.second << endl;
	double t1 = testOrientare(pct, A, B);
	double t2 = testOrientare(pct, B, C);
	double t3 = testOrientare(pct, C, A);

	g << t1 << " " << t2 << " " << t3 << endl;
	pair<pair<double, double>, pair<double, double>> aa = make_pair(a.st, a.dr), bb = make_pair(b.st, b.dr), mz = make_pair(muchii[0].st, muchii[0].dr), mn = make_pair(muchii[n - 2].st, muchii[n - 2].dr);
	
	if (t2 == 0 || aa == mz || bb == mn) return 2;
	else if (t1 == 0 || t2 == 0 || t3 == 0) return 1;
	else if ((t1 < 0 && t2 < 0 && t3 < 0) || (t1 > 0 && t2 > 0 && t3 > 0)) return 1;
	else return 0;
	return t1;
}

int main() {
	int ok = 1, num, indpct;
	double x, y; f >> x >> y;
	gg << x << " " << y << endl;
	punct = make_pair(x, y);
	double xmin = INT_MAX, ymax = INT_MIN;
	f >> n; gg << n << endl;
	for (int i = 0; i < n; i++)
	{
		f >> x >> y;
		//calculez cel mai din stanga sus punct ca sa am pantele de la stanga la dreapta
		if (x < xmin) {
			xmin = x;
			ymax = y;
			indpct = i;
		}
		else if (x == xmin) {
			if (y > ymax)
			{
				ymax = y;
				indpct = i;
			}
		}
		poligon.push_back(make_pair(x, y));
	}
	//daca cel mai din stanga sus nu e primul punct, mut tot ce e inaintea lui la final, si apoi inversez ca poligonul sa se construiasca de la dreapta spre stanga.
	for (int i = 0; i < indpct; i++) {
		poligon.push_back(poligon[i]);
	}
	poligon.erase(poligon.begin(), poligon.begin() + indpct);
	if (poligon[0].second < poligon[1].second)
		reverse(poligon.begin() + 1, poligon.end());

	for (int i = 0; i < poligon.size(); i++) { gg << poligon[i].first << " " << poligon[i].second << endl; 
	//daca punctul este unul din poligon, afisez direct ca este pe frontiera
	if (punct.first == poligon[i].first && punct.second == poligon[i].second) {
	cout << "Punctul este pe frontiera!" << endl; ok = 0;
	num = i+1;
			}
	}

	if (ok) {
		//iau primul punct ca punct origine
		pair<double, double> p1 = poligon[0];
		//pun in vectorul muchii toate diagonalele cu pentele lor (inclusiv dreptele suport)
		for (int i = 1; i < n; i++) {
			dreapta p;
			p.st = p1; p.dr = poligon[i];
			if (poligon[i].first - p1.first == 0) { p.panta = (double)(poligon[i].second - p1.second) / (poligon[i].first + 0.01 - p1.first); p.inf = 1; }
			else {
				p.panta = (double)(poligon[i].second - p1.second) / (poligon[i].first - p1.first);
				p.inf = 0;
			}
			p.ind = i + 1;
			muchii.push_back(p);
		}
		sort(muchii.begin(), muchii.end(), cmp);

		for (auto i : muchii) {
			cout << i.panta << " ";
			if(i.inf==0) g << i.panta << "_" << i.ind << " ";
			else g << "-inf_" << i.ind << " ";
		}
		g << endl;
		cout << endl;
		//creez panta punctului cautat cu originea
		dreapta pct; pct.st = p1; pct.dr = punct;
		if (punct.first - p1.first == 0) {
			pct.panta = (double)(punct.second - p1.second) / (punct.first+0.01 - p1.first);
		}
		else {
			pct.panta = (double)(punct.second - p1.second) / (punct.first - p1.first);
		}
		
		
		
		g << pct.panta << endl;
		//caut binar
		int ind = caut(pct.panta);
		//-1 se afla in dreapta -2 in stanga
		if (ind == -1) g << ind << endl;
		else if (ind == -2) g << ind << endl;
		else g << ind+1 << endl;
		if (ind < 0) { cout << "Punctul se afla in afara poligonului!" << endl; cin.get(); return 0; }
		//imi pregatesc triunghiul
		dreapta inf, sup, inchidere;
		
		inf = muchii[ind];
		cout << muchii.size();
		sup = muchii[ind + 1];
		inchidere.st = inf.dr; inchidere.dr = sup.dr; inchidere.panta = 0;
		cout << inchidere.st.first << " " << inchidere.st.second << endl;
		double test = test_interior(inf, sup, inchidere, punct);
		g << test << endl;
		if (test == 1) cout << "Punctul este in interior!" << endl;
		else if (test == 2) cout << "Punctul este pe frontiera!" << endl;
		else cout << "Punctul este in exterior!";
	}
	else g << "nu" << " " << num;
	f.close();
	g.close();
	cin.get();
	return 0;
}