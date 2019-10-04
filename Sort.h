#include<bits/stdc++.h>

using namespace std;
typedef vector<int> ivec;
typedef vector <int>::iterator veci;

class Sort
{
private:
    int iter=0;
public:
    Sort(vector<int> dlt);
   ~Sort();

    vector<int> vec,temp;
   void selection(vector<int> &vec);    // Complexity n^2/2
   void insertion(vector<int> &vec);    // Complexity best n avg n^2/4 worst selection
   void shellsort(vector<int> &vec);    // Complexity sqrt(n^2) for h = 3x+1
   void mergesort(int s, int e);
   void quicksort(vector<int> &vec);    // Complexity sqrt(n^2) for h = 3x+1
   
   void shuffle(vector<int> &vec);      // Complexity n
};

Sort::Sort(vector<int> dlt)
{
    vec = dlt;
    temp.resize(vec.size());
}

Sort::~Sort()
{
}

void Sort::selection(vector<int> &vec)
{
    int siz = vec.size();
    for (int i = 0; i < siz; i++)
    {
        int m=i;
        for (int j = i+1; j < siz; j++)
        {
            if(vec[j]<vec[i]) // min2max 
                m=j;
        }
        if(i!=m)
            swap(vec[i],vec[m]);
    }
}

void Sort::insertion(vector<int> &vec)
{
    int siz = vec.size();
    for (int i = 0; i < siz; i++)
    {
        for (int j = i; j > 0; j--)
        {
            if(vec[j]<vec[j-1]) // min2max
                swap(vec[j],vec[j-1]);
        }       
    }
}

void shellsort(vector<int> &vec, int h = 1) // TODO
{
    int siz = vec.size();
    
    while(h<siz/3)
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
    ivec ans(temp);
    //{5 6 8,0,2,1,7,3,9,4};    
    return;
}








void Sort::shuffle(vector<int> &vec)
{
    int r,siz = vec.size();
    for (int i = 0; i < siz; i++)
    {
        r = rand() % i; // + offset
        swap(vec[i],vec[r]);
    }
}