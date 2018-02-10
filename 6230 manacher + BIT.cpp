///分析出每个要求的子串是符合 ——————#——————#——————的形式，用manacher处理最长每个顶点的最长回文半径。
///即转化成：多少个，两个点互相都在对方半径内的串形式。
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn = 500005 ;



///manacher O(n) -_-! 不会用这个版本
void manacher(char str[] , int len[] , int n){
    len[0] = 1 ;
    for(int i = 1 , j = 0 ; i < (n << 1) - 1 ; ++ i){
        int p = i >> 1 , q = i - p , r = ((j + 1) >> 1) + len[j] - 1 ;
        len[i] = r < q ? 0 : min(r - q + 1 , len[(j << 1) - i]);
        while(p > len[i] - 1 && q + len[i] < n && str[p - len[i]]
                == str[q + len[i]])
                ++ len[i] ;
        if(q + len[i] - 1 > r) j = i ;
    }
}


char read[maxn] ;

///manacher
char Ma[maxn << 1] ;
int Mp[maxn << 1] ;
int Manacher(char s[] , int len) {
    int l = 0 ;
    Ma[l ++] = '$' ;
    Ma[l ++] = '#' ;
    for(int i = 0 ; i < len ; i ++){
        Ma[l ++] = s[i] ;
        Ma[l ++] = '#' ;
    }
    Ma[l] = 0 ;
    int mx = 0 , id = 0 ;
    for(int i = 0 ; i < l ; i ++){
        Mp[i] = mx > i ? min(Mp[(id << 1) - i] , mx - i) : 1;
        while(i - Mp[i] >= 0 && Ma[i + Mp[i]] == Ma[i - Mp[i]]) Mp[i] ++;
        if(i + Mp[i] > mx){
            mx = i + Mp[i];
            id = i;
        }
    }
    return l;
}
int r[maxn] ; /// 每个点的回文半径（不包括该点）
/*
满足下列条件的i , j
j > i
j-i <= p[i]
j-i <= p[j]
*/
vector<int> g[maxn] ;///

//BIT
int bit[maxn] ;
int n ;
int sum(int i){
    int ans = 0 ;
    for( ; i > 0 ; i -= i & - i) ans += bit[i] ;
    return ans ;
}
void add(int i , int x){
    for( ; i <= n ; i += i & -i) bit[i] += x ;
}

int main(){
    int kase ; scanf("%d" , &kase) ;
    while(kase --){
        memset(bit , 0 , sizeof bit) ;
        for(int i = 0 ; i < maxn ; i ++) g[i].clear() ;

        scanf("%s" , read) ;
        int str_len = strlen(read) ;
        int len = Manacher(read , str_len) ;

        int k = 1 ;
        for(int i = 2 ; i < len ; i += 2 , k ++){
            r[k] = (Mp[i] >> 1) - 1 ;
            g[k - r[k]].push_back(k) ;
        }

        n = str_len ;
        ll ans = 0 ;
        for(int i = 1 ; i <= n ; i ++ ){
            for(int j = 0 ; j < g[i].size() ; j ++)
                add(g[i][j] , 1) ;
            ans += sum(min(i + r[i] , n)) - sum(i) ;
        }
        printf("%lld\n" , ans) ;
    }
    return 0 ;
}
