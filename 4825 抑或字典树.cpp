/*
 * @Samaritan_infi
 */
 /// 注意开大数组空间，抑或字典树初始化为-1
 
#include <bits/stdc++.h>
using namespace std;
typedef long long ll ;

const int maxn = 4000010 ;
const int bit_max = 33 ;

int trie[maxn][3] , val[maxn] = {0} ;
int num ;
void trie_insert(int x) {
    bitset<bit_max> bit = x ;
    int root = 0 ;
    for(int i = 32 ; i >= 0 ; i --) {
        int k = bit[i] ;
        if(trie[root][k] == -1) trie[root][k] = ++ num ;
        root = trie[root][k] ;
    }
    val[root] = x ;
}

int trie_search(int x) {
    bitset<bit_max> bit = x ;
    int root = 0 ;
    for(int i = 32 ; i >= 0 ; i --) {
        int k = bit[i] ;
        if(trie[root][k ^ 1] == -1) {
            root = trie[root][k] ;
        } else {
            root = trie[root][k ^ 1] ;
        }
    }
    return val[root] ;
}

char word[30] ;
int main() {
    int kase ; scanf("%d" , &kase) ;
    int tt = 1 ;
    while( kase -- ) {
        int n , m , a ;
        memset(trie , -1 , sizeof trie) ;
        scanf("%d %d" , &n , &m) ;
        num = 0 ;
        while( n -- ) {
            scanf("%d" , &a) ;
            trie_insert(a) ;
        }
        printf("Case #%d:\n" , tt ++) ;
        while( m -- ) {
            scanf("%d" , &a) ;
            printf("%d\n" , trie_search(a)) ;
        }
    }
    return 0 ;
}

