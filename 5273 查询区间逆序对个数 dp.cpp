/*
 * @Samaritan_infi
 */
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;

const int N = 1e2 + 5;

int dp[N][N], arr[N];

int main () {
    int kase; scanf("%d", &kase);
    while (kase --) {
        int n; scanf("%d", &n);
        for (int i = 1; i <= n; i ++) scanf("%d", &arr[i]);
        memset(dp, 0, sizeof dp);
        for (int i = 1; i <= n; i ++) {
            for (int j = 1; j < i; j ++) if (arr[j] > arr[i])
                dp[1][i] ++;
            dp[1][i] += dp[1][i - 1];
        }

        for (int i = 2; i <= n; i ++) {
            int ans = 0;
            for (int j = i; j <= n; j ++) {
                if (arr[i - 1] > arr[j]) ans --;
                dp[i][j] = dp[i - 1][j] + ans;
            }
        }
        for (int i = 1; i <= n; i ++) {
            for (int j = 1; j <= n; j ++)
                cout << dp[i][j] << " ";
            cout << endl;
        }
    }
    return 0;
}
