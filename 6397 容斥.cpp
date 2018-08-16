/*
 * @Samaritan_infi
 */

#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

inline int read()
{
    int x=0,t=1;char ch=getchar();
    while((ch<'0'||ch>'9')&&ch!='-')ch=getchar();
    if(ch=='-')t=-1,ch=getchar();
    while(ch<='9'&&ch>='0')x=x*10+ch-48,ch=getchar();
    return x*t;
}

const int N = 1e6 + 5;
const int mod = 998244353;

#define inv(x) qpow(x, mod - 2)
inline ll add(ll a, ll b) { if ((a += b) >= mod) a -= mod; return a; }
inline ll mul(ll a, ll b) { return ll(a) * b % mod; }
int qpow(int a, int b) { int r = 1; for (; b; b >>= 1) { if (b & 1) r = mul(r, a); a = mul(a, a); } return r; }
ll fac[N], inv_fac[N];

void init(){
    fac[0] = fac[1] = 1;


    for(int i = 2; i < N; i ++) {
        fac[i] = (fac[i - 1] * i) % mod;
        //inv[i] = (mod - mod / i) * inv[mod % i] % mod; 逆元
    }
    inv_fac[N - 1] = inv(fac[N - 1]);
    for(int i = N - 2; i >= 0; i --)
        inv_fac[i] = (inv_fac[i + 1] * (i + 1)) % mod;
}

inline int C(int a, int b) {
    return mul(fac[a], mul(inv_fac[a - b], inv_fac[b]));
}

//int dp[2000][2000];

int main() {
    init();
    int kase = read();
    while(kase --) {
        ll n, len, up;
        scanf("%lld %lld %lld", &n, &len, &up);
        if(up > len * (n - 1)) { puts("0"); continue; }


        if(up < n) {
            /// a 个东西分到 k 个地方 C(a + k - 1, k - 1)
            ll ans = C(up + len - 1, len - 1);
            printf("%lld\n", ans);
            continue;
        }

        ll ans = C(up + len - 1, len - 1);
        ll num = up / n;
        for(int i = 1; i <= num; i ++) {
            up -= n;
            ll temp = mul(C(up + len - 1, len - 1), C(len, i));
            if(i & 1)
                ans -= temp;
            else
                ans += temp;
        }
        printf("%lld\n", (ans % mod + mod) % mod);
    }
    return 0;
}
