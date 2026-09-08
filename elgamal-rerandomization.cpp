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

    ll m = 60, r1 = 7;

    cout << "m : " << m << endl;

    ll c1 = modpow(alpha, r1, p);
    ll c2 = (m * modpow(beta, r1, p)) % p;

    cout << "c1, c2 : " << c1 << " " << c2 << endl;

    ll  r2 = 9;


    ll c1_new = (c1* modpow(alpha, r2, p)) % p;
    ll c2_new = (c2 * modpow(beta, r2, p)) % p;

    cout << "c1_new, c2_new : " << c1_new << " " << c2_new << endl;
  

    ll m_dec = (c2_new * modinv(modpow(c1_new, x, p), p) % p);

    cout << "m_dec : " << m_dec << endl;

    return 0;
}