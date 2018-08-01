/*
 * @Samaritan_infi
 */
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int N=200010;
int ans[N];
bool must[N];

struct P {
    int x, y, p;
    bool operator < (const P &b) const {
        if(x != b.x)return x < b.x;
        if(y != b.y)return y > b.y;
        return p < b.p;
    }
} a[N], q[N];

/// 答案一定是上凸包上的点（xi * yj - xj * yi）
/// 字典序最小，共线的时候取最小
int main(){
    int kase;
    scanf("%d", &kase);
    while(kase --) {
        int n;
        scanf("%d", &n);
        for(int i = 1; i <= n; i ++) {
            scanf("%d %d", &a[i].x, &a[i].y);
            a[i].p = i;
        }
        sort(a + 1, a + n + 1);
        /// 求凸包
        int t, i;
        for(t = 0, i = 1; i <= n; i ++) {
            if(i > 1 && a[i].x == a[i-1].x) continue;
            while(t > 1 && 1LL * (q[t].y - q[t-1].y) * (a[i].x - q[t].x)
                  < 1LL*(a[i].y - q[t].y) * (q[t].x - q[t-1].x))
                    t --;
            q[++ t] = a[i];
        }
        for(int i = 1; i <= t; i ++) must[i] = 0;
        must[1] = must[t] = 1;
        for(int i = 2; i < t; i ++)
            if(1LL * (q[i].y-q[i-1].y) * (q[i+1].x-q[i].x)
               != 1LL*(q[i+1].y-q[i].y) * (q[i].x-q[i-1].x))
               must[i]=1;
        for(int i = t; i; i --)
            if(must[i])
                ans[i] = q[i].p;
            else
                ans[i] = min(ans[i+1], q[i].p);

        for(int i = 1; i < t; i ++)
            if(ans[i] == q[i].p)
                printf("%d ", ans[i]);
        printf("%d\n", ans[t]);
    }
    return 0;
}
