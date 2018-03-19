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
ll inverse_2 , inverse_5 , inverse_6 ;

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


/// cal SUM(i*i*i*i)
ll cal(ll n) {
    ll a = (n + 1) * (n + 1) % mod * (n + 1) % mod * (n + 1) % mod * (n + 1) % mod ;
    a = ((a - 1 - n) * inverse_5 % mod + mod ) % mod ;
    ll b = n * n % mod * (n + 1) % mod * (n + 1) % mod * inverse_2 % mod ;
    ll c = 2 * n * (n + 1) % mod * (2 * n + 1) % mod * inverse_6 % mod ;
    ll d = n * (n + 1) % mod * inverse_2 % mod ;
    return ((a - b - c - d) % mod + mod ) % mod ;
}

int work(ll n) {
    ll sum = 0 , sum2 = 0 ;
    for(int i = 1 ; i < (1 << prime_pos) ; i ++) {
        int bits = 0 ; ll now = 1 ;
        for(int j = 0 ; j < prime_pos ; j ++) {
            if(i & (1 << j)) {
                bits ++ ;
                now *= prime[j] ;
            }
        }
        ll num = n / now ;
        ll temp = now * now % mod * now % mod * now % mod ;
        temp = temp * cal(num) % mod ;

        if(bits & 1) sum = (sum + temp) % mod ;
        else         sum = (sum - temp) % mod ;
    }

    return (cal(n) - sum + mod) % mod ;
}

int main() {

    inverse_2 = inverse(2 , mod) ;
    inverse_5 = inverse(5 , mod) ;
    inverse_6 = inverse(6 , mod) ;

    int kase ; scanf("%d" , &kase) ;
    while (kase -- ) {
        int n ; scanf("%d" , &n) ;
        decompose(n) ;
        printf("%d\n" , work(n)) ;
    }
    return 0 ;
}
  
