/**
`* @Samaritan
 */
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
#define PII pair<int, int>
#define mp make_pair
#define pb push_back
#define INF 0x3f3f3f3f
#define fi  first
#define se second

const int N = 105;
double dp[N];
int dis[N];

int main(){
    int len;
    while (~ scanf("%d", &len)) {
        int n, c, t; scanf("%d %d %d", &n, &c, &t);
        int v, vg1, vg2; scanf("%d %d %d", &v, &vg1, &vg2);
        for (int i = 1; i <= n; ++i) scanf("%d", &dis[i]);
        dis[0] = 0;
        n++;
        dis[n] = len;
        if (vg2 >= vg1) {
            double ans = len * 1.0 / vg2;
            double rabbit = len * 1.0 / v;

            if (ans < rabbit) puts("What a pity rabbit!");
            else puts("Good job,rabbit!");
            continue;
        }

        dp[0] = 0.0;
        for (int i = 1; i <= n; ++i) {
            double ans = 1e9;
            for (int j = 0; j < i; ++j) {
                double dif = dis[i] - dis[j];
                //cout << dif << endl;
                double now_t = 0;
                if (dif <= c)
                    now_t = dp[j] + dif*1.0 / vg1;
                else
                    now_t = dp[j] + c *1.0 / vg1 + (dif-c)*1.0/vg2;
//                cout << j << endl;
//                cout << dp[j] << endl;
//                cout << now_t << endl;
                if (j) now_t += t;
                ans = min(ans, now_t);

            }
            dp[i] = ans;
        }
//        for (int i = 0; i <= n; ++i)
//            printf("%.5f\n", dp[i]);

        double ans = dp[n];
        double rabbit = len * 1.0 / v;
        //printf("%.5f %.5f\n", dp[n][0], rabbit);

        if (ans < rabbit) puts("What a pity rabbit!");
        else puts("Good job,rabbit!");


        /// dp i,   reach the i th point takes time
        /// dp i,0, dp i+1,0
        ///.dp[i+1][0] = dp[i][0] + (dis[i+1]-dis[i]) / v
//
//        for (int i = 0; i <= n; ++i) for (int j = 0; j < 2; ++j) {
//            dp[i][j] = 1000000.0;
//            to[i][j] = 0;
//        }
//
//
//        dp[0][0] = dp[0][1] = 0;
//        to[0][0] = to[0][1] = c;
//
//        for (int i = 0; i < n; ++i) {
//            double dif = dis[i+1]-dis[i];
//            for (int j = 0; j < 2; ++j) {
//
//                if (dif <= to[i][j]) {
//                    if (dp[i+1][0] >= dp[i][j] + dif/vg1) {
//                        dp[i+1][0] = dp[i][j] + dif/vg1;
//                        to[i+1][0] = max(to[i+1][0], to[i][j]-dif);
//                    }
//                    if (dp[i+1][1] >= dp[i][j] + dif/vg1 + t) {
//                        dp[i+1][1] = dp[i][j] + dif/vg1 + t;
//                        to[i+1][1] = c;
//                    }
//                }
//                else {
//                    if (dp[i+1][0] >= dp[i][j] + to[i][j]/vg1 + (dif-to[i][j])/vg2) {
//                        dp[i+1][0] = dp[i][j] + to[i][j]/vg1 + (dif-to[i][j])/vg2;
//                        to[i+1][0] = max(to[i+1][0], 0.0);
//                    }
//                    if (dp[i+1][1] >= dp[i][j] + to[i][j]/vg1 + (dif-to[i][j])/vg2 + t) {
//                        dp[i+1][1] = dp[i][j] + to[i][j]/vg1 + (dif-to[i][j])/vg2 + t;
//                        to[i+1][1] = c;
//                    }
//                }
//
//            }
//        }
//        //for (int i = 0; i <= n; ++i) cout << dp[i][0] << " " << dp[i][1] << endl;
//
//        double ans = dp[n][0];
//        double rabbit = len * 1.0 / v;
//        //printf("%.5f %.5f\n", dp[n][0], rabbit);
//
//        if (ans < rabbit) puts("What a pity rabbit!");
//        else puts("Good job,rabbit!");
    }
    return 0;
}
