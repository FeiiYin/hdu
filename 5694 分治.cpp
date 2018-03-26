/*
 * @Samaritan_infi
 */
#include <bits/stdc++.h>
using namespace std ;
typedef long long ll ;

inline ll read()
{
    ll x=0,f=1;char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
    return x*f;
}

ll dp[100][2] ; ///dp[i][0] i 的左边 dp[i][1] i的长度

void init() {
    dp[1][0] = dp[1][1] = 1 ;
    dp[2][0] = 1 ; dp[2][1] = 3 ;
    for(ll i = 3 ; i <= 70 ; i ++) {
        dp[i][0] = dp[i - 2][1] + 1;
        dp[i][1] = (dp[i - 1][1] << 1) + 1 ;
        if(dp[i][1] > 1e18) break ;
        //cout << dp[i][0] << " " << dp[i][1] << endl ;
    }
}

ll dfs(ll x) {
    if(! x) return 0 ;
    if(x == 1) return 1 ;
    int i = 1 ;
    for( ; dp[i][1] < x ; i ++) ;
    ll ans = dp[i][0] + 1 ;
    //cout << ans << endl ;
    if(x == dp[i - 1][1] + 1) return ans ;

    ll right = x - (dp[i - 1][1] + 1) ;

    ans += right - (dp[i][0] - dfs(dp[i - 1][1] - right)) ;
    return ans ;
}

int main() {
    init() ;
    int n ;  scanf("%d" , &n) ;
    while(n --) {
        ll l = read() , r = read() ;
        //cout << dfs(l - 1) << " " << dfs(r) << endl ;
        printf("%lld\n" , dfs(r) - dfs(l - 1)) ;
    }
    return 0 ;
}
