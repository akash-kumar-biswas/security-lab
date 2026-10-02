#include<bits/stdc++.h>
using namespace std;

using ll = long long;

ll norm(ll x, ll m){
    return (x%m + m)%m;
}

ll modpow(ll a, ll e, ll m){
    ll r = 1;
    a %= m;

    while(e){
        if(e & 1)
            r = (r*a) % m;
        a = (a * a) % m;
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

    ll d = modinv(e, phi);

    ll m1 = 100, m2 = 105;
    cout << "Original m1, m2: " << m1 << " " << m2 << "\n";

    ll c1 = modpow(m1, e, n);
    ll c2 = modpow(m2, e, n);

    ll c = (c1*c2) % n;

    ll dec_c = modpow(c, d, n);


    cout << "Decrypted (C1*C2): " << dec_c << "\n";

    cout << "M1*M2 : " << (m1*m2) % n << "\n";
    return 0;
    
}