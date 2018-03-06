///f[i][j] == 1代表i到j区间内能全部消去
///递推时考虑三种情况，i，j ； i，k && k + 1 ，j ； i，k，j && i + 1 , k - 1 && k + 1 && j - 1  
#include <bits/stdc++.h>
using namespace std;
typedef long long ll ;

const int maxn = 605 ;
int read[maxn] ;
//int interval[maxn] ;
map<int , int> a ; 

int vis[maxn][maxn] ;
int dp[maxn] ; //[maxn] ;

int n , m ;
void show(){
    for(int i = 0 ; i < n ; i ++){
        for(int j = 0 ; j < n ; j ++){
            cout << vis[i][j] << " " ;
        }cout << endl ;
    }
}

void init(){
    memset(vis , 0 , sizeof(vis)) ;
    a.clear() ; 
    memset(dp , 0 , sizeof(dp)) ;
}
int main(){
    int kase ;
    scanf("%d" , &kase) ;
    while(kase --){
        //int n , m ;
        scanf("%d %d" , &n , &m) ;
        init() ;
        for(int i = 1 ; i <= n ; i ++) scanf("%d" , &read[i]) , vis[i][i - 1] = 1 ;
        int temp ;

        for(int i = 0 ; i < m ; i ++) {
            scanf("%d" , &temp) ;
            a[temp] = 1 ;
        }


        for(int len = 2 ; len <= n ; len ++){

            for(int i = 1 , j = len ; j <= n ; i ++ , j ++){

                if( a[read[j] - read[i]] ) {
                    vis[i][j] |= vis[i + 1][j - 1] ;
                }

                for(int k = i + 1 ; k < j ; k ++){
                    vis[i][j] |= vis[i][k] && vis[k + 1][j] ;
                }
                if( (read[j] - read[i]) % 2 == 0 && a[(read[j] - read[i]) >> 1] ){
                    for(int k = i + 1 ; k < j ; k ++){
                        if(read[k] << 1 == read[i] + read[j]){
                            //cout << "here" << endl ;
                            vis[i][j] |= vis[i + 1][k - 1] && vis[k + 1][j - 1] ;
                        }
                    }
                }
            }
        }
        //show() ;

        for(int i = 1 ; i <= n ; i ++){
            dp[i] = dp[i - 1] ;
            for(int j = 1 ; j <= i ; j ++){
                if(!vis[j][i]) continue ;
                dp[i] = max(dp[i] , dp[j - 1] + i - j + 1) ;
            }
        }
        printf("%d\n" , dp[n] ) ;
    }
    return 0 ;
}
