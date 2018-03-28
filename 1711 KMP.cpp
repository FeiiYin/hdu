/*
 * @Samaritan_infi
 */
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

const int maxn = 1e6 + 5;
int kmp_next[maxn];
int kmp[maxn];
int read[maxn];
int s[maxn];


void get_next(int s[], int len) {
    int i = 0, j = -1;
    kmp_next[i] = j;
    while(i < len) {
        if(j == -1 || s[i] == s[j])
            j ++, i ++, kmp_next[i] = j;
        else
            j = kmp_next[j];
    }
}


void work_kmp(int s[], int t[], int s_len, int t_len) {
    int i = 0, j = 0;
//    int s_len = strlen(s), t_len = strlen(t);
    while(i < s_len) {
        if(j == -1 || s[i] == t[j])
            j ++, i ++, kmp[i] = j;
        else
            j = kmp_next[j];
    }
}



void show(int a[], int len) {
for(int i = 0; i <= len; i ++) cout << a[i] << " "; cout << endl;
}

int main() {
    int kase; scanf("%d", &kase);
    while(kase --) {
        int n, m, x;
        scanf("%d %d", &n, &m);
        for(int i = 0; i < n; i ++) scanf("%d", &read[i]);
        for(int i = 0; i < m; i ++) scanf("%d", &s[i]);
        get_next(s, m);
        work_kmp(read, s, n, m);
        bool flag = true;
        for(int i = 1; i <= n; i ++) {
            if(kmp[i] == m) {
                printf("%d\n", i - m + 1);
                flag = false;
                break;
            }
        }
        if(flag) puts("-1");
    }
    return 0;
}
