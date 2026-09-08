#include<bits/stdc++.h>
using namespace std;

using ll = long long;

ll modpow(ll a, ll e, ll m){
    ll r = 1;
    a %= m;

    while (e){
        if(e & 1){
            r = (r*a) % m;
        }
        a = (a*a) % m;
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
    return (x%m + m) % m;
}

int main(){
    ll alpha = 6, p = 79, x = 15, beta = modpow(alpha, x, p);

    cout << "alpha , beta, p : " << alpha << " " << beta << " " << p << endl;

    cout<< "x : " << x << endl;

    ll m1 = 60, r1 = 7;

    cout << "m1 : " << m1 << endl;

    ll c11 = modpow(alpha, r1, p);
    ll c12 = (m1 * modpow(beta, r1, p)) % p;

    cout << "c11, c12 : " << c11 << " " << c12 << endl;

    ll m2 = 70, r2 = 9;

    cout << "m2 : " << m2 << endl;

    ll c21 = modpow(alpha, r2, p);
    ll c22 = (m2 * modpow(beta, r2, p)) % p;

    cout << "c21, c22 : " << c21 << " " << c22 << endl;


    ll c1p = (c11 * c21) % p;
    ll c2p = (c12 * c22) % p;   

    ll m_dec = (c2p * modinv(modpow(c1p, x, p), p) % p);

    cout << "m_dec : " << m_dec << " " << "Expected : " << (m1 * m2) % p<< endl;

    return 0;
}