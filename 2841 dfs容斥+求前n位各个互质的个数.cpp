/*
 * @Samaritan_infi
 */
///求前n个数中每个数在1-m范围内和他互质数的个数，范围1e5

#include <bits/stdc++.h>
using namespace std;
typedef long long ll ;


const int mod = 1e9 + 7 ;
const int maxn = 1e5 + 5 ;
int prime[maxn][20] , prime_pos ;
int cnt[maxn] = {0} ;
///筛法求前n项质因数
void init() {
    for(int i = 2 ; i <= 1e5 ; i ++) {
        if(cnt[i]) continue ;
        prime[i][0] = i ;
        cnt[i] = 1 ;
        for(int j = 2 ; j*i <= 1e5 ; j ++)
            prime[i * j][cnt[i * j] ++] = i ;
    }
}

ll dfs(int origin , int upper_limit , int pos) {
    ll ans = 0 ;
    for(int i = pos ; i < cnt[origin] ; i ++)
        ans += upper_limit / prime[origin][i] - dfs(origin , upper_limit / prime[origin][i] , i + 1) ;
    return ans ;
}

int main() {
    //inverse_2 = inverse(2 , mod) ;
    //inverse_6 = inverse(6 , mod) ;
    init() ;
    int kase ; scanf("%d" , &kase) ;
    while (kase --) {
        int n , m ;
        scanf("%d %d" , &n , &m) ;
        ll ans = n ;
        for(int i = 2 ; i <= m ; i ++) {
            ans += n - dfs(i , n , 0) ;
            //cout << ans << endl;
        }
        printf("%lld\n" , ans) ;
    }
    return 0 ;
}
