/*
 * @Samaritan_infi
 */
#include <bits/stdc++.h>
using namespace std;

#define rep(i,a,b) for(int i = (a); i <= (b); ++i)
#define sqr(x) (x) * (x)

typedef long long ll;
const int N = 100005;
const int P = 1000000007;
const ll mod = P;
const int INF = 0x3f3f3f3f;
const ll LLINF = 0x3f3f3f3f3f3f3f3f;
ll qmod(ll a,ll n,ll mod){ll ans=1;while(n){assert(ans>0);if(n&1ll)ans=ans*a%mod;n>>=1;a=a*a%mod;}return ans%mod;}

//head

struct Matrix {
    ll a[4][4];
    void init() {
        memset(a,0,sizeof(a));
    }
};
Matrix mul(Matrix a, Matrix b) {
    Matrix ans; ans.init();
    rep(i,1,3) rep(j,1,3) rep(k,1,3) ans.a[i][j] = (ans.a[i][j]+a.a[i][k]*b.a[k][j])%mod;
    return ans;
}
Matrix powmod(Matrix a, ll n) {
    Matrix ans; ans.init();
    if(!n) return ans;
    rep(i,1,3) ans.a[i][i] = 1;
    while(n) {
        if(n&1) ans = mul(ans,a);
        n >>= 1;
        a = mul(a, a);
    }
    return ans;
}

ll f[N], k[N];
void cal(ll a, ll b, ll c, ll d, ll p, ll n) {
    f[1] = a, f[2] = b;
    k[0] = k[1] = k[2] = 0;
    for(int i = 3; i <= n; i ++) {
        f[i] = (f[i - 2]) * c + f[i - 1] * d + p / i;
        cout << f[i] << " ";
    }
    cout << endl;
    printf("correct : %lld\n", f[n]);
}

int main() {
    int T; scanf("%d",&T);
    while(T--) {
        ll a, b, c, d, p, n; scanf("%lld%lld%lld%lld%lld%lld",&a,&b,&c,&d,&p,&n);
        //cal(a, b, c, d, p, n);
        if(n == 1) {
            printf("%lld\n", a);
            continue;
        }
        if(n == 2) {
            printf("%lld\n", b);
            continue;
        }

        ll ans = 0;
        Matrix f; f.init(); f.a[1][1] = d, f.a[1][2] = c, f.a[2][1] = 1, f.a[1][3] = 1, f.a[3][3] = 1;
        Matrix g = f;
        ll k = p;
        ll ed = min(n, k);
        for(ll l = 3, r = 3; l <= ed; l = r + 1) {
            r = min(k / (k / l), ed);
            f = g;
            f = powmod(f, (r - l + 1));
            ll pre_a = a;
            a = (f.a[2][1] * b % mod + f.a[2][2] * a % mod + f.a[2][3] * (k / l) % mod) % mod;
            b = (f.a[1][1] * b % mod + f.a[1][2] * pre_a % mod + f.a[1][3] * (k / l) % mod) % mod;
        }
        f = g;
        ed = max(ed, (ll)2);
        f = powmod(f, n - ed);
        int pre_a = a;
        if(n - ed != 0) {
            a = (f.a[2][1] * b % mod + f.a[2][2] * a % mod ) % mod;
            b = (f.a[1][1] * b % mod + f.a[1][2] * pre_a % mod ) % mod;
        }
        printf("%lld\n", b);
    }
    return 0;
}
