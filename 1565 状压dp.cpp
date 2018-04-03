/*
 * @Samaritan_infi
 */
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

const int maxn = 2e4 + 5;
const int mod = 100000007;

int dp[30][maxn];
int pic[30][30];
int state[maxn], state_pos;
int val[30][maxn];

void init(int n) {
    state_pos = 0;
    for(int i = 0; i < (1 << n); i ++) {
        if(i & (i << 1)) continue;
        state[state_pos ++] = i;
    }
    //for(int i = 0; i < state_pos; i ++) cout << state[i] << " "; cout << endl;
    memset(val, 0, sizeof val);
    for(int i = 1; i <= n; i ++) {
        for(int j = 0; j < state_pos; j ++) {
            int num = state[j];
            int pos = 1;
            while(num) {
                if(num & 1) val[i][j] += pic[i][pos];
                num >>= 1, pos ++;
            }
        }
    }
    memset(dp, 0, sizeof dp);
    for(int i = 0; i < state_pos ; i ++)
        dp[1][i] = val[1][i];
}

int main() {
    int n;
    while(~ scanf("%d", &n)) {
        memset(dp, 0, sizeof dp);
        for(int i = 1; i <= n; i ++) {
            for(int j = 1; j <= n; j ++) {
                scanf("%d", &pic[i][j]);
            }
        }
        init(n);
        for(int i = 2; i <= n; i ++) {
            for(int j = 0; j < state_pos; j ++) {
                for(int k = 0; k < state_pos; k ++) {
                    if(state[j] & state[k]) continue;
                    dp[i][j] = max(dp[i][j], dp[i - 1][k] + val[i][j]);
                }
            }
        }
//        for(int i = 1; i <= n; i ++) {
//            for(int j = 0; j < state_pos; j ++)
//                cout << dp[i][j] << " ";cout << endl;
//        }
        int ans = 0;
        for(int i = 0; i < state_pos; i ++) ans = max(ans, dp[n][i]);
        printf("%d\n", ans);
    }
    return 0;
}

