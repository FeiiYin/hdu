/*
 * @Samaritan_infi
 */
///加上状压真的好难写
#include <bits/stdc++.h>
#define test cout << "  test  " ;
using namespace std ;
typedef long long ll ;

inline ll read()
{
    ll x=0,f=1;char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
    return x*f;
}

const int maxn = 50000 + 5 ;
int type[maxn] ;
vector<int> edge[maxn] ;

int root , root_max_son ;
int son[maxn] ;
bool vis[maxn] ;
int n , type_num ;
ll ans ;

void dfs_root(int x , int pre , int root_tot) {
    son[x] = 1 ;
    int x_max_son = 0 ;
    for(int i = 0 ; i < edge[x].size() ; i ++) {
        int u = edge[x][i] ;
        if(u == pre || vis[u]) continue ;
        dfs_root(u , x , root_tot) ;
        son[x] += son[u] ;
        x_max_son = max(x_max_son , son[u]) ;
    }
    x_max_son = max(x_max_son , root_tot - son[x]) ;
    if(x_max_son < root_max_son) {
        root_max_son = x_max_son ;
        root = x ;
    }
}

vector<int> sta ;
ll sta_num[1100] ;



void dfs_num(int x , int pre , int state) {
    sta.push_back(state) ;
    sta_num[state] ++ ;
    for(int i = 0 ; i < edge[x].size() ; i ++) {
        int u = edge[x][i] ;
        if(u == pre || vis[u]) continue ;
        dfs_num(u , x , state | (1 << type[u])) ;
    }
}


ll cal(int x , int init_state) {
    sta.clear() ;
    memset(sta_num , 0 , sizeof sta_num) ;
    dfs_num(x , 0 , init_state) ;
    //for(int i = 0 ; i < sta.size() ; i ++) cout << sta[i] << " " ; cout << endl ;
    ll res = 0 ;
    for(int i = 0 ; i < sta.size() ; i ++) {
        int s = sta[i] ;
        sta_num[s] -- ;
        res += (ll)sta_num[ (1 << type_num) - 1] ;
        ///枚举所有s的子集
        for(int j = s ; j ; j = (j - 1) & s) {
            res += (ll)sta_num[ j ^ ((1 << type_num) - 1) ] ;
        }
        sta_num[s] ++ ;
    }
    return res ;
}

void dfs(int x) {
    root_max_son = 1e9 ;
    dfs_root(x , 0 , son[x]) ;

    x = root ;
    vis[x] = true ;

    ans += cal(x , 1 << type[x]) ;
    for(int i = 0 ; i < edge[x].size() ; i ++) {
        int u = edge[x][i] ;
        if(vis[u]) continue ;
        ans -= cal(u , (1 << type[x]) | (1 << type[u])) ;
        dfs(u) ;
    }
}

void init() {
    for(int i = 0 ; i <= n ; i ++) edge[i].clear() ;
    memset(vis , 0 , sizeof vis) ;
    ans = 0 ;
    son[1] = n ;
}

int main() {

    while( ~ scanf("%d %d" , &n , &type_num) ) {
        init() ;
        for(int i = 1 ; i <= n ; i ++) scanf("%d" , &type[i]) , type[i] -- ;
        int l , r ;
        for(int i = 1 ; i < n ; i ++) {
            scanf("%d %d" , &l , &r) ;
            edge[l].push_back(r) ;
            edge[r].push_back(l) ;
        }
        if(type_num == 1) {
            printf("%lld\n" ,n * n ) ;
            continue ; 
        }
        dfs(1) ;
        printf("%lld\n" , ans) ;
    }
    return 0 ;
}
