/**
 * @Samaritan
 */
#include <bits/stdc++.h>
using namespace std;
#define PII pair<int, int>
#define fi first
#define se second

const int N = 2e3 + 5;
const int M = 20;
const int INF = 0x7fffffff;

int dp[N][M];
PII stone[M];
int main ()
{
    int n, m;
    while (~ scanf("%d %d", &n, &m)) {
        memset(dp, 0, sizeof dp);

        int point = 0, t;
        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= m; ++j) {
                scanf("%d", &t);
                if (t)
                    stone[point++] = {i, j};
            }
        }

        int tot_status = (1 << point);
        for (int status = 0; status < tot_status; ++status) {
            for (int i = 0; i < point; ++i) {
                if (! ((1<<i) & status)) continue;
                if ((1<<i) == status) {
                    dp[status][i] = stone[i].fi + stone[i].se - 2;
                    continue;
                }
                dp[status][i] = INF;
                for (int j = 0; j < point; ++j)
                    if ((status & (1<<j)) && i != j) {
                        dp[status][i] = min(dp[status][i],
                        dp[status ^ (1<<i)][j] + abs(stone[i].fi - stone[j].fi) + abs(stone[i].se - stone[j].se));
                    }
            }
        }

        int ans = INF;
        if (! point) ans = 0;
        for (int i = 0; i < point; ++i)
            ans = min(ans, dp[tot_status-1][i] + stone[i].fi + stone[i].se - 2);
            // , cout << dp[tot_status-1][i] << endl;
        printf("%d\n", ans);
    }
    return 0;
}

