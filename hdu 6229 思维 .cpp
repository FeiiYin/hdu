#include <bits/stdc++.h>
using namespace std ;
#define MP make_pair

typedef long long ll ;
const int maxn = 1e4 + 5 ;

map< pair<int , int> , int > mp ;
int n ;

int value(int i , int j){
    if((i == 0 && j == 0) || (i == n - 1 && j == n - 1) ||
       (i == 0 && j == n - 1) || (i == n - 1 && j == 0)) return 3 ;
    if(i == 0 || i == n - 1 || j == 0 || j == n - 1)    return 4 ;
    return 5 ;
}

int dx[] = { 0 , 0 , -1 , 1} ;
int dy[] = {-1 , 1 ,  0 , 0} ;

ll gcd(ll a , ll b){
    return b == 0 ? a : gcd(b, a % b);
}
int main(){
    int kase ; scanf("%d" , &kase) ;
    int m , l , r ;
    int tt = 1 ;
    while(kase --){
        scanf("%d %d" , &n , &m) ;

        mp.clear() ;
        while(m --){
            scanf("%d %d" , &l , &r) ;
            mp[ MP(l , r) ] = value(l , r);
            for(int k = 0 ; k < 4 ; k ++){
                int a = l + dx[k] , b = r + dy[k] ;
                if(a >= 0 && b >= 0 && a <= n - 1 && b <= n - 1){
                    mp[ MP(a , b) ] ++ ;
                    mp[ MP(a , b) ] = min(mp[ MP(a , b) ] , value(a , b) ) ;
                }

            }
        }

        ll sum = n * (n + 1) / 2 * 5 - 3 * 2 - 2 * (n - 2) ;
        ll total = n * n * 5 - 4 * 2 - 4 * (n - 2) ;

        //cout << sum << " " << total << endl ;

        for(auto a : mp){
            int i = a.first.first , j = a.first.second ;
            int t = a.second ;

            if(i + j >= n - 1) sum -= (ll)t ;
            total -= (ll)t ;
            //cout << sum << " " << total << endl ;
        }

        ll g = gcd(sum , total) ;
        sum /= g , total /= g ;

        printf("Case #%d: %lld/%lld\n" ,tt++ , sum , total) ;
    }
    return 0 ;
}
