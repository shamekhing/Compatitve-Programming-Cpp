#include<bits/stdc++.h>
using namespace std;
/* * * * * * * * * * * * * * * * * * * 
 * This file includes what I think   *
 * will be useful in online contests *
 *                 * * * * * * * * * *
 * Algos & DS:     * 
 * 01- merge sort  * * * * * * * * * * * * * * * *
 * 02- left leaning red black binary search tree *
 * 03- 
 * 
 * * * * * * * * * * * * * * * * * * */

typedef vector<int> veci;

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
    { 
        int data; node *L=NULL,*R=NULL; bool red=1; 
        node(int datum):data(datum){}
    }; 
    /*
    * null links are black by default
    * and stored in child refering to
    * perants 
    * */

    node *H=NULL; // head, tail

    node* rotL(node *p) // rotate left
    {
        node *c = p->R; 
        // node p: perent, c: child
        p->R = c->L;
        c->L = p;
        c->red = p->red;
        p->red = 1;

        if(p==H) H=c;
        return c;
    }

    node* rotR(node *p) // rotate right
    {
        node *c = p->L; 
        // node p: perent, c: child
        p->L = c->R;
        c->R = p;
        c->red = p->red;
        p->red = 1;
        
        if(p==H) H=c;
        return c;
    }

    void flip(node *p)
    {
        (p==H)?
            p->red = 0:
            p->red = 1;
        p->L->red = 0;
        p->R->red = 0;
    }

    node* put(node *N, int data)
    {
        //static int data = datum;

        if(N==NULL)
        {
            node *t = new node(data);
            
            if(H==NULL) 
               H=t,H->red=0;
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

    bool isRed(node* n)
    {
        if(n==NULL)
            return false;
        else
            return n->red;
    }

    void display(node* N)
    {
        if(N!=NULL)
        {
            char c = char(N->data);
            printf("%c ", c);
            display(N->L);
            display(N->R);
        }
            
        return;
    }
        
};


// TESTING HERE

int main(){
 
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
    //M E C A L H R P X S 
    */

    /* merge sort test
    veci v = {1,3,6,9,4,6,8,9};
    mergesort(v,0,v.size()-1);
     for(int i:v)
        cout<<i<<' ';
    return 0;
    */
}