#include<bits/stdc++.h>
using namespace std;

using ll = long long;

bool isPrimitive(ll g, ll p){
    /*set< ll > s;

    ll cur = 1;
    for(ll i = 1; i < p; i++){
        cur = (cur * g) % p;
        s.insert(cur);
    }

    return s.size() == p-1;
    */
    
    vector<ll> v;
    ll cur = 1;
    for(ll i = 1; i < p; i++){
        cur = (cur * g) % p;
        v.push_back(cur);
    }

    sort(v.begin(), v.end());

    for(ll i = 1; i < p; i++){
        if(v[i-1] != i)
            return false;
    }
    return true;
}

int main(){

    ll p = 79;

    ll g = 2;

    while(g < p){
        if(isPrimitive(g, p))
            break;
        g++;
    }

    cout << g << "\n";
    return 0;
}