/*
 * @Samaritan_infi
 */
#include <bits/stdc++.h>
using namespace std;
typedef long long ll ;


const int mod = 1e9 + 7 ;
int prime[20] , prime_pos ;

void ex_gcd(ll a , ll b , ll &d, ll &x, ll &y) {
    if(! b) {d = a; x = 1; y = 0; }
    else {
        ex_gcd(b , a % b, d, y, x);
        y -= x * (a / b);
    }
}
ll inverse(ll a , ll n) {
    ll d, x, y;
    ex_gcd(a, n, d, x, y);
    return d == 1 ? (x + n) % n : -1 ;
}

int gcd(int x , int y){
    return x % y == 0 ? y : gcd(y , x % y) ;
}


ll inverse_2 , inverse_6 ;

void decompose(ll n) {
    prime_pos = 0 ;
    for(ll i = 2 ; i * i <= n ; i ++) {
        if(!(n % i)) {
            prime[prime_pos ++] = i ;
            while(!(n % i)) n /= i ;
        }
    }
    if(n > 1) prime[prime_pos ++] = n ;
}

///n * (n + 1) * (2 * n + 1) / 6
int work(ll n) {
    ll sum1 = 0 , sum2 = 0 ;
    for(int i = 1 ; i < (1 << prime_pos) ; i ++) {
        int bits = 0 ; ll now = 1 ;
        for(int j = 0 ; j < prime_pos ; j ++) {
            if(i & (1 << j)) {
                bits ++ ;
                now = now * prime[j] / gcd(now , prime[j]);
                ///这里要用最小公倍数，因为输入的m不一定是质数
            }
        }
        ll r = (n - 1) / now ;
        if(bits & 1) sum1 += r ;
        else         sum1 -= r ;
    }

    return sum1 ;
}

int main() {
    //inverse_2 = inverse(2 , mod) ;
    //inverse_6 = inverse(6 , mod) ;

    int n , m ;
    while(~ scanf("%d %d" , &n , &m)) {
        prime_pos = 0 ;
        while(m --) {
            scanf("%d" , &prime[prime_pos ++]) ;
            if(!prime[prime_pos - 1])
            { prime_pos -- ; continue ;}


        }
        if(prime_pos == 0) {
            cout << n - 1 << endl ; continue ;
        }
        printf("%d\n" , work(n)) ;
    }
    return 0 ;
}
