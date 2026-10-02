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

    ll p = 79, alpha = 6, x = 5, beta = modpow(alpha, x, p);

    ll m = 25, k = 7;

    cout << "original: " << m << "\n";
    ll c1 = modpow(alpha, k, p);
    ll c2 = (m * modpow(beta, k, p)) % p;

    cout << "ciphertext c1, c2: " << c1 << " " << c2 << "\n";

    ll dec = (c2 * modinv(modpow(c1, x, p), p)) % p;

    cout << "recovered: " << dec << "\n";
    return 0;
}