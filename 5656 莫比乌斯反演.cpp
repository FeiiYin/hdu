/*
 * @Samaritan_infi
 */
/// 设出f，F的函数后，解决求F的问题，在求出f就容易了
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

const int maxn = 1050;
const int mod = 100000007;

ll quick_pow(ll a, ll x) {
    ll ans = 1;
    while(x) {
        if(x & 1) ans = (ans * a) % mod;
        a = (a * a) % mod;
        x >>= 1;
    }
    return ans % mod;
}

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

int read[maxn];
int num[maxn]; /// num[i]代表含因数i的个数
ll f[maxn]; /// gcd == k 的子集个数
ll F[maxn]; /// gcd 为 k 的倍数的子集个数

void show(ll a[], int len) {
    for(int i = 0; i <= len; i ++) cout << a[i] << " "; cout << endl;
}
void show(int a[], int len) {
    for(int i = 0; i <= len; i ++) cout << a[i] << " "; cout << endl;
}
int main() {
    Mobius();
    int kase; scanf("%d", &kase);
    while(kase --) {
        int n; scanf("%d", &n);
        int max_num = 0;
        for(int i = 0; i < n; i ++) {
            scanf("%d", &read[i]);
            max_num = max(max_num, read[i]);
        }
        memset(num, 0, sizeof num);
        memset(f, 0, sizeof f);
        for(int i = 1; i <= max_num; i ++) {
            for(int j = 0; j < n; j ++) {
                if(! (read[j] % i)) num[i] ++;
            }
        }
        for(int i = 1; i <= max_num; i ++) {
            F[i] = (quick_pow((ll)2, (ll)num[i]) - 1 + mod) % mod;
        }
        ll ans = 0;
        for(int i = 1; i <= max_num; i ++) {
            for(int j = 1; j <= max_num; j ++) {
                if(! (j % i)) {
                    f[i] = (f[i] + mu[j / i] * F[j]) % mod;
                }
            }
            ans = (ans + f[i] * i) % mod;
        }
        //show(f, max_num);
        //show(F, max_num);
        printf("%lld\n", (ans + mod) % mod);
    }
    return 0;
}
