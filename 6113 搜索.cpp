#include <bits/stdc++.h>

using namespace std;
const int maxn = 1e4 ;
bool vis[115][115] ;
char read[116] ;
bool mp[115][115] ;

int dx[] = { 0 , 0 , 1 , -1} ;
int dy[] = {-1 , 1 , 0 ,  0} ;


int n , m ;
void dfs(int x , int y , int v){
    vis[x][y] = 1 ;
    for(int i = 0 ; i < 4 ; i ++ ){
        int a = x + dx[i] , b = y + dy[i] ;
        if(a < 0 || a > n + 1 || b < 0 || b > m + 1 || vis[a][b] || mp[a][b] != v) continue ;
        dfs(a , b , v) ;
    }
}


int main(){

    while(~ scanf("%d %d" , &n , &m)){
        memset( mp , 0 , sizeof(mp)) ;
        memset(vis , 0 , sizeof(vis)) ;
        for(int i = 1 ; i <= n ; i ++){
            scanf("%s" , read + 1) ;
            for(int j = 1 ; j <= m ; j ++){
                mp[i][j] = read[j] - '0' ;
            }
        }
        int pos_0 = 0 , pos_1 = 0 ;

        for(int i = 0 ; i <= n + 1 ; i ++){
            for(int j = 0 ; j <= m + 1 ; j ++){
                if(!vis[i][j]){
                    if(mp[i][j]){
                        pos_1 ++ ;
                    }else{
                        pos_0 ++ ;
                    }
                    dfs(i , j , mp[i][j]) ;
                }
            }
        }
        /*
        for(int i = 1 ; i <= n ; i ++){
            for(int j = 1 ; j <= m ; j ++ ){
                cout << par[i][j] ;
            }cout << endl ;
        }*/
        //cout << pos_0 << " " << pos_1 << endl ;
        if(pos_0 == 1 && pos_1 == 1) puts("1") ;
        else if(pos_0 == 2 && pos_1 == 1) puts("0") ;
        else puts("-1") ;
    }
    return 0 ;
}
