/*
 * @Samaritan_infi
 */
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int N = 1 << 10;
const int mod = 1000000007;
int f[N], cnt[N], ans[N];


int main(){
    int kase;
    scanf("%d", &kase);
    while(kase --) {
        int n, m;
        scanf("%d %d", &n, &m);
        int all = 1 << n;

        /// __builtin_popcount(), 计算数里面有多少个1
        /// 由于是映射到表里计算，非常快
        for(int i = 0; i < all; i ++)
            f[i] = 0, cnt[i] = __builtin_popcount(i);
        f[0] = 1;
        char op[10];
        int x, y;
        while(m --) {
            scanf("%s %d %d", op, &x, &y);
            x --; y --;
            int status = (1 << x) | (1 << y);
            if(op[0]=='+') {
                for(int i = all - 1; ~ i; i --)
                    if(! (i & status))
                        f[i ^ status] = (f[i ^ status] + f[i]) % mod;
            } else {
                for(int i = 0; i < all; i ++)
                    if(! (i & status))
                        f[i ^ status] = (f[i ^ status] - f[i] + mod) % mod;
            }
            for(int i = 1; i <= n; i ++) ans[i] = 0;
            for(int i = 1; i < all; i ++)
                ans[cnt[i]] = (ans[cnt[i]] + f[i]) % mod;
            for(int i = 2; i <= n; i += 2)
                printf("%d%c", ans[i], i < n ? ' ' : '\n');
        }
    }
    return 0;
}
