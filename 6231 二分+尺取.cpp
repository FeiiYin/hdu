/*
 * @Samaritan_infi
 */
 ///将答案进行二分
 ///判断，如果一个区间大于x的数大于等于k，则s ++ ，如果s大于等于m，则成立。
 ///利用尺取判断
#include <bits/stdc++.h>
using namespace std ;
typedef long long ll ;

const int maxn = 1e5 + 5 ;

int a[maxn] ;

int n , k ;
ll m ;
bool check(int val){
    int l = 0 , r = 0;
    ll ans = 0 ;
    int s = 0 ;
    for(int r = 0 ; r < n ; r ++){
        if(a[r] >= val) s ++ ;
        if(s == k){
            ans += n - r ;
            while(a[l] < val){
                ans += n - r ;
                l ++ ;
            }
            s -- ; l ++ ;
        }
    }
    //cout << val << " "<< ans << " " <<  m << endl ;
    return ans >= m ;
}

int main(){
    int kase ; scanf("%d" , &kase) ;
    while(kase --){
        scanf("%d %d %lld" , &n , &k , &m) ;
        for(int i = 0 ; i < n ; i ++){
            scanf("%d" , &a[i]) ;
        }
        int l = 1 , r = 1e9 + 1 ;
        while(l < r){
            int mid = (l + r) >> 1 ;
            if(check(mid)) l = mid + 1 ;
            else r = mid ;
        }
        cout << l - 1 << endl ;
    }
    return 0 ;
}
