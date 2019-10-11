#include<bits/stdc++.h>
using namespace std;
/* * * * * * * * * * * * * * * * * * * 
 * This file includes what I think   *
 * will be useful in online contests *
 *                 * * * * * * * * * *
 * Algos & DS:     * 
 * 01- merge sort  * * * * * * * * * * * * * * * *
 * 02- left leaning red black binary search tree *
 * 03- AVL binary search tree  * * * * * * * * * * 
 * 04- binary indexed tree * * *
 * 
 * * * * * * * * * * * * * * * * * * */

typedef vector<int> veci;
typedef long long lol;
const int m = 1e9+7;

/*/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\**
**\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/*/  

void mergesort(veci &vec, int s, int e) // e = size -1
{
    static veci temp(vec);

    int I = e-s;

    if (e==s) return;
    int m = I>>1;
    
    mergesort(vec, s,s+m);
    mergesort(vec, s+m+1,e);

    int i=s,
        j=s+m+1,
        k=0;

    while(i<=(s+m)||j<=e)
    {
        (vec[i]<vec[j])?
            (i<=(s+m))?
                temp[k++]=vec[i++]:
                temp[k++]=vec[j++]:
            (j<=e)?
                temp[k++]=vec[j++]:
                temp[k++]=vec[i++];
    }

    for (int i = 0; i < k; i++)
        vec[s+i]=temp[i];

    return;
}

/*/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\**
**\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/*/

// TO DO
struct llrbBST //left leaning red black binary search tree
{
    
    struct node // for llrbBST usage
    { int data; node *L=NULL,*R=NULL; bool red=1; node(int datum):data(datum){} }; 
    /*
    * null links are black by default
    * and stored in child refering to
    * perants 
    * */
    node *H=NULL; // tree head
    
    // node p: perent, c: child
    node* rotL(node *p) // rotate left
    { node *c = p->R; p->R = c->L; c->L = p; c->red = p->red; p->red = 1; if(p==H) H=c; return c; }
    node* rotR(node *p) // rotate right
    { node *c = p->L; p->L = c->R; c->R = p; c->red = p->red; p->red = 1; if(p==H) H=c; return c; }

    void flip(node *p) // flip colors
    { (p==H)? p->red = 0: p->red = 1; p->L->red = 0/*!p->L->red*/; p->R->red = 0/*!p->L->red*/; }
    void fflip(node *p) // full flip colors
    { p->red = !p->red ; p->L->red = !p->L->red; p->R->red = !p->R->red; }
    
    bool isRed(node* n)
    { if(n==NULL) return false; else return n->red; }
        
    /* insert new nodes */
    node* put(node *N, int data)
    {
        if(N==NULL)
        {
            node *t = new node(data);
            if(H==NULL) H=t,H->red=0;
            return t;
        } 

             if(data < N->data) N->L = put(N->L,data);
        else if(data > N->data) N->R = put(N->R,data);
        else N->data = data;

        if(isRed(N->R) && !isRed(N->L))     N = rotL(N);
        if(isRed(N->L) &&  isRed(N->L->L))  N = rotR(N);
        if(isRed(N->L) &&  isRed(N->R))     flip(N);

        return N;
    }


    node* red2L(node* N)
    {
        fflip(N);
        if(isRed(N->R->L))
        {
            N->R = rotR(N->R);
            N = rotL(N);
            fflip(N);
        }
        return N;
    }
    node* red2R(node* N)
    {
        fflip(N);
        if(isRed(N->L->L))
        {
            N = rotR(N);
            fflip(N);
        }
        return N;
    }

    node* del(node *N, int data)
    {
        if(data < N->data)
        {
            if(!isRed(N->L) && !isRed(N->L->L))
                N = red2L(N);
            N->L = del(N->L, data); 
        }
        else
        {
            if(isRed(N->L)) N = rotR(N);
            N->L = del(N->L, data);

        }
        
    }
    
    void display(node* N)
    { if(N!=NULL) { char c = char(N->data); printf("%c ", c); display(N->L); display(N->R); } return; }

};

/*/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\**
**\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/*/

struct avlBST
{   
    struct node 
    { int d; node*l=NULL,*r=NULL; int h=1; 
    node(int datum):d(datum){} }; 
    int H(node *N) // height
    { if (N == NULL) return 0; return N->h; } 
    int BF (node *N) // balance factor 
    { if (N == NULL) return 0; return H(N->l)-H(N->r); } 

    node* root=NULL;

    node *RR(node *p) // Rotate Right
    {   // ROTATE
        node *c = p->l; p->l = c->r; c->r = p; 
        // Update H 
        p->h = max(H(p->l), H(p->r)) +1; 
        c->h = max(H(c->l), H(c->r)) +1; 
        // Return New Perent 
        return c; 
    } 
        
