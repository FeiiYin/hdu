/*
 * @Samaritan_infi
 */
#include <bits/stdc++.h>
#define test cout << "  test  " << endl ;
using namespace std ;
typedef long long ll ;

inline ll read()
{
    ll x=0,f=1;char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
    return x*f;
}
const int maxn = 100000 + 5 ;

ll ans[maxn] , temp[maxn];
int save[maxn] ;
int n ;
void show(ll temp[]) {
for(int i = 1 ; i <= n ; i ++) cout << temp[i] << " " ; cout << endl ;
}
void work(int l , int r) {
    if(l == r) {
        ans[1] = max(ans[1] , (ll)save[l] * save[l]) ;
        return ;
    }
    if(l > r) return ;
    int smallest = 1e9 + 5 ;
    int pos = 0 ;
    for(int i = l ; i <= r ; i ++) {
        if(save[i] < smallest) {
            smallest = save[i] ;
            pos = i ;
        }
    }
    int now = 0 ;
    //memset(temp , 0 , sizeof temp) ;
    for(int i = 1 ; i <= r - l + 1 ; i ++) temp[i] = 0 ; 
    for(int i = pos - 1 ; i >= l ; i --) {
        temp[pos - i + 1]  = max(temp[pos - i + 1] , (ll)smallest * save[i]) ;
    }
    for(int i = pos + 1 ; i <= r ; i ++) {
        temp[i - pos + 1]  = max(temp[i - pos + 1] , (ll)smallest * save[i]) ;
    }
    ll biggest = 0 ;
    //show(temp) ;
    //show(ans) ;
    for(int i = 1 ; i <= r - l + 1 ; i ++) {
        biggest = max(biggest , temp[i]) ;
        ans[i] = max(biggest , ans[i]) ;
    }
    work(l , pos - 1) ;
    work(pos + 1 , r) ;
}

int main() {
    while( ~ scanf("%d" , &n)) {
        memset(ans , 0 , sizeof ans ) ;
        for(int i = 0 ; i < n ; i ++) {
            scanf("%d" , &save[i]) ;
        }
        work(0 , n - 1) ;
        for(int i = 1 ; i <= n ; i ++) printf("%lld\n" , ans[i]) ;
    }
    return 0 ;
}
