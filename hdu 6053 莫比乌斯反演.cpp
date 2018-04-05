/*
 * @Samaritan_infi
 */
/// 反面求解，设的函数依旧相似
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

const int maxn = 1e5 + 5;
const int mod = 1e9 + 7;

int mu[maxn], prime[maxn];
bool vis[maxn];

void Mobius() {
    memset(prime, 0, sizeof prime);
    memset(mu, 0, sizeof mu);
    memset(vis, 0, sizeof vis);
    mu[1] = 1;
    int cnt = 0;
    for(int i = 2; i < maxn; i ++) {
        if(! vis[i]) {
            prime[cnt ++] = i;
            mu[i] = -1;
        }
        for(int j = 0; j < cnt && i * prime[j] < maxn; j ++) {
            vis[i * prime[j]] = 1;
            if(i % prime[j]) mu[i * prime[j]] = -mu[i];
            else {
                mu[i * prime[j]] = 0;
                break;
            }
        }
    }
}

ll quick_pow(ll a, ll x) {
    ll ans = 1;
    while(x) {
        if(x & 1) ans = (ans * a) % mod;
        a = (a * a) % mod;
        x >>= 1;
    }
    return ans % mod;
}

int num[maxn];


int main() {
    Mobius();
    int kase; scanf("%d", &kase);
    int tt = 1;
    while(kase --) {
        int n; scanf("%d", &n);
        int x;
        int max_x = 0, min_x = 1e9;
        ll mul = 1;
        memset(num, 0, sizeof num);
        for(int i = 1; i <= n; i ++) {
            scanf("%d", &x);
            mul = (mul * x) % mod;
            max_x = max(max_x, x);
            min_x = min(min_x, x);
            num[x] ++;
        }

        for(int i = min_x; i <= max_x + 1; i ++)
            num[i] += num[i - 1];


        /// 如果因数比其中最小的值大，那么说明一定gcd == 1
        /// 不会存在gcd > min_x 的情况
        ll ans = 0;
        for(int i = 1; i <= min_x; i ++) {
            if(! mu[i]) continue;
            ll now = mu[i];
            for(int j = min_x; j <= max_x; ) {
                int val = j / i;
                int last = min(max_x, (val + 1) * i - 1);
                now = (now * quick_pow(val, num[last] - num[j - 1])) % mod;
                j = last + 1;
            }
            ans = (ans + now) % mod;
        }
        printf("Case #%d: %lld\n", tt ++, ((mul - ans) % mod + mod) % mod);
    }
    return 0;
}
