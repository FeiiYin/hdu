/*
 * @Samaritan_infi
 */
/// x = 2 * 3 * 4 * 5 * ... 
/// 多余的k应该放置在越小的地方，因为这样能让它响应增长的，即剩余的部分越大，即结果越大
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

const ll mod = 1e9 + 7;

ll f[45000]; //前缀乘
int sum[45000]; //前缀和
int inv[45000]; //乘法逆元
void init() {
    inv[1] = 1; f[1] = 1; sum[1] = 0;
    for (int i = 2; i < 45000; i ++) {
        inv[i]=(mod - mod / i) * inv[mod % i] % mod;//乘法逆元
        f[i] = (f[i - 1] * i) % mod;//前缀乘（在取余MOD的环境下，配合后面的乘法逆元）
        sum[i] = sum[i - 1] + i;//前缀和（从2开始）
    }
    return;
}
int main() {
    init();
    int kase; scanf("%d" , &kase);
    while(kase --) {
        int n, k;
        ll ans;
        scanf("%d" , &n);
        if(n < 5) {
            printf("%d\n" , n);
            continue;
        }
        int l = 2, r = 45000;

        while(l + 1 < r) {
            int mid = (l + r) >> 1;
            if(sum[mid] > n) r = mid;
            else l = mid;
        }
        k = n - sum[l];
        if(2 + k > l)
            ans = f[l] * inv[2] % mod * (k + 2) % mod;
        else
            ans = f[l] * inv[l + 1 - k] % mod * (l + 1) % mod;
        printf("%lld\n" , (ans + mod) % mod);
    }
    return 0;
}
