/*
 * @Samaritan_infi
 */
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

/// 最大值即单调队列尾值
/// 变化次数即单调队列中元素个数

const int N = 10000010;
int a[N], q[N];
int main(){
    int kase;
    scanf("%d", &kase);
    while(kase --) {
        int n, m, k, P, Q, R, MOD;
        scanf("%d %d %d %d %d %d %d", &n, &m, &k, &P, &Q, &R, &MOD);
        for(int i = 1; i <= k; i ++)
            scanf("%d", &a[i]);
        for(int i = k + 1; i <= n; i ++)
            a[i] = (1LL * P * a[i - 1] + 1LL * Q * i + R) % MOD;
        int l, r, i;
        ll A = 0, B = 0;
        for(l = 1, r = 0, i = n; i; i --) {
            while(l <= r && a[ q[r] ] <= a[i]) r --;
            q[++ r] = i;
            if(i + m - 1 <= n) {
                while(q[l] >= i + m) l ++;
                A += i ^ a[q[l]];
                B += i ^ (r - l + 1);
            }
        }
        printf("%lld %lld\n", A, B);
    }
    return 0;
}
