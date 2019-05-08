/**
 * @Samaritan
 */
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;

const int N = 1e3 + 5;
const int INF = 0x3f3f3f3f;

int num[N][N];

int main () {
    int m, n, x, y;
    int kase;
    scanf("%d", &kase);
    while (kase--) {
    // while (~ scanf("%d", &n)) {
        scanf("%d %d %d %d", &m, &n, &x, &y);

        for (int i = 1; i <= m; ++i)
            for (int j = 1; j <= n; ++j)
                scanf("%d", &num[i][j]);

        for (int i = 1; i <= m; ++i)
            for (int j = 2; j <= n; ++j)
                num[i][j] += num[i][j-1];

        for (int i = 2; i <= m; ++i)
            for (int j = 1; j <= n; ++j)
                num[i][j] += num[i-1][j];

        int ans = -INF;
        int tmp;
        for (int i = x; i <= m; ++i)
            for (int j = y; j <= n; ++j) {
                tmp = num[i][j] - num[i - x][j] - num[i][j - y] + num[i - x][j - y];
                if (tmp > ans)
                    ans = tmp;
            }
        printf("%d\n", ans);
    }
    return 0;
}

