/*
 * @Samaritan_infi
 */
/// 查询字符串是多少个字符串的子串，将原串的所有子串前缀插入字典树，
/// 注意abab和ab的情况，需要在插入同一个串时判断，不对sum增加
#include <bits/stdc++.h>
using namespace std;
typedef long long ll ;

const int maxn = 1000010 ;

int trie[maxn][26] , sum[maxn] = {0} , id[maxn] = {0} ;
int num ;
void trie_insert(char word[] , int pos) {
    int root = 0 ;
    for(int i = 0 ; word[i] ; i ++) {
        int k = word[i] - 'a' ;
        if(! trie[root][k]) trie[root][k] = ++ num ;
        root = trie[root][k] ;
        if(id[root] != pos) sum[root] ++ ;
        id[root] = pos ;
    }
    //cout << word << "   " << sum[root] << endl ;
}
int trie_search(char word[]) {
    int root = 0 ;
    for(int i = 0 ; word[i] ; i ++) {
        int k = word[i] - 'a' ;
        if(! trie[root][k]) return 0 ;
        root = trie[root][k] ;
    }
    return sum[root] ;
}

char word[30] ;
int main() {
    int n ; scanf("%d" , &n) ;
    for(int i = 1 ; i <= n ; i ++) {
        scanf("%s" , word) ;
        for(int j = 0 ; j < strlen(word) ; j ++) {
            trie_insert(word + j , i) ;
        }
    }
    scanf("%d" , &n) ;
    while( n -- ) {
        scanf("%s" , word) ;
        printf("%d\n" , trie_search(word)) ;
    }
    return 0 ;
}

