/*
 * FOR TESTING 
 * */

#include<bits/stdc++.h>
using namespace std;

#include"Sort.h"

int main(){

    vector<int> ans, v={5,8,6,0,2,1,7,3,9,4};
    Sort ss(v);
    ss.vec = v;
    ss.mergesort(0,9);
    v = ss.vec;
    for(int i:v)
        cout<<i<<' ';

    return 0;
}