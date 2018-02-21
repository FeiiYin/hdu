///F[x] = gcd(i , j) == (x的倍数)
///f[x] = gcd(i , j) == x
///F[x] = (m / x) * (n / x)
///去重，去掉区间相同部分的一半
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn = 1e5 + 5 ;

bool vis[maxn] ;
int prime[maxn] , mu[maxn] ; 

void Mobius(){
    memset(prime , 0 , sizeof(prime)) ;
    memset(mu , 0 , sizeof(mu)) ;
    memset(vis , 0 , sizeof(vis)) ;
    mu[1] = 1 ;
    int cnt = 0 ;
    for(int i = 2 ; i < maxn ; i ++){
        if(! vis[i]){
            prime[cnt ++] = i ;
            mu[i] = -1 ;
        }
        for(int j = 0 ; j < cnt && i * prime[j] < maxn ; j ++){
            vis[i * prime[j]] = 1 ;
            if(i % prime[j]) mu[i * prime[j]] = - mu[i] ;
            else{
                mu[i * prime[j]] = 0 ;
                break ; 
            }
        }
    }
}


int a , b , c , d , k ;
ll work(){
    if(k == 0) return 0 ; 
    b /= k ; d /= k ;
    ll ans1 = 0 , ans2 = 0 ;
    for(int i = 1 ; i <= min(b , d) ; i ++){
        ans1 += (ll)mu[i] * (b/i) * (d/i) ;
    }
    b = min(b , d) ;
    for(int i = 1 ; i <= b ; i ++){
        ans2 += (ll)mu[i] * (b / i) * (b / i) ;
    }
    return ans1 - ans2 / 2 ;
}

int main(){
    int kase ; scanf("%d" , &kase) ;
    int tt = 1 ; 
    Mobius() ;
    while(kase --){
        scanf("%d %d %d %d %d" , &a , &b , &c , &d , &k) ;
        printf("Case %d: %lld\n" , tt ++ , work()) ; 
    }
    return 0 ; 
}
