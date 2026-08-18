#include<bits/stdc++.h>
using namespace std;

using ll = long long;

ll modpow(ll a, ll e, ll m){
    ll r=1;
    a%=m;

    while(e){
        if(e&1){
            r = (__int128)r*a % m;
        }
        a = (__int128)a*a % m;
        e >>= 1;
    }
    return r;
}

ll egcd(ll a, ll b, ll &x, ll &y){
    if(b == 0){
        x = 1;
        y = 0;
        return a;
    }

    ll x1, y1;
    ll g = egcd(b, a%b, x1, y1);
    x=y1;
    y=x1 - (a/b)*y1;
    return g;
}

ll modinv(ll a, ll m){
    ll x, y;
    ll g = egcd(a, m, x, y);
    return (x%m + m) %m;
}

int main(){
    ll p = 61, q = 53;
    ll n = p*q;
    ll phi = (p-1) * (q-1);

    ll e = 2;
    ll x, y;
    while(e < phi){
        if(egcd(e, phi, x, y) == 1) break;
        e++;
    }


    ll d = modinv(e, phi);

    cout << "Public Key (n, e): " << n << " "<< e << endl;
    cout << "Private Key (n, d): " << n << " "<< d << endl;

    ll m;
    cout << "Enter Message: ";
    cin >>m;

    ll sign = modpow(m, d, n);

    ll verify = modpow(sign, e, n);

    cout << "Verification Result: " << (verify == m ? "Valid" : "Invalid" )<< endl;
}