    node *RL(node *p) 
    {   // Rotate
        node *c = p->r; p->r = c->l; c->l = p;
        // Update H 
        p->h = max(H(p->l),	H(p->r)) +1; 
        c->h = max(H(c->l), H(c->r)) +1;
        // Return New Perent 
        return c; 
    } 

    node* makeBalance(node *N, int B, int d)
    {
        if ( B>1 && d < N->l->d) return RR(N);  // Left Left Case 
        if ( B>1 && d > N->l->d) 
        { N->l = RL(N->l); return RR(N); }      // Left Right Case

        if ( B<-1 && d > N->r->d) return RL(N); // Right Right Case 
        if ( B<-1 && d < N->r->d) 
        { N->r = RR(N->r); return RL(N); }      // Right Left Case 

        return N; // no change
    }

    node* insert(node* N, int d) 
    { 
        // insertion part 
        if (N == NULL) { N = new node(d); return N; } 
        
            if (d < N->d) N->l = insert(N->l, d); 
        else if (d > N->d) N->r = insert(N->r, d); 
        else return N; 

        // updating ancestor height
        N->h = max(H(N->l), H(N->r)) +1; 
        // check the balance 
        return makeBalance(N,BF(N),d);    
    } 

    node* remove(node* N, int d)  
    {  
        
        if (N == NULL)  return N;  
    
             if ( d < N->d ) N->l = remove(N->l, d);  // search left
        else if ( d > N->d ) N->r = remove(N->r, d);  // search right
        else
        {  
            if((N->l==NULL)||(N->r==NULL))  //one child or no child  
            {  
                node *temp = N->l? N->l: N->r;
                // if no child case else one child
                if(temp ==NULL) N = NULL; else *N =*temp; 
                free(temp);
            }  
            else // two children
            {  
                // get smallest in right subtree
                node* temp = N->r;  
                while (temp->l != NULL)  
                    temp = temp->l;  
                // copy data to ancestor 
                N->d = temp->d;  
                // delete the smallest
                N->r = remove(N->r, temp->d);  
            }  
        }  
    
        // If the tree had only one node 
        // then return  
        if (N == NULL)  
        return N;  
    
        // updating ancestor height
        N->h = max(H(N->l), H(N->r)) +1;  
        // check the balance 
        return makeBalance(N,BF(N),d);
    }  

    void display(node *root) 
    { 
        if(root != NULL) 
        { 
            cout << root->d << " "; 
            display(root->l); 
            display(root->r); 
        } 
    } 
};

/*/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\**
**\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/*/

struct BITree
{
    int N;
    lol K;
    vector<int> BIT;
    vector<lol> FAC; //factorial

    BITree(int n)
    {
        N=n;
        K=1;
        FAC.resize(n);
        BIT.resize(n,0);
        build();
    }

    void build()
    {
        for (int i = 1; i <= N; i++)
        {
            add(i,1); 
            K=K*i%m; 
            FAC[i-1]=K;
        }
    }

    int get(int ix) //get prefix sum (the new index of the number)
    {   
        ix--;
        int ret = 0;
        for ( ; ix > -1 ; ix = ( ix & (ix+1) ) -1 )
            ret += BIT[ix];
        
        return ret;
    }
    
    void add(int ix, int dv=-1) // index, value added (delta) map the number system 
    {
        ix--;
        for (; ix<N; ix=ix|(ix+1))
            BIT[ix]+=dv;
    }
};

// TESTING HERE

int main(){
 

    /*AVL TEST*/
    avlBST avl;
    avl.root = avl.insert(avl.root, 1); 
	avl.root = avl.insert(avl.root, 2); 
	avl.root = avl.insert(avl.root, 3); 
	avl.root = avl.insert(avl.root, 4); 
	avl.root = avl.insert(avl.root, 5); 
	avl.root = avl.insert(avl.root, 6);
    avl.root = avl.insert(avl.root, 7); 
    avl.root = avl.insert(avl.root, 8); 
    avl.root = avl.insert(avl.root, 9); 
    avl.root = avl.insert(avl.root,10); 
	avl.root = avl.remove(avl.root, 8);
    avl.display(avl.root);
    /* llrbBST test
    llrbBST t;
    t.put(t.H,'S');
    t.put(t.H,'E');
    t.put(t.H,'A');
    t.put(t.H,'R');
    t.put(t.H,'C');
    t.put(t.H,'H');
    t.put(t.H,'X');
    t.put(t.H,'M');
    t.put(t.H,'P');
    t.put(t.H,'L');
    t.display(t.H);
    //t.deleteRec(t.H,'M');
    //t.display(t.H);
    //M E C A L H R P X S 
    //*/

    /* merge sort test
    veci v = {1,3,6,9,4,6,8,9};
    mergesort(v,0,v.size()-1);
     for(int i:v)
        cout<<i<<' ';
    return 0;
    */
}