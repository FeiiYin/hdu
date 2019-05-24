/// KM match
/// total value max, change least
/// solution: edge value multiply with x, origin plus 1
/*
 * @Samaritan_infi
 */
#include<bits/stdc++.h>
//#include <cstdio>
using namespace std;
typedef long long LL;

const int N = 1e2 + 5;
const int INF = 0x3f3f3f3f;

#define PII pair<int, int>
#define fi first
#define se second
#define pb push_back

/// problem pic
int pic[N][N];
int origin[N];

/// KM match
int ex_x[N], ex_y[N];
int match_x[N], match_y[N];
int vis_x[N], vis_y[N];
int slash;
int n, m;

bool dfs (int x) {
    vis_x[x] = true;
    for (int i = 1; i <= m; ++i) {
        if (vis_y[i] || pic[x][i] == INF) {
            continue;
        }

        int ex = ex_x[x] + ex_y[i] - pic[x][i];
        if (! ex) {
            vis_y[i] = true;

            if (match_y[i] == -1 || dfs(match_y[i])) {
                match_x[x] = i;
                match_y[i] = x;
                return true;
            }

        } else if (ex > 0) {
            slash = min(slash, ex);
        }
    }
    return false;
}

int KM () {
    memset(ex_y, 0, sizeof ex_y);
    memset(match_x, -1, sizeof match_x);
    memset(match_y, -1, sizeof match_y);
    for (int i = 1; i <= n; ++i) {
        ex_x[i] = 0;
        for (int j = 1; j <= m; ++j)
            ex_x[i] = max(ex_x[i], pic[i][j]);
    }
    /// work
    for (int i = 1; i <= n; ++i) {
        while (true) {
            memset(vis_x, 0, sizeof vis_x);
            memset(vis_y, 0, sizeof vis_y);
            slash = INF;

            if (dfs(i)) {
                break;
            }

            for (int j = 1; j <= n; ++j)
                if (vis_x[j])
                    ex_x[j] -= slash;
            for (int j = 1; j <= m; ++j)
                if (vis_y[j])
                    ex_y[j] += slash;

//            for (int j = 1; j <= n; ++j)
//                cout << ex_x[j] << " "; cout << endl;
//            for (int j = 1; j <= m; ++j)
//                cout << ex_y[j] << " "; cout << endl;
        }
    }
    int ans = 0;
    for (int i = 1; i <= n; ++i) {
        ans += pic[i][ match_x[i] ];
    }
    return ans;
}



int main () {
    while (~ scanf("%d %d", &n, &m)) {
        const int block = m + 1;

        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= m; ++j) {
                scanf("%d", &pic[i][j]);
                /// to make change least
                pic[i][j] *= block;
            }
        }
        int origin_val = 0;
        for (int i = 1; i <= n; ++i) {
            scanf("%d", &origin[i]);
            origin_val += pic[i][ origin[i] ] / block;
            /// to make change least
            pic[i][ origin[i] ]++;
        }
        int km = KM();
        // printf("%d %d\n", origin_val, km);
        int dif = km / block - origin_val;
        int change_num = n - km % block;
        printf("%d %d\n", change_num, dif);
    }
    return 0;
}
