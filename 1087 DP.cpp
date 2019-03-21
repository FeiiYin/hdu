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

const int N = 1e3 + 5;
LL arr[N];

int stk[N];
int lis (int ar[], int n) {
    int l = 0, r = 1; /// stk[r] = null
    stk[l] = ar[1];
    for (int i = 2; i <= n; ++i) {
        int pos = upper_bound(stk, stk + r, ar[i]) - stk;
        stk[pos] = ar[i];
        if (pos == r) r++;
    }
    return r;
}

LL dp[N];

int main(){
    int n;
    while (~ scanf("%d", &n)) {
        if (! n) break;
        for (int i = 1; i <= n; ++i) scanf("%lld", &arr[i]);
        //dp[1] = arr[1];
        LL ans = 0;
        for (int i = 1; i <= n; ++i) {
            dp[i] = arr[i];
            for (int j = 1; j < i; ++j) if (arr[i] > arr[j]) {
                dp[i] = max(dp[i], dp[j] + arr[i]);
            }
            ans = max(ans, dp[i]);
        }

        printf("%d\n", ans);
    }
    return 0;
}
