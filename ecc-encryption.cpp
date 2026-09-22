#include<bits/stdc++.h>
using namespace std;

int pp = 17;
int a = 2;
int b = 2;

using ll = long long;

struct point
{
    ll x, y;
    bool inf = false;
};

ll normalize(ll x, ll m){
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
    egcd(a, m, x, y);
    return normalize(x, m);
}

point add(point p, point q){
    if(p.inf)
        return q;
    if(q.inf)
        return p;
    
    if(q.x == p.x && q.y == normalize(-p.y, pp))
        return {0,0, true};
    
    ll s;
    if(p.x == q.x && p.y==q.y)
        s = (3*p.x*p.x + a) * modinv(normalize(2*p.y, pp), pp);
    else
        s = ((q.y-p.y) * modinv(normalize(q.x-p.x, pp), pp));
    
    s = normalize(s, pp);

    ll x3 = normalize((s*s -  p.x - q.x), pp);
    
    ll y3 = normalize(s* (p.x - x3) - p.y, pp);

    return {x3, y3, false};
}

point multiply(ll k, point p){
    point r = {0, 0, true};

    while (k--)
    {
        r = add(r, p);
    }
    return r;
}

int main(){
    point g = {5, 1};
    ll x = 5;
    point q = multiply(x, g);

    point m = {6, 3};

    ll k = 3;
    point c1 = multiply(k, g);

    point c2 = add(m, multiply(k, q));

    point neg = multiply(x, c1);
    neg = {neg.x, normalize(-neg.y, pp)};
    point dec_m = add(c2,  neg);

    cout << "original: " << m.x << " " << m.y << endl;
    cout << "expected: " << dec_m.x << " " << dec_m.y << endl;  

}