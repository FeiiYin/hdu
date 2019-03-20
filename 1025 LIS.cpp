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

const int N = 5e5 + 5;
int arr[N];
int stk[N];
int dp[N];

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



int main(){
    int len;
    int kase = 1;
    while (~ scanf("%d", &len)) {
        int x, y;
        for (int i = 0; i < len; ++i) scanf("%d %d", &x, &y), arr[x] = y;
        int ans = lis(arr, len);
        printf("Case %d:\n", kase);
        if(ans==1)
             printf("My king, at most 1 road can be built.\n\n");
        else
             printf("My king, at most %d roads can be built.\n\n",ans);
        kase++;
    }
    return 0;
}
