/*
 * @Samaritan_infi
 */
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

const int maxn = 10005;
const int mod = 1e9 + 7;
int digit[12], len;
int dp[20][15][5];

void get_num(int n) {
    len = 0;
    while(n) {
        digit[ ++ len] = n % 10;
        n /= 10;
    }
}

///top 第几位数，remain 余数，state 状态，主要指前一位。flag表示计算的是不是完整的top位数。
///如 n=111 时，我们计算的三位数不是完整的三位数，有一个上界111，所以不能用dp中储存的数据。
int dfs(int top, int remain, int state, bool flag) {
    if(! top) return remain == 0 && state == 2;

    if(! flag && dp[top][remain][state] != -1)
        return dp[top][remain][state];
    int max_digit = (flag) ? digit[top] : 9;
    int ans = 0;
    for(int i = 0; i <= max_digit; i ++) {
        int now_remain = (remain * 10 + i) % 13, now_state = state;

        if(state == 0 && i == 1) now_state = 1;
        if(state == 1 && i != 1) now_state = 0;
        if(state == 1 && i == 3) now_state = 2;
        ans += dfs(top - 1, now_remain, now_state, flag && i == max_digit);
    }
    if(! flag) dp[top][remain][state] = ans;
    return ans;
}
int main() {
    int n;
    memset(dp, -1, sizeof dp);
    while( ~ scanf("%d", &n)) {
        get_num(n);
        printf("%d\n", dfs(len, 0, 0, 1) % mod);
    }
    return 0;
}
