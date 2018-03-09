/*
 * @Samaritan_infi
 */
///death[i][k] 第i类硬币在第k轮全部被移出         (1 - probability[i] ^ k) ^ num[i]
///survive[i][k] 第i类硬币在第k轮至少还有1枚硬币   1 - death[i]

#include <bits/stdc++.h>
using namespace std;
typedef long long ll ;

const int maxn = 20 ;
int save[maxn] ;
double probability[maxn] ;

double death[maxn][105] ;
double survive[maxn][105] ;


void init(){
    memset(death , 0 , sizeof death) ;
    memset(survive , 0 , sizeof survive) ;
}

double quick_pow(double x , int n) {
    double ans = 1.0 ; 
    while (n) {
        if(n & 1) ans *= x ;
        x *= x ;
        n >>= 1 ;
    }
    return ans ; 
}


int main(){
    int kase ;
    scanf("%d" , &kase) ;
    while (kase --) {
        int n ; scanf("%d" , &n) ;
        for(int i = 1 ; i <= n ; i ++ ){
            scanf("%d %lf" , &save[i] , &probability[i]) ;
        }
        if(n == 1) {
            puts("1.000000") ; 
            continue ; 
        }
        init() ;

        for(int i = 1 ; i <= n ; i ++) {
            for(int k = 1 ; k <= 100 ; k ++ ) {
                death[i][k] = quick_pow((1 - quick_pow(probability[i] , k) ) , save[i]) ;
                survive[i][k] = 1 - death[i][k] ;
            }
        }

        double ans = 0 , temp ;
        for(int i = 1 ; i <= n ; i ++) {
            ans = 0 ;
            for(int k = 1 ; k <= 100 ; k ++) {
                temp = 1.0 ;
                for(int j = 1 ; j <= n ; j ++ ) {
                    if(j != i)
                        temp *= death[j][k] ;
                }
                temp *= (survive[i][k] - survive[i][k + 1]) ;
                ans += temp ;
            }
            printf("%.6f%c" , ans , i == n ? '\n' : ' ') ;
        }
    }
    return 0;
}
