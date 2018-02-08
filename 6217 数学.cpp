//金牌题目
//思路，计算第n位，将数乘上进制的n-1次方，求此时的第一个小数，此时取公式中每个数的小数部分，注意要逼近无穷，然后再乘上进制，此时的整数部分即位所求
#include <bits/stdc++.h>
using namespace std ;
typedef long long ll ;

const int maxn = 1e5 + 5 ;

ll quick_pow(ll a , ll n , ll mod){
    ll ans = 1 , base = a ;
    while(n){
        if(n & 1) ans = ans * base % mod ;
        n >>= 1 ;
        base = base * base % mod ;
    }
    return ans ;
}


int n ;
double work(int index){
    double ans = 0 ;
    for(int i = 0 ; i <= n ; i ++){
        ans += quick_pow(16 , n - i , 8 * i + index) * 1.0 / (8 * i + index) ;
    }
    ans -= (int) ans ;
    ///计算趋向无限的部分，此时指数为负数
    for(int i = n + 1 ; i <= n + 1000 ; i ++){
        ans += powf(16 , n - i) * 1.0 / (8 * i + index) ;
    }
    return ans ;
}



int main(){
    int kase ; scanf("%d" , &kase) ;
    int tt = 1 ;
    while(kase --){
        scanf("%d" , &n) ;
        n -- ;
        double ans = 4 * work(1) - 2 * work(4) - work(5) - work(6) ;

        ans -= (int) ans ;
        if(ans < 0) ans += 1 ;
        int out = (int)(ans * 16) ;
        //cout << out << endl  ;
        printf("Case #%d: %d " , tt ++ , n + 1) ; 
        if(out >= 0 && out <= 9) printf("%d\n" , out) ;
        else printf("%c\n" , 'A' + out - 10 ) ;
    }
    return 0 ;
}
