#include <iostream>
#include <typeinfo>
using namespace std;
//
//class B
//{ protected: static int x;//greseala aici,trebuia sa fie protected pt a fii accesata din D
//int i;
//public: B() { x++; i=1; }//a crescut la 1 aici
//~B() { x--; }
//static int get_x() { return x; }
//int get_i() { return i; }
//};
// int B::x;//default 0
//class D: public B
//{ public: D() { x++; }
//~D() { x--; }
//};
//int f(B *q)
//{ return (q->get_i())+1;
//}
//int main()
//{ B *p=new B;
//cout<<f(p);
//delete p;
//p=new D;
//cout<<f(p);
//delete p;
//cout<<D::get_x();//merge pt ca e static..nu e nevoie de obiect
//return 0;
//}

//class B
//{ int x;
//public: B(int i=17) { x=i; }
//int get_x() { return x; }
//operator int() { return x; } };
//class D: public B
//{ public: D(int i=-16):B(i) {} };
//int main()
//{ D a;
//cout<<27+a;
//return 0;
//}

//
//class cls
//{ static int x;
//public: cls (int i=1) { x=i; }
//cls f(cls a) { return x+a.x; }
//static int g() { return f()/2; } };//nu exista functia f()
//int cls::x=7;
//int main()
//{ cls ob;
//cout<<cls::g();
//return 0;
//}
//
//class cls
//{ int *v,nr;
//public: cls(int i=0) { nr=i; v=new int[i];
//for (int j=0; j<size(); j++) v[j]=3*j; }
//~cls() { delete[] v; }
//int size() { return nr; }
//int& operator[](int i) { return v[i]; }
//cls operator+(cls); };
//cls cls::operator+(cls y)
//{ cls x(size());
//for (int i=0; i<size(); i++) x[i]=v[i]+y[i];
//return x; }
//int main()
//{ cls x(10), y=x, z;//copy constr e implicit..si fara parametrii ia i=0;
//x[3]=y[6]=-15;
//z=x+y;
//for (int i=0; i<x.size(); i++) cout<<z[i]<<' ';//si totusi nu are acces bine la pozitiile 0 si 1
//return 0;
//}
//
////lipsea biblioteca typeinfo
//class B
//{ int i;
//public: B() { i=1; }
//int get_i() { return i; }
//};
//class D: public B
//{ int j;
//public: D() { j=2; }
//int get_j() {return j; }
//};
//int main()
//{ B *p;
//int x=0;
//if (x) p=new B;
//else p=new D;
//if (typeid(p).name()=="D*") cout<<((D*)p)->get_j();//undefined behaviour
//return 0;
//}
//
//class cls
//{ int x;
//public:cls(){}//constr fara param
//     cls(int i) { x=i; }
//int set_x(int i) { int y=x; x=i; return y; }
//int get_x(){ return x; } };
//int main()
//{ cls *p=new cls[10];
//int i=0;
//for(;i<10;i++) p[i].set_x(i);
//for(i=0;i<10;i++) cout<<p[i].get_x();//nu exista get_x de i
//return 0;
//}
//
//template<class T>
//int f(T x, T y)
//{ return x+y;
//}
//int f(int x, int y)
//{ return x-y;
//}
//int main()
//{ int a=5;
//float b=8.6;
//cout<<f(a,b);//-3 converteste la int float-ul..de ce?
//return 0;
//}
