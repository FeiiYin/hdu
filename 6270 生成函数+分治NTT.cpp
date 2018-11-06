#include <bits/stdc++.h>
 
using namespace std;
 
#define rep(i, a, b)    for (int i(a); i <= (b); ++i)
#define dec(i, a, b)    for (int i(a); i >= (b); --i)
#define MP      make_pair
#define fi      first
#define se      second
 
 
typedef long long LL;
 
const int  N = 1e5 + 10;
const LL mod = 998244353;
const LL g   = 3;
 
vector <LL> v[N << 1];
LL x1[N << 1], x2[N << 1];
LL fac[N];
LL ans, flag;
int T;
int n, all, cnt;
int sz;
 
inline LL Pow(LL a, LL b, LL mod){
    LL ret(1);
    for (; b; b >>= 1, (a *= a) %= mod) if (b & 1) (ret *= a) %= mod;
    return ret;
}
 
inline LL C(LL n, LL m){ return m > n ? 0 : fac[n] * Pow(fac[m] * fac[n - m] % mod, mod - 2, mod) % mod; }
 
struct cmp{
    bool operator ()(int a, int b){
        return v[a].size() > v[b].size();
    }
};
 
priority_queue <LL, vector <LL>, cmp> q;
 
void change(LL y[], int len){
    for (int i = 1, j = len / 2; i < len - 1; i++){
        if (i < j) swap(y[i], y[j]);
        int k = len / 2;
        while (j >= k){
            j -= k;
            k /= 2;
        }
        if (j < k) j += k;
    }
}
 
void ntt(LL y[], int len, int on){
    change(y, len);
    for (int h = 2; h <= len; h <<= 1){
        LL wn = Pow(g, (mod - 1) / h, mod);
        if (on == -1) wn = Pow(wn, mod - 2, mod);
        for (int j = 0; j < len; j += h){
            LL w = 1ll;
            for (int k = j; k < j + h / 2; k++){
                LL u = y[k];
                LL t = w * y[k + h / 2] % mod;
                y[k] = (u + t) % mod;
                y[k + h / 2] = (u - t + mod) % mod;
                w = w * wn % mod;
            }
        }
    }
 
    if (on == -1){
        LL t = Pow(len, mod - 2, mod);
        rep(i, 0, len - 1) y[i] = y[i] * t % mod;
    }
}
 
void mul(vector <LL> &a, vector <LL> &b, vector <LL> &c){
    int len = 1;
    int sz1 = a.size(), sz2 = b.size();
 
    while (len <= sz1 + sz2 - 1) len <<= 1;
 
    rep(i, 0, sz1 - 1) x1[i] = a[i];
    rep(i, sz1, len)   x1[i] = 0;
 
    rep(i, 0, sz2 - 1) x2[i] = b[i];
    rep(i, sz2, len)   x2[i] = 0;
 
    ntt(x1, len, 1);
    ntt(x2, len, 1);
 
    rep(i, 0, len - 1) x1[i] = x1[i] * x2[i];
 
    ntt(x1, len, -1);
 
    vector <LL>().swap(c);
    rep(i, 0, sz1 + sz2 - 2) c.push_back(x1[i]);
}
 
 
int main(){
 
    fac[0] = 1;
    rep(i, 1, 1e5 + 3) fac[i] = fac[i - 1] * i % mod;
 
    scanf("%d", &T);
 
    while (T--){
        scanf("%d", &n);
        rep(i, 0, n + 1) vector <LL>().swap(v[i]);
 
        while (!q.empty()) q.pop();
 
        all = 0;
 
        rep(i, 1, n){
            int x, y;
            scanf("%d%d", &x, &y);
            v[i].resize(min(x, y) + 1);
            rep(k, 0, min(x, y)) v[i][k] = C(x, k) * C(y, k) % mod * fac[k] % mod;
            q.push(i);
            all += x;
        }
 
        cnt = n;
        rep(i, 1, n - 1){
            int x = q.top(); q.pop();
            int y = q.top(); q.pop();
 
            mul(v[x], v[y], v[++cnt]);
 
            vector <LL>().swap(v[x]);
            vector <LL>().swap(v[y]);
 
            q.push(cnt);
        }
 
        ans  = 0;
        flag = 1;
        sz   = (int)v[cnt].size();
        rep(i, 0, sz - 1){
            ans = ans + flag * fac[all - i] % mod * v[cnt][i] % mod;
            ans = (ans + mod) % mod;
            flag = -flag;
        }
 
        printf("%lld\n", ans);
    }
 
    return 0;
}
