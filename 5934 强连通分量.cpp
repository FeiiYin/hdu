#include <bits/stdc++.h>

#define mod 1000000007
using namespace std ;
typedef long long ll ;
int ans[10050] ;

struct point {
    ll x , y , r , cost ;
    bool operator < ( const point & k ) const {
        return x < k.x ;
    }
};
point save[1050] ;
int par[1050] ;

int check(int x , int y){
    ll dis = (save[x].x - save[y].x)*(save[x].x - save[y].x) + (save[x].y - save[y].y)*(save[x].y - save[y].y) ;
    if(dis <= save[x].r*save[x].r) return x ;
    if(dis <= save[y].r*save[y].r) return y ;
    return -1 ;
}

const int MAX_V = 1005 ;
int V ; // point
vector <int> G[MAX_V] ;
vector <int> rG[MAX_V] ;
vector <int> vs ;///dui shou
bool used[MAX_V] ;
int cmp[MAX_V] ;

void add_edge( int from , int to ){
    G[from].push_back(to) ;
    rG[to].push_back(from) ;
}
void dfs( int v ){
    used[v] = true ;
    for( int i = 0 ; i < G[v].size() ; i ++ ){
        if( !used[ G[v][i] ])   dfs( G[v][i] ) ;
    }
    vs.push_back(v) ;
}
void rdfs( int v , int k ){
    used[v] = true ;
    cmp[v] = k ;
    for( int i = 0 ; i < rG[v].size() ; i ++ ){
        if( ! used[rG[v][i] ]) rdfs( rG[v][i] , k  );
    }
}
int scc(){
    memset(used , 0 ,sizeof( used)) ;
    vs.clear() ;
    for( int v = 1 ; v <= V ; v ++ ){
        if( !used[v]) dfs(v) ;
    }
    memset( used , 0 ,sizeof( used )) ;
    int k = 0  ;
    for( int i = vs.size() - 1 ; i >= 0 ; i -- ){
        if( ! used[ vs[i] ]) rdfs( vs[i] , k ++ ) ;
    }
    return k ;
}
map<int , ll> val ;
int deg[1050] ;
int main(){
    int T ; scanf("%d" , &T) ;
    int n , k ;
    int kk = 1 ;
    while(T --){
        scanf("%d" , &n) ;
        for( int i = 0 ; i <= n ; i ++ ) {
            G[i].clear() , rG[i].clear() ;
        }memset(cmp , 0 , sizeof( cmp)) ;
        V = n ;

        point tt ;
        for(int i = 1 ; i <= n ; i ++ ){
            scanf("%lld %lld %lld %lld" , &save[i].x , &save[i].y , &save[i].r , &save[i].cost) ;
        }

        for(int i = 1 ; i <= n ; i ++ ){
            for(int j = 1 ; j <= n ; j ++ ){
                if(i == j) continue ;
                if(check(i , j) == i){
                    add_edge(i , j) ;
                }else if(check(i , j) == j )
                    add_edge(j , i) ;
            }
        }
        int ans = scc() ;
        //cout << ans << endl ;
        val.clear() ;
        for(int i = 1 ; i <= n ; i ++ ){
            if(val.count(cmp[i]))
                val[ cmp[i] ] = min(val[ cmp[i] ] , save[i].cost) ;
            else
                val[ cmp[i] ] = save[i].cost ;
        }// cout << cmp[i ] << " " ;
        memset(deg , 0 , sizeof(deg)) ;
        for(int i = 1 ; i <= n ; i ++ ){
            for(int j = 0 ; j < G[i].size() ; j ++ ){
                //cout << i << " " << G[i][j] << endl ;
                if(cmp[ G[i][j] ] != cmp[i]){
                    deg[ cmp[ G[i][j] ] ] ++ ;
                }
            }
        }
        //for(int i = 0 ; i <= 5 ; i ++ ) cout << deg[i] << " " ; cout << endl ;
        ans = 0 ;
        for(int i = 1 ; i <= n ; i ++ ){
            if(!deg[ cmp[i] ]){
                ans += val[ cmp[i] ] ;
                deg[ cmp[i] ] ++ ;
            }
        }
        printf("Case #%d: %d\n" ,kk++ , ans ) ;
        //for(int i = 0 ; i < n ; i ++ ) cout << save[i].x << " " ;
    }
    return 0 ;
}
