/*
 * @Samaritan_infi
 */
///注意对顶点排序建边避免重复，暴力搜索
#include <bits/stdc++.h>
using namespace std;
typedef long long ll ;

const int maxn = 110 ;
int n , m , s ;
bool pic[maxn][maxn] ;
vector<int> edge[maxn] ;


int ans , save[maxn] ;
void show(int now) {
    cout << "show : " ;
    for(int i = 0 ; i < now ; i ++ ) cout << save[i] << " " ; cout << endl ;
}
void dfs(int now) {
    if(now == s) {
        ans ++ ;
        return ;
    }
    for(int i = 0 ; i < edge[save[now - 1]].size() ; i ++) {
        int reach = edge[save[now - 1]][i] ;
        bool flag = true ;
        for(int j = 0 ; j < now ; j ++) {
            if(! pic[save[j]][reach]) {
                flag = false ;
                break ;
            }
        }
        if(flag) {
            save[now ++] = reach ;
            dfs(now) ;
            now -- ;
        }
    }
}

void init(int n) {
    for(int i = 1 ; i <= n ; i ++) edge[i].clear() ;
    memset(pic , false , sizeof pic) ;
    save[0] = 1 ;
    ans = 0 ;
}

int main(){
    int kase ;
    scanf("%d" , &kase) ;
    while (kase --) {
        scanf("%d %d %d" , &n , &m , &s) ;
        init(n) ;
        int l , r ;
        for(int i = 0 ; i < m ; i ++ ) {
            scanf("%d %d" , &l , &r) ;
            if(l > r) swap(l , r) ;
            edge[l].push_back(r) ;
            pic[l][r] = pic[r][l] = true ;
        }
        for(int i = 1 ; i <= n ; i ++){
            save[0] = i ;
            dfs(1) ;
        }

        printf("%d\n" , ans) ;
    }
    return 0;
}
