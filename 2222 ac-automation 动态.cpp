/*
 * @Samaritan_infi
 */
#include <bits/stdc++.h>
using namespace std;
typedef long long ll ;

const int max_key = 800 ;
const int max_main = 1e7 + 5 ;
const int maxn = 100000000 ;


struct node {
    node *next[26] ;
    node *fail ;
    int sum ;
};
node * root ;

void init() {
    root = (struct node *) malloc(sizeof(struct node)) ;
    for(int i = 0 ; i < 26 ; i ++) root->next[i] = NULL ;
    root->fail = NULL ; root->sum = 0 ;
}

void ac_insert(char s[]) {
    node * p = root ;
    for(int i = 0 ; s[i] ; i ++ ) {
        int x = s[i] - 'a' ;

        if(p->next[x] == NULL) {
            node * new_node = (struct node *)malloc(sizeof(struct node)) ;
            for(int i = 0 ; i < 26 ; i ++) new_node->next[i] = NULL ;
            new_node->fail = NULL ; new_node->sum = 0 ;
            p->next[x] = new_node ;
        }

        p = p->next[x] ;
    }
    p->sum ++ ;
}

node * que[maxn] ;
void build_fail_pointer() {
    int head = 0 , tail = 1 ;
    que[head] = root;
    node * p;
    node * temp;
    while(head < tail) {
        temp = que[head++];
        for(int i = 0; i < 26; i ++) {
            if(!temp->next[i]) continue ; 

            if(temp == root) {
                temp->next[i]->fail = root;
            } else {
                p = temp->fail;
                while(p) {
                    if(p->next[i]) {
                        temp->next[i]->fail = p->next[i];
                        break;
                    }
                    p = p->fail;
                }
                if(p == NULL) temp->next[i]->fail = root;
            }
            que[tail++] = temp->next[i];

         
        }
    }
}

int ac_automation(char *ch) {
    int cnt = 0 ;
    node * p = root;
    int len = strlen(ch);
    for(int i = 0; i < len; i ++) {
        int x = ch[i] - 'a';
        while(! p->next[x] && p != root) p = p->fail;
        p = p->next[x];
        if(! p) p = root;
        node *temp = p;
        while(temp != root) {
           if(temp->sum >= 0) {
               cnt += temp->sum;
               temp->sum = -1;
           } else break;
           temp = temp->fail;
        }
    }
    return cnt ;
}


char key[max_key] ;
char read[max_main] ;

int main() {
    int kase ; scanf("%d" , &kase) ;
    int n ;
    while( kase -- ) {
        init() ;
        scanf("%d" , &n) ;
        while( n -- ) {
            scanf("%s" , key) ;
            ac_insert(key) ;
        }
        scanf("%s" , read) ;
        build_fail_pointer() ;
        int ans = ac_automation(read) ;
        printf("%d\n" , ans) ;
    }
    return 0 ;
}
