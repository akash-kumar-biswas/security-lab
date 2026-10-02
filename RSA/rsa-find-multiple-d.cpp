#include<bits/stdc++.h>
using namespace std;

using ll = long long;

ll norm(ll x, ll m){
    return (x%m + m)%m;
}

ll egcd(ll a, ll b, ll &x, ll &y){
    if(b == 0){
        x = 1;
        y = 0;
        return a;
    }

    ll x1, y1;
    ll g = egcd(b, a%b, x1, y1);
    x = y1;
    y = x1 - (a/b)*y1;
    return g;
}

ll modinv(ll a, ll m){
    ll x, y;
    ll g = egcd(a, m, x, y);
    return norm(x, m);
}


int main(){
    ll p = 53, q = 61;

    ll n = p*q;
    ll phi = (p-1) * (q-1);

    ll e = 2;
    ll x,y;
    while(e < phi){
        if(egcd(e, phi, x, y) == 1)
            break;
        e++;
    }

    ll d1 = modinv(e, phi);

    ll d2 = d1 + phi;
    ll d3 = d1 + 2*phi;

    cout << "Computed d1, d2, d3: " << d1 << " " << d2 << " " << " " << d3 << "\n";
    cout << "Verification: "<< "\n";

    if(e*d1 % phi == 1)
        cout << "Valid d\n";
    
    if(e*d2 % phi == 1)
        cout << "Valid d\n";

    if(e*d3 % phi == 1)
        cout << "Valid d\n";

    return 0;
    
}