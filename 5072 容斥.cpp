/*
 * @Samaritan_infi
 */
/// 反过来处理
#include <bits/stdc++.h>
using namespace std;
typedef long long ll ;

const int maxn = 1e5 + 5 ;
int save[maxn] ;
int factor[maxn] ;
int prime[20] , prime_pos ;

/// 求出含有该因数的个数
void init(int n) {
    memset(factor , 0 , sizeof factor) ;
    for(int i = 0 ; i < n ; i ++) {
        for(int j = 1 ; j * j <= save[i] ; j ++) {
            if(!(save[i] % j)) {
                factor[j] ++ ;
                if(j * j != save[i]) factor[save[i] / j] ++ ;
            }
        }
    }
}

void decompose(int n) {
    prime_pos = 0 ;
    for(int i = 2 ; i * i <= n ; i ++) {
        if(!(n % i)) {
            prime[prime_pos ++] = i ;
            while(!(n % i)) n /= i ;
        }
    }
    if(n > 1) prime[prime_pos ++] = n ;
}
ll work(int n) {
    ll ans = 0 ;

    for(int i = 0 ; i < n ; i ++) {
        int x = save[i] ;
        if(x == 1) continue ;
        decompose(x) ;
        ll work_x = 0 ;
        for(int j = 1 ; j < (1 << prime_pos) ; j ++) {
            int sign = -1 ;
            ll now = 1 ;
            for(int k = 0 ; k < prime_pos ; k ++) {
                if(j & (1 << k)) {
                    sign *= -1 ;
                    now *= prime[k] ;
                }
            }
            //cout << sign * factor[now] << " ." ;
            work_x += sign * factor[now] ;
        }
        ans += (work_x - 1) * (n - work_x)  ;
    }
    return (ll)n * (n - 1) * (n - 2) / 6 - ans / 2;
}
int main() {
    int kase ; scanf("%d" , &kase) ;
    while (kase --) {
        int n ; scanf("%d" , &n) ;
        for(int i = 0 ; i < n ; i ++) {
            scanf("%d" , &save[i]) ;
        }
        init(n) ;
        printf("%lld\n" , work(n)) ;
    }
    return 0 ;
}
