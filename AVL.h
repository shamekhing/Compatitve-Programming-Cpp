#include<bits/stdc++.h>
using namespace std;

struct node 
{ 
    int d,h=1; 
    node*l=NULL,
        *r=NULL;
    
    node(int datum):d(datum){} 
}; 

class AVL
{   
private:
    
    int H  (node *N);  // height
    int BF (node *N);  // balance factor 
    node *RR(node *p); // Rotate Right
    node *RL(node *p); // Rotate Left

    node* makeBalance(node *N, int B, int d);


public:
    node* root=NULL;
    void display(node *root);
    node* insert(node* N, int d);
    node* remove(node* N, int d);
    
};


int AVL::H (node *N) // height
{ 
    if (N == NULL) 
        return 0; 

    return N->h; 
} 

int AVL::BF (node *N) // balance factor 
{ 
    if (N == NULL) 
        return 0; 
        
    return H(N->l)-H(N->r); 
} 

    

node* AVL::RR(node *p) // Rotate Right
{   // ROTATE
    node *c = p->l; p->l = c->r; c->r = p; 
    // Update H 
    p->h = max(H(p->l), H(p->r)) +1; 
    c->h = max(H(c->l), H(c->r)) +1; 
    // Return New Perent 
    return c; 
} 
        
node* AVL::RL(node *p) 
{   // Rotate
    node *c = p->r; p->r = c->l; c->l = p;
    // Update H 
    p->h = max(H(p->l),	H(p->r)) +1; 
    c->h = max(H(c->l), H(c->r)) +1;
    // Return New Perent 
    return c; 
} 

node* AVL::makeBalance(node *N, int B, int d)
{
    if ( B>1 && d < N->l->d) return RR(N);  // Left Left Case 
    if ( B>1 && d > N->l->d) 
    { N->l = RL(N->l); return RR(N); }      // Left Right Case

    if ( B<-1 && d > N->r->d) return RL(N); // Right Right Case 
    if ( B<-1 && d < N->r->d) 
    { N->r = RR(N->r); return RL(N); }      // Right Left Case 

    return N; // no change
}

node* AVL::insert(node* N, int d) 
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

node* AVL::remove(node* N, int d)  
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

void AVL::display(node *root) 
{ 
    if(root != NULL) 
    { 
        cout << root->d << " "; 
        display(root->l); 
        display(root->r); 
    } 
}