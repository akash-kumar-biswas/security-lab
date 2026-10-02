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
    ll p1 = 53, q1 = 61;

    ll n1 = p1*q1;
    ll phi1 = (p1-1) * (q1-1);

    ll e1 = 2;
    ll x,y;
    while(e1 < phi1){
        if(egcd(e1, phi1, x, y) == 1)
            break;
        e1++;
    }

    ll d1 = modinv(e1, phi1);

    ll p2 = 71, q2 = 73;

    ll n2 = p2*q2;
    ll phi2 = (p2-1) * (q2-1);

    ll e2 = 2;
    ll x1,y1;
    while(e2 < phi2){
        if(egcd(e2, phi2, x, y) == 1)
            break;
        e2++;
    }

    ll d2 = modinv(e2, phi2);

    ll m = 102;
    cout << "Original: " << m << "\n";

    ll s = modpow(m, d1, n1);

    cout << "signature: " << s << "\n";

    ll c = modpow(s, e2, n2);

    cout << "ciphertext: " << c << "\n";

    ll dec = modpow(c, d2, n2);

    cout << "decrypted: " << dec << "\n";

    ll v = modpow(dec, e1, n1);

    cout << "verificatio: " << v << "\n";


    if(m == v)
        cout << "valid\n";
    else
        cout << "invalid\n";

    return 0;
    
}