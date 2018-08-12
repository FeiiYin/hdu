/*
 * @Samaritan_infi
 */
/// 考虑到并查集， 或者类似合并的，考虑启发式
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int N = 1e5 + 5;

ll pre[N];
int operation[N];
int par[N], set_num[N];
set<ll> pre_a[N], pre_b[N];
ll ans, k;
inline void init(int n) {
    memset(par, 0, sizeof (int) * (n + 2));
    memset(set_num, 0, sizeof (int) * (n + 2));

    for(int i = 1; i <= n; i ++)
        pre_a[i].clear(), pre_b[i].clear();
    ans = 2e9;
}

ll output[N];

int find_par(int x) {
    if(x == par[x]) return x;
    return par[x] = find_par(par[x]);
}

/// x 并入 y
inline void unite_clear(int x, int y) {
    par[x] = y;
    set_num[y] += set_num[x];
    for(ll it : pre_a[x])
        pre_a[y].insert(it);
    for(ll it : pre_b[x])
        pre_b[y].insert(it);
    pre_a[x].clear();
    pre_b[x].clear();
}

void unite(int x, int y) {
    int x_par = find_par(x);
    int y_par = find_par(y);
    /// 把当前元素少的合并到元素多的中
    /// 一定要用后面位置的前缀和减去前面位置的前缀和
    if(x_par > y_par) {
        swap(x_par, y_par);
    }
    /// abs( pre_a[y] - pre_b[x] - k )
    /// 同样枚举元素少的
    if(set_num[x_par] > set_num[y_par]) {
        for(ll now : pre_a[y_par]) {
            now = now - k;
            auto t = pre_b[x_par].lower_bound(now);
            if(t != pre_b[x_par].end())
                ans = min(ans, abs(now - (*t)));
            if(t != pre_b[x_par].begin())
                t --, ans = min(ans, abs(now - (*t)));
        }
        unite_clear(y_par, x_par);
    } else {
        for(ll now : pre_b[x_par]) {
            now = now + k;
            auto t = pre_a[y_par].lower_bound(now);
            if(t != pre_a[y_par].end())
                ans = min(ans, abs((*t) - now));
            if(t != pre_a[y_par].begin())
                t --, ans = min(ans, abs((*t) - now));
        }
        unite_clear(x_par, y_par);
    }
}

int main() {
    pre[0] = 0;
    int n;
    while (~ scanf("%d %lld", &n, &k)) {
        memset(output, 0, sizeof (int) * (n + 2));
        init(n);
        for(int i = 1; i <= n; i ++) {
            scanf("%lld", &pre[i]);
            pre[i] = pre[i - 1] + pre[i];
        }
        for(int i = 1; i <= n; i ++)
            scanf("%d", &operation[i]);

        int cur = operation[n];
        par[cur] = cur; set_num[cur] = 1;
        /// a - b
        pre_a[cur].insert(pre[cur]);
        pre_b[cur].insert(pre[cur - 1]);
        ans = abs(pre[cur] - pre[cur - 1] - k);
        output[n] = ans;

        for(int i = n - 1; i >= 1; i --) {
            cur = operation[i];
            par[cur] = cur;
            set_num[cur] = 1;
            pre_a[cur].insert(pre[cur]);
            pre_b[cur].insert(pre[cur - 1]);
            ans = min(ans, abs(pre[cur] - pre[cur - 1] - k));

            if(par[cur + 1]) unite(cur, cur + 1);
            if(par[cur - 1]) unite(cur, cur - 1);

            output[i] = ans;
            if(! ans) break;
        }

        for(int i = 1; i <= n; i ++)
            printf("%lld\n", output[i]);
    }
    return 0;
}
