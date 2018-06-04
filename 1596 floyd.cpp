/*
 * @Samaritan_infi
 */
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

const int maxn = 1050;
double dis[maxn][maxn];

void floyd(int n) {
    for(int k = 1; k <= n; k ++) {
        for(int i = 1; i <= n; i ++) {
            for(int j = 1; j <= n; j ++) {
                dis[i][j] = max(dis[i][j], dis[i][k] * dis[k][j]);
            }
        }
    }
}

int main() {
    int n;
    while(~ scanf("%d", &n)) {
        for(int i = 1; i <= n; i ++) {
            for(int j = 1; j <= n; j ++) {
                scanf("%lf", &dis[i][j]);
            }
        }
        floyd(n);
        int op, l, r; scanf("%d", &op);
        while(op --) {
            scanf("%d %d", &l, &r);
            if(dis[l][r] < 1e-9) printf("What a pity!\n");
            else
            printf("%.3f\n", dis[l][r]);
        }
    }
    return 0;
}
