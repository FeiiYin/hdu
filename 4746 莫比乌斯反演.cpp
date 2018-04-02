/*
 * @Samaritan_infi
 */
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

const int maxn = 5e5 + 5;
const int mod = 100000007;

int mu[maxn], prime[maxn];
bool vis[maxn];
int num[maxn]; /// num[i]代表含质数因数i的个数
void Mobius() {
    memset(prime, 0, sizeof prime);
    memset(mu, 0, sizeof mu);
    memset(vis, 0, sizeof vis);
    mu[1] = 1;
    int cnt = 0;
    for(int i = 2; i < maxn; i ++) {
        if(! vis[i]) {
            prime[cnt ++] = i;
            num[i] = 1;
            mu[i] = -1;
        }
        for(int j = 0; j < cnt && i * prime[j] < maxn; j ++) {
            vis[i * prime[j]] = 1;
            num[i * prime[j]] = num[i] + 1;
            if(i % prime[j]) mu[i * prime[j]] = -mu[i];
            else {
                mu[i * prime[j]] = 0;
                break;
            }
        }
    }
}

int sum[20][maxn];

void init() {
    Mobius();
    memset(sum, 0, sizeof sum);
    /// sum[i][j] 计算gcd 素因子个数为i的j系数的总和
    /// j 是 i的倍数， 因为 f(n) = sum(n|d) (mu[d/n]*F(d))
    /// 对于f(i), F(j)的贡献系数为mu(j/i)
    /// 而f(i)是gcd == i时的个数，即对gcd 素因子为num[i]时有贡献
    /// 即求出了素因子个数指定时各个j的系数的贡献值
    for(int i = 1; i < maxn; i ++)
        for(int j = i; j < maxn; j += i)
            sum[ num[i] ][j] += mu[j / i];
    /// sum[i][j] 求出 gcd <= i时各个系数的贡献值
    for(int i = 1; i < maxn; i ++)
        for(int j = 1; j < 20; j ++)
            sum[j][i] += sum[j - 1][i];
    /// 求出各个的前缀和，用于分块加速
    for(int i = 0; i < 20; i ++)
        for(int j = 1; j < maxn; j ++)
            sum[i][j] += sum[i][j - 1];
}

void show(ll a[], int len) {
    for(int i = 0; i <= len; i ++) cout << a[i] << " "; cout << endl;
}
void show(int a[], int len) {
    for(int i = 0; i <= len; i ++) cout << a[i] << " "; cout << endl;
}


int main() {
    init();
    int kase; scanf("%d", &kase);
    while(kase --) {
        int a, b, p;
        scanf("%d %d %d", &a, &b, &p);
        ll ans = 0;
        if(p > 18) {
            printf("%lld\n", (ll)a * b);
            continue;
        }
        if(a > b) swap(a, b);
        ///牢记 F(x) = sum(x|n) f(n)
        /// f(n) = sum(n|x) (mu[x/n]*F(x))
        
        for(int i = 1, last; i < a; i = last + 1) {
            last = min(a /(a / i), b /(b / i));
            ans += (ll)(a / i) * (b / i) * (sum[p][last] - sum[p][i - 1]);
        }
        printf("%lld\n", ans);
    }
    return 0;
}
