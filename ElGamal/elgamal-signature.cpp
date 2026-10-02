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

    ll m = 34;

    ll k = 2;

    ll x3, y3;
    while(k < p-1){
        if(egcd(k, p-1, x3, y3) == 1)
            break;
        k ++;
    }

    ll y1 = modpow(alpha, k, p);
    ll y2 = (modinv(k, p-1) * norm((m - x * y1), p-1)) % (p-1);

    ll lhs = (modpow(beta, y1, p) * modpow(y1, y2, p)) % p;

    ll rhs = modpow(alpha, m, p);

    cout << "verification result --> lhs, rhs: " << lhs << " " << rhs << "\n";
    if(lhs == rhs)
        cout << "valid\n";
    else
        cout << "invalid";

    
    return 0;
}