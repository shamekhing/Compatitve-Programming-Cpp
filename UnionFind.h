#include<bits/stdc++.h>
/* * * * * * * * * * * * *
 * Union Find Algo&DS    *
 * used for problems of  *
 * dynamic connectivity  *
 * * * * * * * * * * * * */
class UnionFind 
{
private:
    int siz, *UF,*UFz;
public:
     UnionFind(int d);
    ~UnionFind(){};
    
    int root(int x);
    void Union(int a,int b);
    bool Find(int a, int b);
};

UnionFind::UnionFind(int d)
{
    siz=d+1;
    UF =new int[siz];
    UFz=new int[siz];
    for (int i = 0; i < siz; i++)
        UF[i] =i,
        UFz[i]=1;
}
int UnionFind::root(int x)
{
    while (x!=UF[x])
    {
        UF[x]=UF[UF[x]];// path compression
        x=UF[x];
    }
    return x;
}
void UnionFind::Union(int a, int b)
{
    int rootA=root(a),
        rootB=root(b);
    
    if(UFz[rootA]>UFz[rootB])
        std::swap(rootA,rootB);
    
    UF[rootA]=rootB;
    UFz[rootA]+=UFz[rootB];
}
bool UnionFind::Find(int a, int b)
{
    return root(a)==root(b);
}
