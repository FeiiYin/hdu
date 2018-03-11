/*
 * @Samaritan_infi
 */
 ///注意斜率优化的第二个不等号是大于号，注意斜率优化第二个判断中乘开分母可能会爆long long
 ///树上dp由于有不同的线路产生不同的前缀和，所以要对操作进行存储与回溯，存储的stack在函数内声明会比较方便
 
#include <bits/stdc++.h>
using namespace std;
typedef long long ll ;

const int maxn = 1e5 + 5 ;


vector<pair<int , int> > edge[maxn] ;

void add_edge(int l , int r , int v) {
    edge[l].push_back(make_pair(r , v)) ;
    edge[r].push_back(make_pair(l , v)) ;
}

/// dp[i] = dp[j] + p + (pre[i] - pre[j]) ^ 2 ;
ll check_time ;
ll pre[maxn] ;
ll dp[maxn] ;
ll que[maxn] ;
ll ans ;

int head , tail ;
ll get_dp(int i , int j) {
    return dp[j] + check_time + (pre[i] - pre[j]) * (pre[i] - pre[j]) ;
}
ll get_up(int k , int j) {
    return (dp[j] + pre[j] * pre[j]) - (dp[k] + pre[k] * pre[k]) ;
}
ll get_down(int k , int j) {
    return (ll)2 * (pre[j] - pre[k]) ;
}



void init(int n) {
    for(int i = 1 ; i <= n ; i ++) edge[i].clear() ;
    pre[1] = 0 ;
    head = 0 , tail = 1 ;
    ans = -10000 ;
}

double get_slope(int k , int j) {
    return (double) (get_up(k , j)) * 1.0 / (get_down(k , j)) ;
}

void dfs(int u , int par , int val) {
    pre[u] = pre[par] + (ll)val ;
    stack< pair<int , int> > operation ;
    /// (1 , x) pop head x
    /// (2 , x) pop tail x
    /// (3 , x) insert tail x
    if(u != 1) {
        while(head + 1 < tail && get_up(que[head] , que[head + 1]) <= pre[u] * get_down(que[head] , que[head + 1]))
            operation.push(make_pair(1 , que[head ++])) ;
        dp[u] = get_dp(u , que[head]) ;
        ans = max(ans , dp[u]) ;
        /// 这里不能将两个分母乘开来，否则会爆ll
        while(head + 1 < tail && get_slope(que[tail - 2] , que[tail - 1])
              >= get_slope(que[tail - 1] , u) )
            operation.push(make_pair(2 , que[tail --])) ;
    }

    que[tail ++] = u ;
    operation.push(make_pair(3 , que[tail - 1])) ;

    for(int i = 0 ; i < edge[u].size() ; i ++ ) {
        int v = edge[u][i].first ;
        if(v == par) continue ;
        int now = edge[u][i].second ;
        dfs(v , u , now) ;
    }

    while(! operation.empty()) {
        int op = operation.top().first ;
        int pos = operation.top().second ;
        operation.pop() ;

        if(op == 1) {
            que[-- head] = pos ;
        } else if(op == 2) {
            que[tail ++] = pos ;
        } else {
            tail -- ;
        }
    }
}
void show(int n ) {
    for(int i = 1 ; i <= n ; i ++) cout << dp[i] << " " ; cout << endl ;
}
int main(){
    int kase ; scanf("%d" , &kase) ;
    while (kase --) {
        int n ;
        scanf("%d %lld" , &n , &check_time) ;
        init(n) ;
        int l , r , v ;
        for(int i = 1 ; i < n ; i ++ ) {
            scanf("%d %d %d" , &l , &r , &v) ;
            add_edge(l , r , v) ;
        }
        dfs(1 , 0 , 0) ;
        //show(n) ;
        printf("%lld\n" , ans - check_time) ;
    }
    return 0;
}
