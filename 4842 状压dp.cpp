#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
int stone[101], L, S, T, M, dp[2100], mpt[2100];
int main(){
    int i, j, l, k, ptr = 0, minn;
    cin >> L >> S >> T >> M;
    for (i = 1; i <= M; i++)
        scanf("%d", &stone[i]);
    memset(mpt, 0, sizeof(mpt));
    memset(dp, 0, sizeof(dp));
    sort(stone + 1, stone + 1 + M);
    stone[0] = ptr = 0;
    for (i = 1; i <= M; i++){
        l = stone[i] - stone[i - 1];
        if (!(l % T)) k = T;
        else k = l % T;
        k = k + T;
        k = min(k, l);
        ptr = ptr + k;
        mpt[ptr] = 1;
    }
    for (i = 1; i <= ptr + T; i++){
        minn = 0x7ffffff;
        for (j = i - T; j <= i - S; j++)
        if (j >= 0 && dp[j] < minn)
            minn = dp[j];
        dp[i] = minn + mpt[i];
    }
    minn = 0x7ffffff;
    for (i = ptr + 1; i <= ptr + T; i++)
        minn = min(minn, dp[i]);
    printf("%d\n", minn);
    return 0;
}
