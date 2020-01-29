#include <iostream>
using namespace std;
//
//class cls1
//{
//    int x;
//public:
//    cls1()
//    {
//        x=13;
//    }
//    int g()
//    {
//        static int i;
//        i++;
//        return (i+x);
//    }
//};//static i=0;i=1;returneaza 14
//class cls2
//{
//    int x;
//public:
//    cls2()
//    {
//        x=27;
//    }
//    cls1& f()
//    {
//        static cls1 ob;
//        return ob;
//    }
//};//ob temporar,pt a apela g
//int main()
//{
//    cls2 ob;
//    cout<<ob.f().g();//14
//    return 0;
//}

//class cls1
//{ protected: int x;
//public: cls1(int i=10) { x=i; }
//int get_x() { return x;} };
//class cls2: cls1
//{ public: cls2(int i):cls1(i) {} };
//int main()
//{ cls d(37);//nu exista clasa cls..cu cls1 merge,cls2 e inacc
//cout<<d.get_x();
//return 0;
//}

//class cls
//{ int x;
//public: cls(int y) {x=y; }
//int operator*(cls b){return (x*b.x); } };//prea multe argumente
//int main()
//{ cls m(100),n(15);
//cout<<m*n;
//return 0;
//}
//
//class B1 { public: int x; };
//class B2 { int y; };
//class B3 { public: int z; };
//class B4 { public: int t; };
//class D: private B1, protected B2, public B3, B4
//{ int u; };
//int main()
//{ D d;
//cout<<d.u;//privat
//cout<<d.x;//inacc
//cout<<d.y;//privat
//cout<<d.z;
//cout<<d.t;//inacc
//return 0;
//}

//class cls
//{ int vi;
//public: cls(int v=37) { vi=v; }
//friend int& f(cls); };
//int& f(cls c) { return c.vi; }//e acc
//int main()
//{ const cls d(15);
//f(d)=8;//fara sens,dar nu e eroare
//cout<<f(d);//deci 15
//return 0;
//}

//class cls1
//{ public: int x;
//cls1(int i=20) { x=i; } };
//class cls2
//{ public: int y;
//cls2(int i=30) { y=i; }
//operator cls1() { cls1 ob; ob.x=y; return ob; } };
//cls1 f(cls1 ob)
//{ ob.x++;//nu modifica x
//return ob;
//}
//int main()
//{ cls1 ob1; f(ob1); cout<<ob1.x;
//cls2 ob2; f(ob2); cout<<ob2.y;//20 30
//return 0;
//}

//class cls
//{ int x;
//public: cls(int i=25) { x=i; }
//int f(); };
//int cls::f() { return x; }
//int main()
//{ const cls d(15);
//cout<<d.f();//const si this din fct f() nu merg
//return 0;
//}
//class cls
//{
//public:
//    int x;
//    cls(int i=0)
//    {
//        x=i;
//    }
//    ~cls(){cout<<"des";} de 3 ori
//};
//cls f(cls c)
//{
//    c.x++;
//    return c;
//}
//int main()
//{
//    cls r(10);
//    cls s=f(r);
//    return 0;
//}
//template <class tip>
//tip dif(tip x, tip y)
//{ return x-y;
//}
//unsigned dif(unsigned x, unsigned y)
//{ return x>=y?x-y:y-x;
//}
//int main()
//{ unsigned i=7,j=8;
//cout<<dif(i,j); 1
//return 0;
//}
