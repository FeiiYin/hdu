#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
const int N = 1e3 + 5;
const int mod = 1e9 + 7;

char s[N]; int num[N];
LL dp[N][15][3];
/// 当前位置， 递增/非递增状态，前一个数，是否上限
LL dfs (int pos, int status, int pre, int limit) {
    if (pos < 1) return 1;
    if (! limit && dp[pos][pre][status] != -1)
        return dp[pos][pre][status];
    int end = limit ? num[pos] : 9;
    LL ans = 0;
    if (status) {
        for (int i = pre; i <= end; ++i) {
            ans += dfs(pos-1, status, i, limit && i == end);
            ans %= mod;
        }
    } else {
        for (int i = 0; i <= end; ++i) {
            /// 1 递增，0 非递增
            if (i > pre) {
                ans += dfs(pos-1, 1, i, limit && i == end);
                ans %= mod;
            } else {
                if (! i && pre == 10)
                    ans += dfs(pos-1, 0, 10, limit && i == end);
                else
                    ans += dfs(pos-1, 0, i, limit && i == end);
                ans %= mod;
            }
        }
    }
    if (! limit) dp[pos][pre][status] = ans;
    return ans;
}

LL solve () {
    int len = strlen(s);
    for (int i = 0; i < len; ++i) num[len-i] = s[i] - '0';
    return dfs(len, 0, 10, 1);
}

int main () {
    memset(dp, -1, sizeof dp);
    int kase; scanf("%d", &kase); while (kase--) {
        scanf("%s", s);
        printf("%lld\n", solve() - 1);
    }
    return 0;
}
