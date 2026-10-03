#include<bits/stdc++.h>
using namespace std;

using ll = long long;


ll pp = 17;
ll a = 2, b = 2;  // y^2 = x^3 + 2x + 2

struct point{
    ll x, y;
    bool inf = false;
};

ll norm(ll x, ll m){
    return (x%m + m) % m;
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

point add(point p, point q){
    if(q.inf)
        return p;
    if(p.inf)
        return q;
    
    ll x1 = p.x, y1 = p.y, x2 = q.x, y2 = q.y;
    
    if(x1 == x2 && y1 == norm(-y2, pp))
        return {0, 0, true};
    
    ll s;
    if(x1== x2 && y1 == y2){
        if(y1 == 0)
            return {0, 0, true};
        s = (3 * x1*x1 + a) * modinv(norm(2*y1, pp), pp);
    }
    else{
        s = (y2 - y1) * modinv(norm(x2 - x1, pp), pp);
    }
    s = norm(s, pp);

    ll x3 = norm(s*s - x1 - x2, pp);
    ll y3 = norm(s * (x1 - x3) - y1, pp);

    return {x3, y3};
}

point multiply(ll k, point g){
    point r = {0, 0, true};

    while(k){
        if(k & 1)
            r = add(r, g);
        g = add(g, g);
        k >>= 1;
    }
    return r;
}

ostream& operator<<(ostream& out, point p){
    out << p.x << " " << p.y;
    return out;
}

int main(){
    point g = {5, 1};
    ll x = 5;

    point q = multiply(x, g);

    point m = {0, 6};
    ll k1 = 4;

    point c1 = multiply(k1, g);
    point c2 = add(m, multiply(k1, q));

    ll k2 = 5; 
    
    point c1p = add(c1, multiply(k2, g));
    point c2p = add(c2, multiply(k2, q));

    point neg = multiply(x, c1p);
    neg.y = norm(-neg.y, pp);

    point dec = add(c2p, neg);

    cout << "original: " << m << endl;
    cout << "recovered randomized ciphertext: " << dec << endl;
}

