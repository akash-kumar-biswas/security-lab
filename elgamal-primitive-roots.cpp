#include<bits/stdc++.h>
using namespace std;

using ll = long long;

bool isPrimtive(int g, ll p){
    set<ll> s;
    ll cur = 1;
    for (ll i = 1; i < p; i++){
        cur = (cur * g) % p;
        s.insert(cur);
    }

    return s.size() == p - 1;
}


int main(){

    /*
    ll p = 107, g;

    cout << "Enter g: " ;
    cin >> g;

    vector<ll> residues;

    ll curr = 1;

    for(ll i = 1; i < p; i++){
        curr = (curr * g)% p;
        residues.push_back(curr);
    }

    sort(residues.begin(), residues.end());

    int f = 1;
    for(ll i = 0; i < residues.size(); i++){
        if(residues[i] != (i+1)){
            f = 0;
            break;
        }
    }
    */

    ll p = 107;
    ll g = 2;

    int f = 0;
    while(1){
        if(isPrimtive(g, p)){
            break;
        }
        g++;
    }
  
    cout << g;


    return 0;
}