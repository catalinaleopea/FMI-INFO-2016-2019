#include <iostream>
using namespace std;
struct node
{
    int key;
    unsigned char height;
    node* left;
    node* right;
    //node(int k) { key = k; left = right = 0; height = 1; }
};
node *p;
unsigned char height(node* p)
{
    return p?p->height:0;
}

int bfactor(node* p)
{
    return height(p->right)-height(p->left);
}

void fixheight(node* p)
{
    unsigned char hl = height(p->left);
    unsigned char hr = height(p->right);
    p->height = (hl>hr?hl:hr)+1;
}

node* rotateright(node* p)
{
    node* q = p->left;
    p->left = q->right;
    q->right = p;
    fixheight(p);
    fixheight(q);
    return q;
}

node* rotateleft(node* q)
{
    node* p = q->right;
    q->right = p->left;
    p->left = q;
    fixheight(q);
    fixheight(p);
    return p;
}

node* balance(node* p) // balancing the p node
{
    fixheight(p);
    if( bfactor(p)==2 )
    {
        if( bfactor(p->right) < 0 )
            p->right = rotateright(p->right);
        return rotateleft(p);
    }
    if( bfactor(p)==-2 )
    {
        if( bfactor(p->left) > 0  )
            p->left = rotateleft(p->left);
        return rotateright(p);
    }
    return p; // balancing is not required
}

node* insert(node* &p, int k) // insert k key in a tree with p root
{
    if( p==NULL ){ p=new node;
    p->key=k;
    p->height=0;
    p->left=p->right=NULL;
    return p;}

    if( k<p->key )
        p->left = insert(p->left,k);
    else
        p->right = insert(p->right,k);
    return balance(p);
}

node* findmin(node* p) // find a node with minimal key in a p tree
{
    /*if(p->left!=NULL)
        findmin(p->left);
    else
        return p;*/
   return p->left?findmin(p->left):p;
}

node* removemin(node* p) // deleting a node with minimal key from a p tree
{
    if( p->left==0 )
        return p->right;
    p->left = removemin(p->left);
    return balance(p);
}

node* remove(node* p, int k) // deleting k key from p tree
{
    if( !p ) return 0;
    if( k < p->key )
        p->left = remove(p->left,k);
    else if( k > p->key )
        p->right = remove(p->right,k);
    else //  k == p->key
    {
        node* q = p->left;
        node* r = p->right;
        delete p;
        if( !r ) return q;
        node* min=findmin(p);
        min->right = removemin(p);
        min->left = q;
        return balance(min);
    }
    return balance(p);
}

void afiseaza(node *&p)
{
    if(p==NULL)
        return;
    afiseaza(p->left);
    cout<<p->key<<' ';
    afiseaza(p->right);
}

int main()
{

    insert(p,4);
    insert(p,5);
    insert(p,7);
    insert(p,2);
    insert(p,1);
    insert(p,3);
    insert(p,6);
    afiseaza(p);
    remove(p,1);
    cout<<'\n';
    afiseaza(p);
    remove(p,5);
    cout<<'\n';
    afiseaza(p);
}
