#include<bits/stdc++.h>
using namespace std;

using ll = long long;


int main(){
    ll p = 79, g;

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

    if(f){
        cout << "Valid";
    }
    else
        cout << "Invalid";


    return 0;
}