/*
 * @Samaritan_infi
 */
///二分
///没有必要知道每一个点具体的状态，只要判断它的上界能够大于下界即成立。
///下界题目给出，上界由二分的值减去其余子树的下界得到
///注意搜索的时候UP值为1，即如果对该点没有上界要求的话，它的上界应该至少是自己。
#include <bits/stdc++.h>
using namespace std ;
typedef long long ll ;

const int maxn = 100005 ;
int n ;
vector<int> edge[maxn] ;
int sub_size[maxn] ;
//搜索子树大小
void search_sub_size(int x , int par){
    sub_size[x] = 1 ;
    for(int i = 0 ; i < edge[x].size() ; i ++){
        int node = edge[x][i] ;
        if(node == par) continue ;
        search_sub_size(node , x) ;
        sub_size[x] += sub_size[node] ;
    }
}
int up[maxn] , down[maxn] , check_up[maxn]; //每个结点子树黑色个数的上下界
int dfs_down[maxn] , dfs_up[maxn] ;

bool dfs(int x , int par){
    int DOWN = 0 , UP = 1 ;
    for(int i = 0 ; i < edge[x].size() ; i ++){
        int node = edge[x][i] ;
        if(node == par) continue ;
        if(!dfs(node , x)) return false ;
        DOWN +=  dfs_down[node] ;
        UP += dfs_up[node] ;
    }
    dfs_down[x] = max(DOWN , down[x]) ;
    dfs_up[x] = min(UP , check_up[x]) ;
    return dfs_up[x] >= dfs_down[x] ;
}

bool check(int num){
    for(int i = 1 ; i <= n ; i ++){
        check_up[i] = min(sub_size[i] , num - up[i]) ;
        if(check_up[i] < down[i]) return false ;
    }
    if(! dfs(1 , 0)) return false ;
    return dfs_down[1] <= num && dfs_up[1] >= num ;
}

void init(){
    memset(sub_size , 0 , sizeof(sub_size)) ;
    memset(up , 0 , sizeof(up)) ;
    memset(down , 0 , sizeof(down)) ;
    for(int i = 1 ; i <= n ; i ++ ) edge[i].clear() ;
}
int main(){
    int kase ; scanf("%d" , &kase) ;
    while(kase --){
        scanf("%d" , &n) ;
        init();
        int l , r , op ;
        for(int i = 1 ; i < n ; i ++){
            scanf("%d %d" , &l , &r) ;
            edge[l].push_back(r) ;
            edge[r].push_back(l) ;
        }
        search_sub_size(1 , 0) ;
        bool flag = true ;
        scanf("%d" , &op) ;
        while(op --){
            scanf("%d %d" , &l , &r) ;
            down[l] = max(down[l] , r) ;
            if(r > sub_size[l]) flag = false ;
        }
        scanf("%d" , &op) ;
        while(op --){
            scanf("%d %d" , &l , &r) ;
            up[l] = max(up[l] , r) ;
            if(r > n - sub_size[l]) flag = false ;
        }
        if(!flag) {puts("-1") ; continue ; }
        l = 0 , r = n ;
        while(l < r){
            int mid = (l + r) >> 1 ;
            if(check(mid)) r = mid ;
            else l = mid + 1 ;
        }
        printf("%d\n" , r) ;

    }
    return 0 ;
}
