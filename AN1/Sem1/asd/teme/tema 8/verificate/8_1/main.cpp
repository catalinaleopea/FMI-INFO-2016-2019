/**Să se implementeze un arbore binar de căutare echilibrat AVL cu următoarele operații
(cu echilibrare după fiecare operaţie, acolo unde este necesar):
(a) adauga (t, x) - insereaza cheia x în arborele de rădăcină t;
(b) cauta(t, x) - întoarce 1 dacă elementul a se afla în arborele de rădăcină t și 0
în caz contrar;
(c) maxim(t) - întoarce elementul maxim din arborele de rădăcină t, fără a-l șterge
din arbore;
(d) sterge(t, x) - șterge în arborele de rădăcină t nodul cu cheia x (păstrând
proprietatea de arbore binar de căutare şi, eventual, echilibrarea);
(e) afisează (t) – afişează cheile din arborele de rădăcină t, în ordine crescătoare.
**/
#include <iostream>
using namespace std;

struct nod{
int key;
int ech;
nod *left, *right;
};
nod* p;

void drumMaxim(nod *p,int &max,int lung)
{
    if (p!=NULL)
    {
        drumMaxim(p->right,max,lung+1);
        if((p->left==NULL)&&(p->right==NULL)&&(max<lung))
            max=lung;
        drumMaxim(p->left,max,lung+1);
    }
}

void factorEchilibru(nod *p)
{
    int hleft=1;int hright=1;
    if(p->left!=NULL)
        drumMaxim(p->left,hleft,1);
    else
        hleft=0;
    if(p->right!=NULL)
        drumMaxim(p->right,hright,1);
    else
        hright=0;
    p->ech=hright-hleft;
}

nod* rotRight(nod *p)
{
    nod *q;
    q=p->left;
    p->left=q->right;
    if(q->right!=NULL)
        p->left=q->right;
    q->right=p;
    factorEchilibru(p);
    factorEchilibru(q);
    return p;
}

nod* rotLeft(nod *p)
{
    nod *q;
    q=p->right;
    p->right=q->left;
    if(q->left!=NULL)
        p->right=q->left;
    q->left=p;
    factorEchilibru(p);
    factorEchilibru(q);
    p=q;
    return p;
}

nod* dRotRight(nod *&p)
{
    p->left=rotLeft(p->left);
    p=rotRight(p);
    return p;
}

nod* dRotLeft(nod *&p)
{
    p->right=rotRight(p->right);
    p=rotLeft(p);
    return p;
}

nod* echilibrare(nod *p)
{
    nod *w;
    factorEchilibru(p);//se calculeaza factorul de echilibru a nodului curent p
    if(p->ech==-2)// daca p nod este critic
    {
        w=p->left; // atunci w este copilul stanga al lui p
        if (w->ech==1)// si daca acesta are factorul de echilibru 1
            p = dRotRight(p);// atunci se face dubla rotatie dreapta
        else//altfel se face o simpla rotatie dreapta
            p = rotRight(p);
    }
    else
        if(p->ech==2)//daca p nod este critic
         {

            w=p->right;//w este copilul dreapta al nodului curent p
            if (w->ech==-1)// si acesta are factorul de ech -1
                p = dRotLeft(p);//se face o dubla rotatie stanga
            else//altfel se face o simpla rotatie stanga
               p = rotLeft(p);
        }
    return p;
}

nod* adauga(nod *p,int x)
{
    if (p==NULL)// daca nodul curent este NULL atunci
    {
        p=new nod; //se aloca spatiu pentru el in zona heap
        p->key=x; //informatia devine x
        p->ech=0; // factorul de echilibru este 0 - nodul este echilibrat
        p->right=NULL;// nodul se insereaza ca nod frunza
        p->left=NULL; //deci referintele catre copii sai sunt NULL
        return p;
    }
    else
    {
        if (x<p->key) //daca cheia care se doreste inserata este
        //mai mica ca valoare decat informatia din nodul curent
            p->left =adauga(p->left,x);// atunci se insereaza
        //in subarborele stang al nodului curent
        else
            if (x>p->key) //altfel daca cheia care se va insera
        //e mai mare decat informatia din nodul curent
                p ->right = adauga(p->right,x); // atunci se va insera
        //in subarborele drept
            else
                cout<<"Nodul exista deja\n";
    }
    p = echilibrare(p);// daca intervin cazuri de dezechilibru
    //se va echilibra subarborele sau chiar arborele
}

nod* sterge(nod *p,int x)
{
    nod *q,*r,*w;
    if (p!=NULL)
    {// daca nodul curent este diferit de NULL
        if (x<p->key) //cheia care se doreste stearsa este mai mica decat informatia din nod
            p->left = sterge(p->left,x); // se cauta cheia de sters in subarborele stang al nodului curent
        else
            if (x>p->key) // daca cheia este mai mare
                p->right = sterge(p->right,x);// se cauta in subarborele drept
        else
        {//daca cheia este egala cu informatia din nodul curent
            q=p;//un nod q devine p
            if (q->right==NULL) // daca copilul drept al lui q eate NULL
                p=q->left;// atunci p devine q->stanga
            else
                if (q->left==NULL) //altfel daca copilul stang al lui q este NULL
                    p=q->right;// p devine q->dreapta
                else
                {
                    w=q->left;//altfel w este copilul stanga al lui q
                    r=q;// r devine q
                    if (w->right!=NULL)// daca copilul drept al lui w nun este NULL
                    {
                        while (w->right!=NULL)
                        {
                            r=w;
                            w=w->right;
                        }
                        p->key=w->key;
                        q=w;
                        r->right=w->left;
                        r=p->left;
                        w=w->left;
                        if (r!=NULL)
                            while ((r!=w)&&(r!=NULL))
                            {
                                r = echilibrare(r);
                                r=r->right;
                            }
                    }
                    else
                    {
                        p->key=w->key;
                        p->left=w->left;
                        q=w;
                    }
                }
            delete(q);// se sterge q
        }
    }
    if (p!=NULL)
        p = echilibrare(p);// se echilibreaza p daca nu este NULL
    return p;
}

bool cauta(nod*p,int x)
{
    if(p==NULL)
        return 0;
    if(p->key==x)
        return 1;
    if(x<p->key)
        cauta(p->left,x);
    else
        cauta(p->right,x);
}

nod* cautaMax(nod*p)
{
    if(p->right!=NULL)
        cautaMax(p->right);
    else
        return p;
}

void afiseaza(nod*p)
{
    if(p==NULL)
        return;
    cout<<p->key<<' ';
    if(p->left)
        afiseaza(p->left);

    if(p->right)
        afiseaza(p->right);
}


int main()
{
    for(int i=1;i<=8;i++)
        p=adauga(p,i);
    //p=adauga(p,4);
    //p=adauga(p,5);
    //p=adauga(p,7);
    //p=adauga(p,2);
    //p=adauga(p,1);
    //p=adauga(p,3);
    //p=adauga(p,6);
    afiseaza(p);
    sterge(p,5);
    cout<<endl;
    afiseaza(p);
    //cout<<endl<<cauta(p,3);
    //cout<<endl<<cauta(p,5);
    //nod *c=cautaMax(p);
    //cout<<endl<<c->key;
    return 0;
}
