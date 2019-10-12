#include<bits/stdc++.h>

/*
 * Sort Algorithms 
 * How To Use :
 * 
 *  #include"Sort.h"
 *  Sort(vector).sortMethod()
 * 
 * Sort Methods:
 * 1- selection
 * 2- insertion
 * 3- shellsort --TODO
 * 4- mergesort
 * 5- quicksort
 * 6- shuffle
 */

using namespace std;
typedef vector<int> ivec;
typedef vector <int>::iterator veci;

class Sort
{
private:
    ivec &vec,temp;
protected:
    int siz;

public:
    Sort(ivec &v);
   ~Sort();

   void selection();    // Complexity n^2/2
   void insertion();    // Complexity best n avg n^2/4 worst selection
   void shellsort();    // Complexity sqrt(n^2) for h = 3x+1
   
   void mergesort();    // Complexity n log(n)
        void mergesort(int s, int e); // over loaded with default argument
   void quicksort();
        void quicksort(int s, int e);    // Complexity sqrt(n^2) for h = 3x+1

   void shuffle();      // Complexity n
};

Sort::Sort(ivec &v):vec(v), siz(v.size()), temp(v){};

Sort::~Sort()
{
}

void Sort::selection()
{
    //int siz = vec.size();
    for (int i = 0; i < siz; i++)
    {
        int m=i;
        for (int j = i+1; j < siz; j++)
        {
            if(vec[j]<vec[m]) // min2max 
                m=j;
        }
        if(i!=m)
            swap(vec[i],vec[m]);
    }
}

void Sort::insertion()
{
    //int siz = vec.size();
    for (int i = 0; i < siz; i++)
    {
        for (int j = i; j > 0; j--)
        {
            if(vec[j]<vec[j-1]) // min2max
                swap(vec[j],vec[j-1]);
        }       
    }
}

/*
void shellsort(int h = 1) // TODO
{
    
    while(h < siz/3)
        h=3*h+1;
    
    while (h > 0) // or h>=1
    {
        for (int i = h; i < siz; i++)
        {
            for (int j = i; j >= h && vec[j]<vec[j-h]; j-=h)
            {
                swap(vec[j],vec[j-h]);
            }
        }
        h/=3;
    }
}
*/

void Sort::mergesort(int s, int e)
{
    
    int I = e-s;

    if (e==s) return;
    int m = I>>1;//m+1
    
    mergesort(s,s+m);
    mergesort(s+m+1,e);

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
        Sort::vec[s+i]=temp[i];
    
    return;
}

void Sort::quicksort(int s, int e)
{
    if(e<=s) return;
    int l=s,h=e,
        i=s+1;

    while (i<=h)
    {
             if(vec[l] > vec[i]) {swap(vec[l],vec[i]); l++; i++;}
        else if(vec[l] < vec[i]) {swap(vec[i],vec[h]); h--;}
        else i++;
        
    }

    quicksort(s,l-1);
    quicksort(h+1,e);    
    
    return;
}


void Sort::mergesort(){mergesort(0,siz-1);}
void Sort::quicksort(){shuffle();quicksort(0,siz-1);}

void Sort::shuffle()
{
    int r;//siz = vec.size();
    for (int i = 0; i < siz; i++)
    {
        r = rand() % (i+1); // + offset
        swap(vec[i],vec[r]);
    }
}