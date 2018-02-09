#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn = 1e5 + 5 ;

ll arr[maxn] ;
ll p[maxn] ;
int n ;
ll work(ll index){
    ll sum = 0 ;
    for(int i = 0 ; i < n ; i ++){
        p[i] = arr[i] % index ;
        sum += p[i] ;
    }
    ///if(sum % index) return -1 ; with this will wrong answer 
    sort(p , p + n) ;
    ll value = 0 ;
    for(int i = n - 1 ; i >= 0 ; i --){
        if(!p[i]) continue ; 
        value += (index - p[i]) ;
        sum -= index ;
        if(sum <= 0) break ;
    }
    return value ;
}

int main(){
    int kase ; scanf("%d" , &kase) ;

    while(kase --){
        scanf("%d" , &n);
        ll sum = 0 ;
        for(int i = 0 ; i < n ; i ++){
            scanf("%lld" , &arr[i]) ;
            sum += arr[i] ;
        }
        ll ans = 1e18 ;
        for(ll i = 2 ; i*i <= sum ; i ++){
            if((sum % i)) continue ;
            ll a = work(i) ;
            //if(a >= 0)
                ans = min(ans , a) ;
            ///very important to small the sum , without will time exceed 只要求质因数就行了，且质因数最小
            while(sum % i == 0) sum /= i ;
        }
        if(sum != 1){
            ll a = work(sum) ;
            //if(a >= 0) 
            ans = min(ans , a) ;
        }
        printf("%lld\n" , ans) ;
    }
    return 0 ;
}
