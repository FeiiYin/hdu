/*
 * @Samaritan_infi
 */
 
#include <bits/stdc++.h>
using namespace std;
typedef long long ll ;

const int maxn = 500000 + 5 ;

int sum[maxn] ;
int dp[maxn] ;
///dp[i] = min(dp[i] , dp[j] + m + (sum() ^ 2))
int que[maxn] ;
int n , m ;
int get_dp(int i , int j) {
    return dp[j] + m + (sum[i] - sum[j]) * (sum[i] - sum[j]) ;
}

///这么写会除0
double get_slope(int i , int j) { // j > i
    return ((dp[j] + sum[j] * sum[j]) - (dp[i] + sum[i] * sum[i]))
                / (2 * (sum[j] - sum[i])) ;
}
int get_up(int i , int j) {
    return ((dp[j] + sum[j] * sum[j]) - (dp[i] + sum[i] * sum[i])) ;
}
int get_down(int i , int j) {
    return (2 * (sum[j] - sum[i])) ;
}

int main(){

    while ( ~ scanf("%d %d" , &n , &m)) {
        sum[0] = dp[0] = que[0] = 0 ;
        for(int i = 1 ; i <= n ; i ++ ) {
            scanf("%d" , &sum[i]) ;
            sum[i] += sum[i - 1] ;
        }
        int head = 0 , tail = 1 ;
        memset(que , 0 , sizeof que) ;
        for(int i = 1 ; i <= n ; i ++) {
            while(head + 1 < tail &&
                  get_up(que[head], que[head + 1])
                  <= sum[i] * get_down(que[head], que[head + 1]))
                    head ++ ;
            dp[i] = get_dp(i , que[head]) ;
            while(head + 1 < tail &&
                  get_up(que[tail - 2] , que[tail - 1]) * get_down(que[tail - 1] , i)
                    >= get_up(que[tail - 1] , i) * get_down(que[tail - 2] , que[tail - 1]))
                    tail -- ;
            que[tail ++] = i ;
        }
        printf("%d\n" , dp[n]) ;

    }
    return 0;
}
