/*
 * @Samaritan_infi
 */
/// 数组的比指针的要快上许多

#include <bits/stdc++.h>
using namespace std;
typedef long long ll ;

const int maxn = 1000010 ;

int trie[maxn][26] , sum[maxn] = {0} ;
int num ;
void trie_insert(char word[]) {
    int root = 0 ;
    for(int i = 0 ; word[i] ; i ++) {
        int k = word[i] - 'a' ;
        if(! trie[root][k]) trie[root][k] = ++ num ;
        root = trie[root][k] ;
        sum[root] ++ ;
    }
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


int main() {
    char word[11] ;
    bool flag = false ;

    while(gets(word)) {
        if(strlen(word) == 0) {
            flag = true ;
            continue ;
        }
        if(! flag) trie_insert(word) ;
        else printf("%d\n" , trie_search(word)) ;
    }
    return 0 ;
}

